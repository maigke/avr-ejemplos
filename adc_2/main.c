/******************************************************
 * main.c
 *
 * Program Name:  adc_2
 *         Date:  2021-05-03
 *       Author:  YOUR_NAME
 *      License:  YOUR_LICENSE
 *
 * Description:
 *  This is my program description..
 *
 *****************************************************/
#include <stdio.h>
#include <stdlib.h>

#include <avr/io.h>
#include <util/delay.h>


void AVRInit();
void adc_setup();
unsigned int adc_read(char channel);




void uart_init(unsigned char baudrate);
unsigned char ReceiveByte(void);
void TransmitByte(unsigned char data);
void uart_puts(const char *s);


int main()
{

	unsigned char n=0;
	char buff[4]; //valor binario del ADC
	char buff2[6]; //valor de voltaje del ADC

	// Initialize the AVR modules
	AVRInit();
  uart_puts("ADC5:\n");
	// Infinite loop
	while(1)
	{

		n = adc_read(5);
		sprintf(buff,"%d",n);
		uart_puts("\n\r v:"); uart_puts(buff);
		sprintf(buff2,"%.4f",n*5.0/255);
		uart_puts("\n\r r:"); uart_puts(buff2);
		PORTB |= (1<<PB0);
		_delay_ms(500);
		PORTB &= ~(1<<PB0);
	}

	return 0;
}


void AVRInit()
{
	uart_init(103);
	DDRD |= (1 <<PD1); //TX
	DDRD &= ~(1<<PD0); //RX
	adc_setup();
	DDRB |= (1<< PB0);


}

void adc_setup()
{
	/* Referencia en AVcc*/
	ADMUX &= ~(1 << REFS1);
	ADMUX |= 1 << REFS0;

	/*Justificacion a la izquieda Resolucion 8 bits*/
	ADMUX |= (1 << ADLAR);

	/*Canal a leer por defecto*/
	/* No es necesario realizar esta acción */

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
	16MHz/128 = 125kHz
	Estado del ADC: ON
	Modo: Manuel
	*/
	ADCSRA |= (1<<ADEN);
	ADCSRA &= ~(1<< ADATE);

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

void uart_init(unsigned char baudrate)
{
	UBRR0 = baudrate;
	UCSR0B = (1 << RXEN0) | (1<<TXEN0);
	UCSR0C = (3 << UCSZ00);
}

unsigned char ReceiveByte(void)
{
	while (!(UCSR0A &(1<<RXC0))) {
		/* code */
	}
	return UDR0;
}

void TransmitByte(unsigned char data)
{
	while(!(UCSR0A &(1<<UDRE0)));
	UDR0 = data;
}

void uart_puts(const char *s)
{
	while(*s)
	{
		TransmitByte(*s);
		s++;
	}
}
