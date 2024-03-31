#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "keyb.h"

extern char keyMap[4][4];

uint8_t Leeteclado()
{
	uint8_t tiempo = 20;
	uint8_t c; //columnas - In
	uint8_t r; //renglones - Out
	uint8_t val=16;
	DDRB = 0x0F;
	PORTB |= 0xF0;
	PORTB |= 0x0F; //Pone en alto las filas del keypad
	for(r = 0; r < 4; r++)
	{
		PORTB &=~(1<<r); //se escribe un cero al renglon i esimo
		for(c = 0; c < 4; c++)
		{
			if( (PINB & (1<<(c+4)))== 0)
			{
				val = (r<<2) + c;
			}
			while( (PINB &(1 <<(c+4))) == 0);
			xdelay_ms(tiempo);
		}
		PORTB |= (1<<r);  //se restaura el uno
	}
	 PORTB |= 0x0F; //Pone en alto las filas del keypad
	 return val;
}


char KeyMap(uint8_t val)
{
    uint8_t cc,rr;
    char car;
    cc = val%4;
    rr = (val - cc)>>2;
    car =  keyMap[rr][cc];
    return car;
}

void xdelay_ms(int valor)
{
	for( int i = 0; i < valor; i++)
		_delay_ms(1);
}
