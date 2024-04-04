/******************************************************
 * main.c
 *
 * Program Name:  p1
 *         Date:  2020-04-08
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
#include <timer1.h>
#include <lcd.h>


#define Desbordar	PB3

volatile long valor=0;
volatile long contador = 0;
ISR(TIMER1_OVF_vect)
{
	PORTB|=(1<<Desbordar);
	_delay_us(15);
	contador++;
}

ISR(TIMER1_CAPT_vect)
{
	valor = ICR1;
}
/*
ISR(ANA_COMP_vect)
{
	PORTD^=(1<<PD2);
}
*/
void AVRInit()
{
	lcd_init(LCD_DISP_ON);
	//Pone el timer el modo Noise Canceller
	//ICNC1 = 1  - Cancelacion de ruido habilitada
	//ICES1 = 1  - deteccion en flanco de subida
	timer1_setup(0,1,0,0,3);
	DDRB|=(1<<Desbordar);
	DDRD|=(1<<PD2);
	//Configuracion del Comparador analogico
	ACSR&=~(1<<ACD); //habilita el comparador analógico
	ACSR&=~(1<<ACBG);//
	ACSR|=(1<<ACIC); //Habilita la funcion de captura en el T1
	//Habilitacion de interrupciones
	TIMSK|=(1<<TOIE1);
	TIMSK|=(1<<ICIE1); //habilita la interrupcion por captura del timer1
	sei();

}

int main()
{
	char buff[8];
	// Initialize the AVR modules
	AVRInit();

	// Infinite loop
	while(1)
	{
		PORTB&=~(1<<Desbordar);
		if(contador == 800)
		{
			lcd_gotoxy(0,0);
			lcd_puts("valor:");
			lcd_gotoxy(7,0);
			//se le suman 240 unidades para complementar los 15useg
			//del tiempo de descarga del capacitor
			itoa(valor+240, buff,16);
			lcd_puts(buff);
			contador = 0;
		}
	}

	return 0;
}
