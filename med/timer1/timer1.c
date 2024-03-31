#include <avr/io.h>
#include "timer1.h"

void timer1_setup(unsigned char mode, int prescale, unsigned char outmode_A, unsigned char outmode_B, unsigned char capture)
{
    /*
     *Ajustando el ancho de los campos de bit
     */
     mode &= 15;
     outmode_A &= 3;
     outmode_B &= 3;
     capture &= 3;

     unsigned char clock_mode = 0;
     //El cero significa que el temporizador está apagado

     switch(prescale)
     {
        case 1: clock_mode = 1; break;
        case 8: clock_mode = 2; break;
        case 64: clock_mode = 3; break;
        case 256: clock_mode = 4; break;
        case 1024: clock_mode = 5; break;
        default:
            if(prescale < 0) //Habilitar conexion por reloj externo
                clock_mode = 7;
     }
     TCCR1A = (outmode_A << 6) | \
              (outmode_B << 4) | \
              (mode & 3);

     TCCR1B = (capture << 6) | ((mode & 0x0C) << 1) | clock_mode;
}
