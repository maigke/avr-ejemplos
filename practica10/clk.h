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

#define F_CPU 16000000L ///< Frecuencia de 16MHz
#if F_CPU == 16000000L
#define ADC_PRESCALER 0x07  ///<Factor de division 128  F_ADC = 125kHz*/
#define CPU_PRESCALER 0x00
#elif F_CPU == 8000000L
#define ADC_PRESCALER 0x06  ///<Factor de division 64   F_ADC = 125kHz*/
#define CPU_PRESCALER 0x01
#elif F_CPU == 4000000L
#define ADC_PRESCALER 0x05  ///<Factor de division 32*/
#define CPU_PRESCALER 0x02
#elif F_CPU == 2000000L
#define ADC_PRESCALER 0x04  ///<Factor de division 16*/
#define CPU_PRESCALER 0x03
#elif F_CPU == 1000000L
#define ADC_PRESCALER 0x03  ///<Factor de division 8*/
#define CPU_PRESCALER 0x04
#else
#error "Teensyduino only supports 16, 8, 4, 2, 1 MHz.  Please edit boards.txt"
#endif



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

void _init_Teensyduino_internal_(void);


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

