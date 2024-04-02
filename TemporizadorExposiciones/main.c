/******************************************************
 * main.c
 *
 * Program Name:  TemporizadorExposiciones
 *         Date:  2024-04-01
 *       Author:  YOUR_NAME
 *      License:  YOUR_LICENSE
 *
 * Description:
 *  This is my program description..
 * 
 *****************************************************/
/*
 * main.c
 *
 * Created: 3/17/2024 5:19:21 PM
 *  Author: mmont
 */ 

#include <xc.h>
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>



// Definición de pines
#define BOTON_SET_PIN    PB0
#define BOTON_MAS_PIN    PB1
#define BOTON_MENOS_PIN  PB2
#define LED_EXPOSICION   PB3
#define LEDS_TIEMPO_PIN  PB4
#define LED_SEMAFORO_AZUL PD2
#define LED_SEMAFORO_ROJO    PD0
#define LED_SEMAFORO_VERDE   PD1

// Definición de estados
#define AJUSTE_TIEMPO_EXPOSICION 0
#define AJUSTE_TIEMPO_PREGUNTAS  1
#define EJECUCION_TIEMPO_EXPOSICION 2
#define EJECUCION_TIEMPO_PREGUNTAS  3

// Variables globales
uint8_t estado_actual = AJUSTE_TIEMPO_EXPOSICION;
uint8_t tiempo_exposicion = 0;
uint8_t tiempo_preguntas = 0;


// Definir variables globales
volatile uint16_t contador_tiempo_exposicion = 0;
volatile uint8_t minuto = 0;
// Función de interrupción para el temporizador (ejemplo para un temporizador de 8 bits)
ISR(TIMER0_OVF_vect) {
	contador_tiempo_exposicion++;
	if(contador_tiempo_exposicion == 14648)
	{
		minuto++;
		contador_tiempo_exposicion = 0;
	}
}


void timer0_setup( uint8_t mode,
uint16_t prescale,
uint8_t outmode_A,
uint8_t outmode_B){
	mode &= 7;
	outmode_A &= 3;
	outmode_B &= 3;
	uint8_t clock_mode = 0;
	switch(prescale)
	{
		case 1: clock_mode = 1; break;
		case 8: clock_mode = 2; break;
		case 64: clock_mode = 3; break;
		case 256: clock_mode = 4; break;
		case 1024: clock_mode = 5; break;
		default:
		if (prescale <0)
		clock_mode = 7;
	}
	TCCR0A = (outmode_A<<6) | (outmode_B <<4)|(mode & 3);
	TCCR0B = ((mode &0x04)<<1) | (clock_mode);
}


// Función para iniciar temporizador
void iniciar_temporizador() {
	contador_tiempo_exposicion = 0;
	minuto = 0;
	// Configurar temporizador (ejemplo para un temporizador de 8 bits)
	//TCCR0A = 0; // Modo normal
	//TCCR0B = (1 << CS00) | (1 << CS02); // Prescaler de 1024
	timer0_setup(0,64,0,0);
	TIMSK |= (1 << TOIE0); // Habilitar interrupción por desbordamiento
	TCNT0 = 0; // Reiniciar el contador
	sei();
}

// Función para detener temporizador
void detener_temporizador() {
	// Detener temporizador
	TCCR0B &= ~((1 << CS00) | (1 << CS01) | (1 << CS02)); // Detener temporizador
}

// Función para comparar el tiempo transcurrido con el tiempo guardado
int comparar_tiempo_exposicion(uint8_t tiempo_guardado) {
	if (minuto >= tiempo_guardado) {
		// Se alcanzó el tiempo de exposición deseado
		// Realizar acciones correspondientes
		detener_temporizador();
		return 1;
	}
	return 0;
}

// Función para inicializar los pines de los botones
void inicializar_botones() {
	// Configura los pines de los botones como entradas
	DDRB &= ~((1 << BOTON_SET_PIN) | (1 << BOTON_MAS_PIN) | (1 << BOTON_MENOS_PIN));
	// Habilita las resistencias de pull-up internas
	PORTB |= (1 << BOTON_SET_PIN) | (1 << BOTON_MAS_PIN) | (1 << BOTON_MENOS_PIN);
	// Configura el pin de los LEDs de tiempo como salida
	DDRB |= (0x0F << LEDS_TIEMPO_PIN);
	DDRB |= (1 << LED_EXPOSICION);
	// Configura los pines del semáforo como salida
	DDRD |= (1 << LED_SEMAFORO_AZUL) | (1 << LED_SEMAFORO_ROJO) | (1 << LED_SEMAFORO_VERDE);

}

// Función para leer el estado de los botones
uint8_t leer_botones() {
	// Lee el estado de los pines de los botones
	return ~(PINB);
}

// Función para actualizar visualización de LEDs de tiempo
void actualizar_leds(uint8_t tiempo) {
	// Máscara para obtener los 4 bits inferiores del tiempo
	uint8_t tiempo_modificado = tiempo & 0x0F;

	// Apaga todos los LEDs
	PORTB &= ~(0x0F << LEDS_TIEMPO_PIN);

	// Enciende los LEDs correspondientes según el valor del tiempo
	PORTB |= (tiempo_modificado << LEDS_TIEMPO_PIN);
}

int main(void)
{
	int j = 0;  //variable para romper ciclos
    // Configuración de pines
    inicializar_botones();
	
	// Encender el LED de exposición
	PORTB |= (1 << LED_EXPOSICION);
	    
	// Parpadear los LEDs de tiempo a intervalos de 500ms
	for (int i = 0; i < 10; i++) {
		_delay_ms(1000);
		PORTB ^= (0x0F << LEDS_TIEMPO_PIN); // Invierte el estado de los LEDs
	}
	    

    // Bucle principal
    while (1) {
	    uint8_t botones = leer_botones();

	    // Lógica de la máquina de estados
	    switch (estado_actual) {
			case AJUSTE_TIEMPO_EXPOSICION:
			if (botones & (1 << BOTON_SET_PIN)) {
				// Guardar tiempo ajustado de exposición
				if(botones & (1 << BOTON_SET_PIN))
				{

					while(botones &(1 << BOTON_SET_PIN)){
						botones = leer_botones();
					}
				}
				// Apagar LEDs de tiempo y LED de exposición
				PORTB &= ~(0x0F << LEDS_TIEMPO_PIN);
				PORTB &= ~(1 << LED_EXPOSICION);

				// Cambiar al estado de ajuste de tiempo de preguntas
				estado_actual = AJUSTE_TIEMPO_PREGUNTAS;
				} else {
				// Implementar lógica de ajuste de tiempo de exposición
				if (botones & (1 << BOTON_MAS_PIN)) {
					_delay_ms(25);
					tiempo_exposicion++; // Incrementar tiempo de exposición
					} else if (botones & (1 << BOTON_MENOS_PIN)) {
					if (tiempo_exposicion > 0) {
						_delay_ms(25);
						tiempo_exposicion--; // Decrementar tiempo de exposición si es mayor que cero
					}
				}

				// Actualizar visualización de LEDs de tiempo
				actualizar_leds(tiempo_exposicion);
			}
			break;

		    case AJUSTE_TIEMPO_PREGUNTAS:
		    if (botones & (1 << BOTON_SET_PIN)) {
			     // Guardar tiempo ajustado de preguntas
			    PORTB &= ~(1 << LED_EXPOSICION); // Apagar LED de exposición
				_delay_ms(25);
				if(botones & (1 << BOTON_SET_PIN))
				{
					
					while(botones & (1 << BOTON_SET_PIN)){
						botones = leer_botones();
					}	
				}
			    estado_actual = EJECUCION_TIEMPO_EXPOSICION;
			    } else {
			    // Implementar lógica de ajuste de tiempo de preguntas
				if (botones & (1 << BOTON_MAS_PIN)) {
					tiempo_preguntas++; // Incrementar tiempo de preguntas
					} else if (botones & (1 << BOTON_MENOS_PIN)) {
					if (tiempo_preguntas > 0) {
						tiempo_preguntas--; // Decrementar tiempo de preguntas si es mayor que cero
					}
				}

				// Actualizar visualización de LEDs de tiempo
				actualizar_leds(tiempo_preguntas);
		    }
		    break;

		    case EJECUCION_TIEMPO_EXPOSICION:
		    iniciar_temporizador(); // Iniciar temporizador de exposición
			// Encender el LED de exposición
			PORTB |= (1 << LED_EXPOSICION);
			PORTD |= (1 << LED_SEMAFORO_VERDE);
			PORTD &= ~(1 << LED_SEMAFORO_AZUL);
			PORTD &= ~(1 << LED_SEMAFORO_ROJO);
			
		    // Implementar lógica de ejecución de tiempo de exposición
				while(estado_actual == EJECUCION_TIEMPO_EXPOSICION){
					actualizar_leds(minuto);
					if((tiempo_exposicion - minuto) == 1){
						PORTD |= (1 << LED_SEMAFORO_VERDE);
						//PORTD |= (1 << LED_SEMAFORO_AMARILLO);
						PORTD |= (1 << LED_SEMAFORO_ROJO);
					}
					j = comparar_tiempo_exposicion(tiempo_exposicion);
					if (j == 1)
						break;					
				}
				actualizar_leds(minuto);
				PORTD &= ~(1 << LED_SEMAFORO_VERDE);
				PORTD &= ~(1 << LED_SEMAFORO_AZUL);
				PORTD |= (1 << LED_SEMAFORO_ROJO);
				j  = 0;
				botones = leer_botones();
				while (!(botones & (1 << BOTON_SET_PIN))) {
					botones = leer_botones();
				}
				estado_actual = EJECUCION_TIEMPO_PREGUNTAS;
		    break;

		    case EJECUCION_TIEMPO_PREGUNTAS:
			minuto = 0;
			contador_tiempo_exposicion = 0;
		    iniciar_temporizador(tiempo_preguntas); // Iniciar temporizador de preguntas
			PORTB &= ~(1 << LED_EXPOSICION);  //Apagar led de Exposicion
			PORTD |= (1 << LED_SEMAFORO_VERDE);  //Encender led Semaforo Verde
		    PORTD &= ~(1 << LED_SEMAFORO_AZUL);
		    PORTD &= ~(1 << LED_SEMAFORO_ROJO);
			// Implementar lógica de ejecución de tiempo de preguntas
			while(estado_actual == EJECUCION_TIEMPO_PREGUNTAS){
				actualizar_leds(minuto);
				if((tiempo_preguntas - minuto) == 1){
					PORTD |= (1 << LED_SEMAFORO_VERDE);
					PORTD |= (1 << LED_SEMAFORO_AZUL);
					PORTD |= (1 << LED_SEMAFORO_ROJO);
				}
				j = comparar_tiempo_exposicion(tiempo_preguntas);
				if ( j == 1)
					break;
			}
			actualizar_leds(minuto);
			PORTD &= ~(1 << LED_SEMAFORO_VERDE);
			PORTD &= ~(1 << LED_SEMAFORO_AZUL);
			PORTD |= (1 << LED_SEMAFORO_ROJO);
			// Esperar a que el usuario presione el botón SET para reiniciar o apague y encienda el temporizador para ajustar nuevos tiempos
			j  = 0;
			botones = leer_botones();
			while (!(botones & (1 << BOTON_SET_PIN))) {
				botones = leer_botones();
			}
			estado_actual = EJECUCION_TIEMPO_EXPOSICION;
		    break;
			
	    }

	    _delay_ms(50); // Pequeña pausa para evitar rebotes de botones
    }

    return 0;

}