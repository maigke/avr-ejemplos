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
