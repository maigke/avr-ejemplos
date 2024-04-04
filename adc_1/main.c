/******************************************************
 * main.c
 *
 * Program Name:  adc_1
 *         Date:  2021-05-02
 *       Author:  YOUR_NAME
 *      License:  YOUR_LICENSE
 *
 * Description:
 *  This is my program description..
 *  Para imprimir los puntos decimales con sprintf
 *  poner esto en Makefile
 *  -Wl,-u,vfprintf -lprintf_flt -lm
 *
 *****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <lcd/lcd.h>

void AVRInit();
void adc_setup();
unsigned int adc_read(char channel);


int main()
{
	unsigned char n=0;
	char buff[4]; //valor binario del ADC
	char buff2[6]; //valor de voltaje del ADC

	// Initialize the AVR modules
	AVRInit();
	lcd_gotoxy(5,0);
	lcd_puts("ADC5:");
	// Infinite loop
	while(1)
	{
		n = adc_read(5);
		lcd_gotoxy(1,1);
		itoa(n,buff,10);
		lcd_puts("v:");lcd_puts(buff);
		sprintf(buff2,"%.3f",n*5.0/255);
		lcd_puts(" r=");lcd_puts(buff2);
		_delay_ms(200);
		PORTB |= (1<<PB0);
		_delay_ms(200);
		PORTB &= ~(1<<PB0);

	}

	return 0;
}

void AVRInit()
{
	// AVR Initialization
	lcd_init(LCD_DISP_ON_CURSOR_BLINK);
	adc_setup();
	lcd_home();
	DDRB |= (1<< PB0);
}

void adc_setup()
{
	/**
	Configuracion del reloj del ADC

	Reloj: 125kHz

	ADPS2 ADPS1  ADPS0    Divisor
	0       0     0         2
	0       0     1         2
	0       1     0         4
	0       1     1         8
	1       0     0        16
	1       0     1        32
	1       1     0        64
	1       1     1       128

	Por ejemplo Si F_CPU = 16MHz    con ADPS[2..0]= 3
	Entonces la frecuencia de conversion es
	16MHz/128 = 125kHz*/

  
	/* Referencia en AVcc*/
	ADMUX &= ~(1 << REFS1);
	ADMUX |= 1 << REFS0;

	/*Justificacion a la izquieda Resolucion 8 bits*/
	ADMUX |= (1 << ADLAR);

	/*Canal a leer por defecto*/
	/* No es necesario realizar esta acción */


	/*
	Estado del ADC: ON
	Modo: Manual
	*/
	ADCSRA |= (1<<ADEN);
	ADCSRA &= ~(1<< ADATE); //Si este bit es 1 hay conversion AUTO
  ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}

unsigned int adc_read(char channel)
{
	ADMUX &= 0xFF;
	ADMUX |= channel;
	_delay_us(10); //delay para estabilizar el voltaje de entrada del ADC
	ADCSRA |= (1<<ADSC); //Inicia la conversion

	while(bit_is_clear(ADCSRA,ADIF));
	return ADCH;
}
