/******************************************************
 * main.c
 *
 * Program Name:  ejem_1
 *         Date:  2021-03-23
 *       Author:  YOUR_NAME
 *      License:  YOUR_LICENSE
 *
 * Description:
 *  This is my program description..
 *
 *****************************************************/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED PD3

volatile char flag = 1;

ISR(INT0_vect)
{
	flag^= 1;  //cada vez que entra INT0 se conmuta la bandera
}


//Prototipos de funciones
void AVRInit();

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
  /*
	 Configuracion de la interrupcion  INT0
   Caracteristicas:
	 Entra la interrupcion por flanco de subida
	*/
	GIMSK |= (1<<INT0);
  MCUCR &= ~(1<< ISC01);
	MCUCR |= (1<< ISC00);


	DDRD|=(1<<LED);
	DDRD &= ~(1<<PD2); //Declara como entrada INT0
	PORTD |=(1<<PD2);  //habilita RPullUp de INT0

  sei();
}
