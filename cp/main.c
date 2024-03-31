/******************************************************
 * main.c
 *
 * Program Name:  cp
 *         Date:  2021-03-24
 *       Author:  YOUR_NAME
 *      License:  YOUR_LICENSE
 *
 * Description:
 *  This is my program description..
 *
 *   Calculo de las RPM
 *   muescas = 8;
 *   Eventos por vuelta = 16  ---> vuelta
 *   Tiempo de muestreo 50ms  ---> Ts = 10
 *   Cuenta de muescas        ---> n
 *
 *   Para calcular la velocidad en RPM se realizan las
 *   siguientes operaciones:
 *
 *   velocidad = eventos/ Tiempo de muestreo
 *
 *   v = n/10e-3 = 100n;
 *
 *   La velocidad en terminos de Hertz, se determina como
 *
 *   v = velocidad/ Eventos por vuelta
 *   v = v/16  (Hz)
 *
 *   Para convertir esta cantidad a RPM se debe multiplicar
 * 	 por 60 segundos
 *
 *   v_RPM = 60v;

 *
 *   Por lo tanto la expresion puede quedar como
 *
 *	 v_RPM = 60*n*Ts/vuelta
 *
 *
 *
 *
 *****************************************************/
#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <timer0/timer0.h>
#include <timer1/timer1.h>
#include <lcd/lcd.h>

volatile uint16_t n=0;
volatile char flagSample = 1;
const char vuelta = 18; //cambios por revolucion
const int Umbral = 1;
long startTime = 0;
volatile unsigned int OvCount= 0;
volatile unsigned int OvCount2= 0;
volatile unsigned long int ticks=0;


//prototipos
void AVRInit();
void motor(int valor);
long int getTime();


/*
* Se configura para que entre cada cambio
*/
ISR(INT0_vect)
{
	//if(ticks-startTime > Umbral)
	{
		n++;
		//startTime = ticks;
		//PORTD ^=(1<<PD1);
	}

}

/*
* El tiempo de muestreo debe ser de 100ms
* El microcontrolador puede generar 100.352ms

*/

ISR(TIMER0_OVF_vect)
{
	OvCount++;

	if (OvCount == 195)  //49 = 100ms aprox
	{
		flagSample=1;
		OvCount =0;
	}
}

int main()
{
	// Initialize the AVR modules
	char v[8];   //salida del motor a leer
	char e[6]; char uu[4]; char r[4];
  float error = 0.0;
	int referencia = 30; //velocidad tick en 50ms 42 /2 = 21
	int u = 0;
	int u_k = 0;
	float Kp = 9.85;//Kp = 255/35 a max vel cuenta 35 pulsos en 106ms
	AVRInit();
  // Infinite loop
	while(1)
	{
		if(flagSample)
		{
			error = referencia - n;
			u = (int) (Kp*error);
			if (u< 0) u=0;
			if (u>255) u = 255;
			u_k = (u);  //lo transforma a un numero de 8 bits
			motor(u_k);  //funcion que determina el valor u
			PORTD ^=(1<<PD0);
			ticks +=n;
		  OvCount2++;
			//itoa(n,v,10);//itoa((int)(error), e,10);itoa(u_k,uu,10);itoa(referencia,r,10);
			flagSample = 0; n = 0; error=0;
			//lcd_clrscr();
		//	lcd_gotoxy(0,0);lcd_puts(v);//lcd_puts(" ");lcd_puts(e);
			//lcd_puts(" ");lcd_puts(uu);
		//	lcd_gotoxy(0,1);lcd_puts(r);
		}
		if(OvCount2 == 200)
		{
			itoa(ticks,v,10);
			lcd_clrscr();
		  lcd_gotoxy(0,0);lcd_puts(v);
			ticks=0;OvCount2=0;

		}

	}

	return 0;
}


void AVRInit()
{
	// AVR Initialization

	GIMSK |= (1 << INT0);
	MCUCR &= ~(1 << ISC01); //Cualquier cambio lógico genera una interrupt
	MCUCR |= (1 << ISC00);
	//MCUCR |= (1 << ISC01);

	DDRD &=~(1<<PD2);   //Configura como entrada
	PORTD |=(1<<PD2);  //Resistencia de pullup
  DDRD |=(1<<PD0);
	DDRD |=(1<<PD1);
  //Configura el timer0 para generar interrupcion cada 100ms
	/*
	Modo Normal (0)
	Factor de prescalamiento: 8
	Periodo de autoreset = 1s
	F_CLK = 1MHz
	*/
	timer0_setup(0,1,0,0);
	//OCR0A = 122;
	TIMSK |= (1 << TOIE0);
	sei();

  //Configura Timer 1 para generar PWM por temporizacion
  /*
   * Modo: FastPWM (7)
	 * Factor de prescalamiento: 8
	 * Frecuencia de PWM estimada: 1kHz
	 *
	*/

  timer1_setup(5,1,2,0,0);
	DDRB |=(1<<PB3); //Terminal de salida PWM
  lcd_init(LCD_DISP_ON);
}

/*Genera una PWM defina por el valor dado*/
void motor(int valor)
{
	OCR1A= valor;
}
