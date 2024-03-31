/******************************************************
 * main.c
 *
 * Program Name:  int0_1
 *         Date:  2020-10-13
 *       Author:  YOUR_NAME
 *      License:  YOUR_LICENSE
 *
 * Description:
 *  Este program lee un boton en PD2 por medio de 
 *  interrupciones
 *****************************************************/
#include <avr/io.h> 
#include <util/delay.h> 
#include <avr/interrupt.h>
#define LED PD3


volatile char flag = 0;

/* Declaracion de funciones
*/
void AVRInit();

ISR(INT0_vect)
{
	flag^=1;
}


int main()
{
	// Initialize the AVR modules
	AVRInit();

	// Infinite loop
	while(1)
	{
		flag?PORTD|=(1<<LED):PORTD&=~(1<<LED); 
	}

	return 0;
}

void AVRInit()
{
	GIMSK |= (1<<INT0);  //Boton en PD2
	MCUCR |= (1<<ISC01); //Flanco de bajada
	MCUCR &=~(1<<ISC00); 

	DDRD &=~(1<<PD2);  //Escribir un cero en DDRx es entrada
	PORTD |= (1<<PD2); //Escribir a una entrada un uno, es RBPU

	DDRD|=(1<<LED);
	sei();
}
