/******************************************************
 * main.c
 *
 * Este programa 
 * Program Name:  ejemplo2
 *         Date:  2024-03-30
 *       Author:  Miguel Montiel Mtz
 *      License:  YOUR_LICENSE
 *
 * Description:
 *  This is my program description..
 * 
 *****************************************************/
#include <avr/io.h> 
#include <util/delay.h> 

#define clear_bit(sfr,bit) (SFR_BYTE(sfr) &=~_BV(bit))
#define set_bit(sfr,bit) (SFR_BYTE(sfr) |= _BV(bit))
#define toggle_bit(sfr,bit) (SFR_BYTE(sfr) ^=_BV(bit)) 

void AVRInit()
{
	// AVR Initialization
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
