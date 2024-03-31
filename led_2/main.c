/******************************************************
 * main.c
 *
 * Program Name:  led_2
 *         Date:  2020-10-21
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
	// AVR Initialization
    timer0_setup(3,1,2,0);
    OCR0A = 0xE3;
    
    DDRB|=(1<<PB2);
}
