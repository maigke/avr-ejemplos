/******************************************************
 * main.c
 *
 * Program Name:  t0_2
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
    DDRB |= (1<< PB2);
    
    /* Modo: 2 (CTC)
     * Prescale: 256
     * OC0A: 1 (toggle)
     * Periodo: 10 ms
     * OCR0A: 155
     */
    timer0_setup(2,256,1,0);
    OCR0A = 156;
    
}
