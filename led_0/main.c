/******************************************************
 * main.c
 *
 * Program Name:  led_0
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
int const precarga = 131;


//Macro de Interrupcion
ISR(TIMER0_OVF_vect)  //latido
{
    TCNT0 = precarga;
    PORTB^=(1<<PB5);
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
	// AVR Initialization
    timer0_setup(0,8,0,0);  //modo de funcionamiento del timer
    TIMSK |=(1<<TOIE0);  //mascara para interrupcion del timer
    DDRB|=(1<<PB5);  //led  
    sei();  //Habilita las interrupciones globalmente
}
