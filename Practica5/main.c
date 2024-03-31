/******************************************************
 * main.c
 *
 * Program Name:  Practica5
 *         Date:  2020-09-25
 *       Author:  YOUR_NAME
 *      License:  YOUR_LICENSE
 *
 * Description:
 *  This is my program description..
 *
 *****************************************************/
#include <avr/io.h>
#include <util/delay.h>
#include <src/clk.h>
#include <src/pines.h>


/*********************************************
Definicion de Estados
*********************************************/
#define DETENIDO 0
#define DERECHA 1
#define IZQUIERDA 2


void AVRInit();

int main()
{
	// Initialize the AVR modules
	unsigned char ESTADO =  DETENIDO;
	AVRInit();
	//Condiciones iniciales
	clrbit(Pa,a); clrbit(Pb,b); clrbit(PEn,En);

	// Infinite loop
	while(1)
	{
		switch(ESTADO)
		{
			case DETENIDO:
			{

				if(bit_is_clear(PIN(Pstart),start) && bit_is_set(PIN(Pstop),stop) && bit_is_clear(PIN(PI_nD), I_nD))
				{
					ESTADO = DERECHA;
					setbit(Pa,a);clrbit(Pb,b);setbit(PEn,En);
				}
				if(bit_is_clear(PIN(Pstart),start) && bit_is_set(PIN(Pstop),stop) && bit_is_set(PIN(PI_nD), I_nD))
				{
					ESTADO = IZQUIERDA;
					clrbit(Pa,a);setbit(Pb,b);setbit(PEn,En);
				}
			}break;
			case DERECHA:
			{
				if(bit_is_set(PIN(Pstart),start) && bit_is_clear(PIN(Pstop),stop) && bit_is_clear(PIN(PI_nD), I_nD))
				{
					ESTADO = DETENIDO;
					clrbit(Pa,a);clrbit(Pb,b);clrbit(PEn,En);
				}
			}break;
			case IZQUIERDA:
			{
				if(bit_is_set(PIN(Pstart),start) && bit_is_clear(PIN(Pstop),stop) && bit_is_set(PIN(PI_nD), I_nD))
				{
					ESTADO = DETENIDO;
					clrbit(Pa,a);clrbit(Pb,b);clrbit(PEn,En);
				}
			}
		}

	}

	return 0;
}

void AVRInit()
{
	// Configuracion de las entradas
	clrbit(DDR(Pstart),start);
	clrbit(DDR(Pstop), stop);
	clrbit(DDR(PI_nD), I_nD);
	//Configuracion de las resistencias de pull up
	setbit(Pstart, start);
	setbit(Pstop, stop);
	setbit(PI_nD, I_nD);
	//Configuracion de salidas
	setbit(DDR(Pa), a);
	setbit(DDR(Pb), b);
	setbit(DDR(PEn),En);
}
