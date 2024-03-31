/************************************************************************
@file "timer0.c"
Implementación del modulo timer0.h
@author Miguel Montiel
************************************************************************/
#include <avr/io.h>
#include "timer0.h"

/**
@details Selecciona el modo, el preescalamiento y los modos para acomodarlos en los registros TCCR0A y TCCR0B
*/
void timer0_setup(byte mode, int prescale, byte outmode_A, byte outmode_B)
{
    mode&=7;
    outmode_A&=3;
    outmode_B&=3;
    byte clock_mode = 0;

    switch(prescale)
    {
        case 1: clock_mode = 1; break;
        case 8: clock_mode = 2; break;
        case 64: clock_mode = 3; break;
        case 256: clock_mode = 4; break;
        case 1024: clock_mode = 5; break;
        default:
            if(prescale < 0)
                clock_mode = 7;
    }

    TCCR0A = (outmode_A << 6) | \
             (outmode_B << 4) | \
             (mode & 0x03);
    TCCR0B = ((mode & 0x04)<<1) | (clock_mode);
}
