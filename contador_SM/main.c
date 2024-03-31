/******************************************************
 * main.c
 *
 * Program Name:  contador_SM
 *         Date:  2024-03-30
 *       Author:  Miguel Montiel
 *      License:  YOUR_LICENSE
 *
 * Description:
 *  Se lee un pulso emitido por un sensor de proximidad
 *  dicho pulso se ve refleado en dos leds de salida
 *  contando del 0 al 3 y al llegar un nuevo pulso
 *  causa el desbordamiento.
 *  El conteo se realiza por medio de una maquina de 
 *  estados finitos.
 * 
 *****************************************************/
#include <avr/io.h> 
#include <util/delay.h> 

/**
* @name Macros para sustituir el seteo de bits individuales
*/
#define setbit(sfr,bit) (_SFR_BYTE(sfr)|=_BV(bit))    /**<Pone en set un bit*/
#define clrbit(sfr,bit) (_SFR_BYTE(sfr)&=~_BV(bit))   /**<Pone en clear un bit*/
#define togglebit(sfr,bit) (_SFR_BYTE(sfr)^=_BV(bit)) /**<Cambia el estado de bit*/
#define DDR(x) (*(&x -1)) ///< direcciona al puerto de configuracion
#define PIN(x) (*(&x -2)) ///< direcciona al puerto de lectura


uint8_t Edo_actual = 0;
uint8_t temp = 0;


void AVRInit()
{
	clrbit(DDRC, DDC2); // Entrada del sensor óptico
	setbit(DDRD, DDD7); // salida 
	setbit(DDRB, DDB0); // salida
}

int main()
{
	// Initialize the AVR modules
	AVRInit();
	clrbit(PORTD, PD7);
	clrbit(PORTB, PB0);

	// Infinite loop
	while(1)
	{
		if(bit_is_clear(PINC, PC2))
		{
			_delay_ms(20);
			if(bit_is_clear(PINC, PC2))
			{
				if(bit_is_set(PIND, PD7))
				{setbit(Edo_actual, 0);}
				else
				{clrbit(Edo_actual, 0);}
				if(bit_is_set(PINB, PB0))
				{setbit(Edo_actual, 1);}
				else
				{clrbit(Edo_actual, 1);}
				Edo_actual++;
				if(Edo_actual == 0x04)
				{Edo_actual = 0;}
				//Se enmascara el estado actual
				Edo_actual &= 0x03;
				temp = Edo_actual & 0x02;
				if(temp == 0x02)
				{setbit(PORTB, PB0);}
				else
				{clrbit(PORTB, PB0);}
				
				temp = Edo_actual & 0x01;
				if(temp == 0x01)
				{setbit(PORTD, PD7);}
				else
				{clrbit(PORTD, PD7);}
			}
		}
	}

	return 0;
}
