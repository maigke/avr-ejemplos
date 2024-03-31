/******************************************************
 * main.c
 *
 * Program Name:  tecladoInt
 *         Date:  2021-04-03
 *       Author:  YOUR_NAME
 *      License:  YOUR_LICENSE
 *
 * Description:
 *  This is my program description..
 *
 *****************************************************/
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <lcd/lcd.h>


void AVRInit();
uint8_t LeeTeclado();
void delay_ms(int valor);

volatile uint8_t flag = 0;

ISR(PCINT_vect)
{
	flag = 1;
}

int main()
{
	uint8_t val = 16;
	// Initialize the AVR modules
	AVRInit();
	lcd_home();
	lcd_puts("Interrupciones");
	sei();

	// Infinite loop
	while(1)
	{
			if(flag)
			{
				cli();//inhabilita Interrupciones
				val = LeeTeclado();
				lcd_gotoxy(5,1);
				if(val < 10)
					lcd_putc(0x30 + val);
				else if((val > 9) && (val < 16))
					lcd_putc(0x57 + val);
				else
					lcd_putc(' ');

				flag = 0;
				delay_ms(100);
				sei();
			}
	}

	return 0;
}

void AVRInit()
{
	// AVR Initialization
	GIMSK |= (1 << PCIE);

	PCMSK = (1<<PCINT7 | 1<<PCINT6 | 1<<PCINT5 | 1<<PCINT4);

	lcd_init(LCD_DISP_ON_CURSOR_BLINK);
	DDRB = 0x0F;
	PORTB |= 0xF0;
	PORTB |= 0x0F;
}

uint8_t LeeTeclado()
{
	uint8_t tiempo = 10,c,r,val = 0;
	DDRB = 0x0F;
	PORTB |= 0xF0;
	PORTB |= 0x0F;

	for( r= 0; r < 4; r++)
	{
		PORTB &= ~(1 << r);
		delay_ms(tiempo);
		for( c = 0; c < 4; c++)
		{
			if( (PINB & (1 << (c + 4))) == 0)
			{
				val = (r << 2) + c;
			}
			while( (PINB & (1<<(c + 4))) == 0);
			delay_ms(tiempo);
		}
		PORTB |= (1 << r);
	}
	PORTB |= 0x0F;
	return val;
}

void delay_ms(int valor)
{
	for( int i = 0; i < valor; i++)
		_delay_ms(1);
}
