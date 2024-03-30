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

Este programa lee las terminales PD3 y PD2
las salidas son PD7 y PB0

se considera la siguiente tabla de verdad

PD2  PD3 | PD6[rojo]  PB0[verde]
---------+-------------------------
1      1 |   0          1   Verde
1      0 |   1          0   Rojo
0      1 |   1          1   Naranja
0      0 |   0          0   Apagado

Las salidas se conectan a un led bicolor 
conectadas las salidas PD7 t PB0

 * 
 *****************************************************/
#include <avr/io.h> 
#include <util/delay.h> 

/**
* @name Macros para sustituir el seteo de bits individuales
*/
#define setbit(sfr,bit) (_SFR_BYTE(sfr)|=_BV(bit))    /**<Pone en set un bit*/
#define clrbit(sfr,bit) (_SFR_BYTE(sfr)&=~_BV(bit))   /**<Pone en clear un bit*/
#define togglebit(sfr,bit) (_SFR_BYTE(sfr)^=_BV(bit)) /**<Cambia el estado de bit*/
#define DDR(x) (*(&x -1)) ///< direcciona al puerto de configuracion
#define PIN(x) (*(&x -2)) ///< direcciona al puerto de lectura

void AVRInit()
{
	// AVR Initialization
	// Configuracion de puertos
	// Entradas
	DDRD &= ~(1<< DDD3);
	DDRD &= ~(1<< DDD2);
	//Salidas
	DDRD |= (1 << DDD6);
	DDRB |= (1 << DDB0);


}

int main()
{
	// Initialize the AVR modules
	AVRInit();
	clrbit(PORTD,PD6);
	setbit(PORTB,PB0);
	// Infinite loop
	while(1)
	{
		if(bit_is_clear(PIND, PD3) && bit_is_set(PIND, PD2))
		{
			_delay_ms(20);
			if(bit_is_clear(PIND, PD3) && bit_is_set(PIND, PD2))
			{
				setbit(PORTD,PD6);
				clrbit(PORTB,PB0);
				while(bit_is_clear(PIND,PD3) &&
				bit_is_set(PIND, PD2));
			}
		}
		
		else if(bit_is_set(PIND, PD3) && bit_is_clear(PIND, PD2))
		{
			_delay_ms(20);
			if(bit_is_set(PIND, PD3) && bit_is_clear(PIND, PD2))
			{
				setbit(PORTD,PD6);
				setbit(PORTB,PB0);
				while(bit_is_set(PIND,PD3) &&
				bit_is_clear(PIND, PD2));
			}
		}
		
		else if(bit_is_clear(PIND, PD3) && bit_is_clear(PIND, PD2))
		{
			_delay_ms(20);
			if(bit_is_clear(PIND, PD3) && bit_is_clear(PIND, PD2))
			{
				clrbit(PORTD,PD6);
				clrbit(PORTB,PB0);
				while(bit_is_clear(PIND,PD3) &&
				bit_is_clear(PIND, PD2));
			}
		}
		
		else 
		{
			
			clrbit(PORTD,PD6);
			setbit(PORTB,PB0);
			
		}
		

	}

	return 0;
}
