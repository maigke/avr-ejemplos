/******************************************************
 * main.c
 *
 * Program Name:  led_1
 *         Date:  2020-10-20
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
#include <timer0/timer0.h>


void AVRInit();

ISR(TIMER0_COMPA_vect)
{
    PORTB^=(1<<PB5);
}


int main()
{
	// Initialize the AVR modules
	AVRInit();
    PORTB&=~(1<<PB5);
    _delay_ms(5000);

	// Infinite loop
	while(1)
	{

	}

	return 0;
}


void AVRInit()
{
	// AVR Initialization
    
    DDRB|=(1<<PB5);
    OCR0A = 194;
    timer0_setup(2,256,0,0); //modo CTC
    TIMSK|=(1<<OCIE0A);  //habilito la interrupcion por comparacion
    sei();
}
