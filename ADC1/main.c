/******************************************************
 * main.c
 *
 * Program Name:  ADC1
 *         Date:  2020-05-14
 *       Author:  YOUR_NAME
 *      License:  YOUR_LICENSE
 *
 * Description:
 *  This is my program description..
 *
 *****************************************************/
#include <stdio.h>

#include <avr/io.h>
#include <util/delay.h>
#include <uart.h>



//macros para setear
#define setbit(sfr,bit) (_SFR_BYTE(sfr)) |= (_BV(bit))
#define clrbit(sfr,bit) (_SFR_BYTE(sfr)) &=~(_BV(bit))


void AVRInit();

void adc_setup(void);
unsigned int adc_read(char channel);

int main()
{
	unsigned int n; char buff[8]; //valor binario ADC


	// Initialize the AVR modules
	AVRInit();
	uart_puts("HOLAAAAAAAAAAAAA----------------------\n\r");
	uart_puts("Esta iniciando el dispositivo\n\r");
	// Infinite loop
	while(1)
	{

		n = adc_read(3);
		sprintf(buff, "%d", n);
		uart_puts(buff);		uart_puts("************\n\r");
		sprintf(buff, "%.4f",n*3.3/256);
		uart_puts(buff);		uart_puts("------------\n\r");
		_delay_ms(1000);
	}

	return 0;
}

void AVRInit()
{
	//configurando a 57600bps
	uart_init(16);
	clrbit(DDRD, PD0); //Rx
	setbit(DDRD, PD1); //Tx


	/*
	Configuracion del ADC
	1. Selecciona el reloj del ADC1
	2. Selecciona los voltajes de referencia del ADC
	3. Establece la justificacion con ADLAR para 8 bits por ejemplo
	4. Selecciona el o los canales a leer
	5. Enciende el modulo del ADC
	6. Inicia la conversion del ADC
	7. Espera a que termine la conversión del ADC1
	8. Realiza la lectura del registro ADCH:ADCL
	*/
	adc_setup();
}

void adc_setup(void)
{
	//Vref+ y Vref-   Avref y GND
	//Justificacion: A la izquierda (8 bits)
	//Canal: 3

	clrbit(ADMUX, REFS1);
	clrbit(ADMUX, REFS0);

	setbit(ADMUX, ADLAR);

	clrbit(ADMUX, MUX3);
	clrbit(ADMUX, MUX2);
	setbit(ADMUX,	MUX1);
	setbit(ADMUX, MUX0);

	//Reloj del ADC: FCPU/128 = 125kHz
	//Estado del convertidor: ON
	//Modo:  Automático

	setbit(ADCSRA, ADEN);  //ADC habilitadi
	setbit(ADCSRA, ADATE); //Autodisparo habilitado

	setbit(ADCSRA, ADPS2); //Frecuencia de ADC 125kHz
	setbit(ADCSRA, ADPS1);
	setbit(ADCSRA, ADPS0);
}

unsigned int adc_read(char channel)
{
	ADMUX &= 0xF8;
	ADMUX |= channel; //selecciona el canal
	_delay_us(10); //delay para estabilizar el voltaje a la entrada del ADC
	setbit(ADCSRA, ADSC); //Arranca el ADC

	while(bit_is_clear(ADCSRA,ADIF));
	return ADCH;
}
