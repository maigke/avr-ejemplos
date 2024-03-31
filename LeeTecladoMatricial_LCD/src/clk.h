/** @file clk.h

@code #include <clk.h> @endcode

@brief Macros para definir la frecuencia de oscilacion del reloj
principal
*/
#ifndef CLK_H
#define CLK_H




/**
 *  @name  Definitions for MCU Clock Frequency
 *  Adapt the MCU clock frequency in Hz to your target.
 *  Revisa las paginas 37-39
 */




/**
* @name Macros para sustituir el seteo de bits individuales
*/
#define setbit(sfr,bit) (_SFR_BYTE(sfr)|=_BV(bit))    /**<Pone en set un bit*/
#define clrbit(sfr,bit) (_SFR_BYTE(sfr)&=~_BV(bit))   /**<Pone en clear un bit*/
#define togglebit(sfr,bit) (_SFR_BYTE(sfr)^=_BV(bit)) /**<Cambia el estado de bit*/
#define DDR(x) (*(&x -1)) ///< direcciona al puerto de configuracion
#define PIN(x) (*(&x -2)) ///< direcciona al puerto de lectura

/**
 *  @name Functions funciones para el microcontrolador Atmega32u4
 */


/**
 @fn _init_Teensyduino_internal_
 @brief    Funcion para inicializar los tiempos en el ATMega32U4
 @param    none
 @return   none
    Ejemplo:
    \verbatim
    _init_Teensyduino_internal_();
    \endverbatim
*/




/**
 @fn delay_ms
 @brief    Funcion para generar retardos
 @param    unsigned int time_ms en milisegundos
 @return   none
    Ejemplo:
    \verbatim
    delay_ms(1250); //Genera retardo de 1.25 seg
    \endverbatim
*/
void delay_ms(unsigned int time_ms);

/*@}*/
#endif  //end clk.h
