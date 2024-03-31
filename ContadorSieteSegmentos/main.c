/******************************************************
 * main.c
 *
 * Program Name:  Practica3
 *         Date:  2020-09-16
 *       Author:  Miguel Montiel Martínez
 *
 *
 * Description:
 *  Este programa muestra hacer un contador simple en
 *  lenguaje C, mostrando el resultado en un display de
 *  siete segmentos, los códigos están almacenados en
 *  la SRAM
 *
 *****************************************************/
#include <avr/io.h>
#include <util/delay.h>

//Definición de macros
#define setbit(sfr,bit) (_SFR_BYTE(sfr)|=(_BV(bit)))
#define clearbit(sfr,bit) (_SFR_BYTE(sfr)&=~(_BV(bit)))
#define togglebit(sfr,bit) (_SFR_BYTE(sfr)^=_BV(bit)) /**<Cambia el estado de bit*/

//definición de macros para direccionar puertos
#define DDR(x) (*(&x -1)) ///< direcciona al puerto de configuracion
#define PIN(x) (*(&x -2)) ///< direcciona al puerto de lectura

#define seg_a PB7
#define seg_b PB6
#define seg_c PB5
#define seg_d PB4
#define seg_e PB3
#define seg_f PB2
#define seg_g PB1

#define boton PD2
#define Pboton PORTD

//Funciones de C
void AVRInit();
unsigned char display(int numero);

int main()
{
	int contador = 0;
	unsigned char valor = 0;
	AVRInit();
  PORTB = 0xFF;
	// Infinite loop
	while(1)
	{
		if(bit_is_clear(PIN(Pboton),boton))
		{
			_delay_ms(40);
			if(bit_is_clear(PIN(Pboton), boton))
			{
				valor = display(contador);
				contador++;
				if(contador > 9)
				{
					contador = 0;
				}
				PORTB = ~(valor);
				while(bit_is_clear(PIN(Pboton),boton));
			}
		}
	}

	return 0;
}


void AVRInit()
{
	// define salidas
	DDRB = 0xFF;
	// define entrada
	clearbit(DDR(Pboton),boton);
	setbit(Pboton,boton);
}


unsigned char display(int numero)
{
	unsigned char out = 0x00;
	switch(numero)
	{
		case 0: out = 0xfc; break;
		case 1: out = 0x60; break;
		case 2: out = 0xda; break;
		case 3: out = 0xf2; break;
		case 4: out = 0x66; break;
		case 5: out = 0xb6; break;//1011 0110
		case 6: out = 0xbe; break;
		case 7: out = 0xe0; break;
		case 8: out = 0xfe; break;
		case 9: out = 0xf6; break;
		default: out = 0x00;
	}
	return out;
}
