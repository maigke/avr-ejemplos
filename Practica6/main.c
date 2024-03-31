/******************************************************
 * main.c
 *
 * Program Name:  Practica6
 *         Date:  2020-10-09
 *       Author:  Miguel Montiel Martinez
 *      License:  YOUR_LICENSE
 *
 * Description:
 *  Este programa permite mover un motor
 *
 *****************************************************/
#include <avr/io.h>
#include <util/delay.h>
#include <clk.h>
#include <pines.h>

void AVRInit();
void gira();
void ActivaSalida(unsigned char paso);


unsigned char const pasos[]={0x0E, 0x0D, 0x0B, 0x07};

int main()
{
	int i;
	// Initialize the AVR modules
	AVRInit();
	while(1)
	{
			if(bit_is_clear(PIN(Pmarcha),Marcha))
			{
				delay_ms(10); //antirrebotes
				if(bit_is_clear(PIN(Pmarcha),Marcha))
				{
					setbit(Pen1, en1); //habilita el motor
					setbit(Pen2, en2);
					if(bit_is_clear(PIN(Pgiro),Giro))
					{ //Giro derecha
						for (i = 0; i<4; i++)
						{
							ActivaSalida(pasos[i]);
							delay_ms(250);
						}
					}
					else
					{ //giro izquierda
						for (i = 3; i >= 0; i--)
						{
							ActivaSalida(pasos[i]);
							delay_ms(250);
						}
					}
				}
			}
			else
			{
				clrbit(Pen1, en1);
				clrbit(Pen2, en2);
			}
	}

	return 0;
}

void AVRInit()
{
	// AVR Initialization
	DDRB = 0x3F;

	DDRD = 0x00;
	setbit(Pmarcha,Marcha);  //resistencias del pullup
	setbit(Pgiro, Giro);

	// mantiene detenido al motor
	PORTB = 0x00;

}

void ActivaSalida( unsigned char paso)
{
	if(paso & (1<<0)) setbit(Poin1, in1);
	else clrbit(Poin1, in1);

	if(paso & (1<<1)) setbit(Poin2, in2);
	else clrbit(Poin2, in2);

	if(paso & (1<<2)) setbit(Poin3, in3);
	else clrbit(Poin3, in3);

	if(paso & (1<<3)) setbit(Poin4, in4);
	else clrbit(Poin4, in4);

}
