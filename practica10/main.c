/******************************************************
 * main.c
 *
 * Program Name:  practica10
 *         Date:  2020-11-08
 *       Author:  YOUR_NAME
 *      License:  YOUR_LICENSE
 *
 * Description:
 *  This is my program description..
 *
 *****************************************************/
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <clk.h>
#include <timer0/timer0.h>
#include <lcdlibrary/lcd.h>


volatile char contador=49;
ISR(INT0_vect)
{
	OCR0A=contador++;
}

ISR(INT1_vect)
{
	OCR0A=contador--;
}

void AVRInit();

int main()
{

	char buffer[5];
	char oldContador= 0;
	// Initialize the AVR modules
	AVRInit();
	lcd_puts("Frecuencia:\n");
	itoa(contador,buffer,10);
	lcd_puts(buffer);
	oldContador = contador;
	// Infinite loop
	while(1)
	{
		togglebit(PORTD,PD6);
		if(oldContador != contador)
		{
			lcd_gotoxy(0,1);
			lcd_puts("   ");
			lcd_gotoxy(0,1);
			itoa(contador,buffer,10);
			lcd_puts(buffer);
			oldContador = contador;
		}
	}

	return 0;
}


void AVRInit()
{

	// AVR Initialization
	lcd_init(LCD_DISP_ON_CURSOR);
	//configuracion del timer0 para generar una onda cuadrada
	// Modo de operacion: CTC
	// Factor de preescalamiento:1
	// OCR:49
	// Periodo deval autoreset: 50 us
	// F_CPU: 1MHz
	// F_base: 10kHz =>  100us
	OCR0A = contador;
	timer0_setup(2,1,0,1);
	//habilitando interrupciones

MCUCR = (1 << ISC00) | (1 << ISC01);
	//Se declaran como entradas a los pines para controlar la frecuencia
	clrbit(DDRD,PD2);
	clrbit(DDRD,PD3);
	setbit(PORTD,PD2);
	setbit(PORTD,PD3);

	//Salida para la frecuencia
  setbit(DDRD,PD5);
  setbit(DDRD,PD6);
	//habilita las interrupciones externas
	GIMSK = (1 << INT0) | (1 << INT1);
	//en flanco de subida
	MCUCR = (1 << ISC00) | (1 << ISC01);
	MCUCR = (1 << ISC10) | (1 << ISC11);
	sei();

}
