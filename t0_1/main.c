/******************************************************
 * main.c
 *
 * Program Name:  t0_1
 *         Date:  2021-04-20
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


const char precarga = 68; 

//Prototipo
void AVRInit();

ISR(TIMER0_OVF_vect)
{
    TCNT0 = precarga;
    
}

int main()
{
	// Initialize the AVR modules
	AVRInit();
    
	// Infinite loop
	while(1)
	{

	}

	return 0;
}

void AVRInit()
{
	DDRB |= (1<< PB2);
    DDRD |= (1<< PD5);
    timer0_setup(0,8,1,1);
    
    TIMSK |= (1 << TOIE0);
    OCR0A = 100;
	sei();
    
}
