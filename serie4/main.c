/******************************************************
 * main.c
 *
 * Program Name:  serie3
 *         Date:  2021-05-28
 *       Author:  Miguel Montiel
 *      License:  YOUR_LICENSE
 *
 * Description:
 *  El formato del comando para este programa es
 *  5-xx  donde 5 da inicio a la toma de lecturas y
 *        xx representa al valor de set
 *****************************************************/
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
	#include <stdbool.h>
  #include <avr/io.h>
  #include <util/delay.h>
  #include <avr/interrupt.h>


	//definicion de teclas
	#define INTRO 0x0D
	#define RETROCESO 0x08
	#define ESCAPE 0x1B

	//define el tamano del buffer
	#define lenbuff 10


  bool flagcommand = false;
	char xbuff=0x00;
	char cbuff[lenbuff];
	char rcvChar = 0x00;

  char mando[]={0};
  float temperatura = 25.0;


  void AVRInit();
  void adc_setup();
  unsigned int adc_read(char channel);




  void uart_init(unsigned char baudrate);
  unsigned char uart_receive(void);
  void uart_transmit(unsigned char data);
  void uart_puts(const char *s);
	int uart_dataAvailable(void);
	void initBuff(void);
	void add2cbuff(unsigned char c);
	void echosel(unsigned char c);


  void comando(void);

/*Interrupciones*/
ISR(USART_RX_vect)
{
	rcvChar = 0x00;
	rcvChar = UDR0;
	add2cbuff(rcvChar);
	echosel(rcvChar);
  PORTB^=(1<<PB0);
}


  int main()
  {

  	unsigned char n=0;
  	char buff[4]; //valor binario del ADC
  	char buff2[6]; //valor de voltaje del ADC

  	// Initialize the AVR modules
  	AVRInit();
    PORTD &= ~(1<<PD2); //Relevador OFF
  	// Infinite loop
  	while(1)
  	{
      if(flagcommand)
      {
        comando();
        uart_puts(mando);uart_puts("\n\r");
        sprintf(buff,"%.2f",temperatura);
        uart_puts(buff);uart_puts("\n\r");
        uart_puts("------------\n\r");
        if (mando[0] == 'a')

        {
          n = adc_read(5);
      		sprintf(buff,"%d",n);
      		uart_puts("\n\r v:"); uart_puts(buff);
      		sprintf(buff2,"%.4f",n*5.0/255);
      		uart_puts("\n\r r:"); uart_puts(buff2);
          if( n*5.0/255 <= temperatura )
            PORTD |= (1<<PD2);  //Relevador  ON
          else
            PORTD &= ~(1<<PD2); //Relevador OFF
        }
     		else if(mando[0] == 'b')
     			PORTD &= ~(1<<PD2); //Relevador OFF

      }
  	}

  	return 0;
  }


  void AVRInit()
  {
  	uart_init(103);
  	DDRD |= (1 <<PD1); //TX
  	DDRD &= ~(1<<PD0); //RX
  	adc_setup();
  	DDRB |= (1<< PB0);//Terminal para led
 	  DDRD |= (1<<PD2); //Terminal para habilitar el rele
    PORTD &= ~(1<<PD2);

    //habilitación de Interrupciones
    //del puerto serie
    UCSR0B|= (1<<RXCIE0);
    sei();

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

  unsigned char uart_receive(void)
  {
  	while (!(UCSR0A &(1<<RXC0))) {
  		/* code */
  	}
  	return UDR0;
  }

  void uart_transmit(unsigned char data)
  {
  	while(!(UCSR0A &(1<<UDRE0)));
  	UDR0 = data;
  }

  void uart_puts(const char *s)
  {
  	while(*s)
  	{
  		uart_transmit(*s);
  		s++;
  	}
  }

	int uart_dataAvailable(void)
  {
    if ( UCSR0A & ( 1 << RXC0) )
        return 1;

    return 0;
}


	void initBuff(void)
	{
	    int i;
	    for(i=0;i<lenbuff; i++)
	    {
	        cbuff[i]=0x00;
	    }xbuff=0x00;
	}

	void add2cbuff(unsigned char c)
	{
	    if(xbuff<lenbuff)
	    {
	        switch(c)
	        {
	        case INTRO:
	            flagcommand = true;
	            break;
	        case RETROCESO:
	            if(xbuff>0) cbuff[--xbuff] = 0x00;
	            break;
	        case ESCAPE:
	            initBuff();
	            break;
	        default:
	            cbuff[xbuff++]=c;
	        }
	    }
	    else
	    {
	        initBuff();
	        uart_puts("ERROR\r\n");
	    }
	}

	void echosel(unsigned char c)
	{
	    switch(c)
	    {
	    case INTRO:
	        uart_puts("\r\n");
	        break;
	    case RETROCESO:
	        uart_transmit(RETROCESO);
	        break;
	    case ESCAPE:
	        uart_transmit(ESCAPE);
	        break;
	    default:
	        uart_transmit(c);
	    }
	}


/*
* El formato del comando es el siguiente:

[a/b]     [12.3]
arranca   valor de ajuste
*/

	void comando(void)
	 {

	   	char temp[6];
	   	char cmd[lenbuff];
      unsigned char i= 0;
      UCSR0B &=~(1<<RXCIE0);
	   	//clrbit(UCSR0B, RXCIE0);  //no admite recepcion de nuevo comando

	    for(i=0; i< lenbuff; i++){
	           cmd[i]= 0x00;
	       }
         uart_puts("En proceso comando");
         uart_puts(cbuff);uart_puts("\n\r");
         flagcommand = false;
         strcpy(cmd,cbuff);
         strncpy(mando,cmd,1); //copia el primer caracter
         strcpy(cmd,cbuff);
         //guarda la temperatura
         for(i=1;i<5;i++)
         {
           temp[i-1]=cmd[i];
         }
         temperatura = atof(temp);
   }
