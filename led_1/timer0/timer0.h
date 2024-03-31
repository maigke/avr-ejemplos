/**@file timer0.h
@code #include <timer0.h> @endcode

@brief
Rutina para la configuración del timer 0 de 8 bits
Este temporizador cuenta con 8 modos de operación clasificados en 4 grupos

 Normal                                        modo{0}
 CTC (limpia a la captura)                     modo{2}
 Fast PWM                                      modo{3,7}
 PWM de Fase Correcta                          modo{1,5}

*/

#ifndef TIMER0_H_INCLUDED
#define TIMER0_H_INCLUDED

/**
 *  @name  Definicion para la variable byte
 *  para usar en lugar de unsigned char
 */
#define byte uint8_t /**< definición del tipo de dato byte */


/**
 *  @name Functions
 */

/**
 @fn timer0_setup
 @brief    Ajusta los valores del temporizador 0 para sus diferentes modo y activacion
           de las terminales externas de comparación
 @param    mode Se refiere uno de los siete modos de operacion del timer
 @param    prescale Se refiere al valor de ṕrescalamiento para el temporizador
 @param    outmode_A Se refiere al comportamiento que pueden tener los bits de comparacion
           del modulo A
 @param    outmode_B Se refiere al comportamiento que pueden tener los bits de comparacion
            del modulo B
 @return   none
 
 Ejemplo:
 \verbatim
 Se pone timer en modo CTC
 con preescalamiento de 256
 y salidas en comparacion anuladas
 timer0_setup(2,256,0,0);
 \endverbatim
*/
void timer0_setup(byte mode, int prescale, byte outmode_A, byte outmode_B);

#endif // TIMER0_H_INCLUDED
