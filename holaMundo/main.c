/***
Este programa lee las terminales PD3 y PD2
las salidas son PD7 y PB0

se considera la siguiente tabla de verdad

PD2  PD3 | PD7[rojo]  PB0[verde]
---------+-------------------------
1      1 |   0          1   Verde
1      0 |   1          0   Rojo
0      1 |   1          1   Naranja
0      0 |   0          0   Apagado

Las salidas se conectan a un led bicolor 
conectadas las salidas PD7 t PB0
*/

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{

// Configuracion de puertos
// Entradas
	DDRD &= ~(1<< DDD3);
	DDRD &= ~(1<< DDD2);
//Salidas
	DDRD |= (1 << DDD7);
	DDRB |= (1 << DDB0);

	PORTD &= ~(1 << PD7);
	PORTB |= (1 << PB0);

	while(1)
	{	
		if (!(PIND &(1<<PD3)) && (PIND & (1<<PD2)))
		{
			PORTD|=(1<<PD7);
			PORTB&=~(1<<PB0);
		}
		else if ((PIND&(1<<PD3)) && !(PIND & (1<<PD2)))
		{
			PORTD|=(1<<PD7);
			PORTB|=(1<<PB0);
		}
		else if (!(PIND&(1<<PD3)) && !(PIND &(1 <<PD2)))
		{
			PORTD&=~(1<<PD7);
			PORTB&=~(1<<PB0);
		}
		else
		{
			PORTD&=~(1<<PD7);
			PORTB|=(1<<PB0);
		}
	}
return 0;
}
