/************************************************************************
@file "clk.c"
Implementaci�n del modulo clk.h
@author Miguel Montiel
************************************************************************/
#include "clk.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


/***********************************************************************                                                                     *
@details funcion que inicializa la atmega32u4 con los preescalamientos adecuados
*/


/**
@details Funcion que llama a _delay_ms para evitar desbordamientos
*/
void delay_ms(unsigned int time_ms)
{
    unsigned int i;
    for(i=0; i<time_ms; i++)
        _delay_ms(1);
}
