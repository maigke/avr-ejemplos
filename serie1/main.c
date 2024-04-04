/******************************************************
 * main.c
 *
 * Program Name:  serie1
 *         Date:  2020-11-18
 *       Author:  YOUR_NAME
 *      License:  YOUR_LICENSE
 *
 * Description:
 *  This is my program description..
 *
 *****************************************************/
#include <avr/io.h>
#include <util/delay.h>

#define LED PD2

void AVRInit();

int main()
{
	unsigned char c;
	// Initialize the AVR modules
	AVRInit();

	// Infinite loop
	while(1)
	{
		while(!(UCSRA & (1<<RXC)));
		c=UDR;
		PORTD ^=(1<<LED);
	}

	return 0;
}


void AVRInit()
{
	// AVR Initialization
	UBRRL = 12;
	UCSRB = (1 << RXEN);  //Recepcion habilitada
	UCSRC = (3<< UCSZ0);  //8 bits de datos
	UCSRC&=~(1 << USBS);  //un bit de paro

	DDRD |=(1<<PD1); //Salida TxD
	DDRD &=~(1<<PD0); //Entrada RxD 
}
