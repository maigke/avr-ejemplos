/******************************************************
 * main.c
 *
 * Program Name:  tecladoInt2
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
#include <clk/clk.h>
#include <lcd/lcd.h>
#include <keyb/keyb.h>
/*Esta mascara debe ser incluida cuando se llama a */
 char keyMap[4][4]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}};

void AVRInit();
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
	lcd_puts("Interrupciones 2");
	sei();

	// Infinite loop
	while(1)
	{
        if(flag)
			{
				cli();//inhabilita Interrupciones
				val = Leeteclado();
				lcd_gotoxy(5,1);
				if(val < 10)
                {
                    lcd_putc(0x30 + val);
                    lcd_putc(' ');
                    lcd_putc(KeyMap(val));
                }
					
				else if((val > 9) && (val < 16))
                {
                    lcd_putc(0x57 + val);
                    lcd_putc(' ');
                    lcd_putc(KeyMap(val));
                }
					
				else
                {
                    lcd_gotoxy(5,1);
					lcd_puts("   ");
                }
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
