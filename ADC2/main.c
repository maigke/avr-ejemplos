/******************************************************
 * main.c
 *
 * Program Name:  ADC2
 *         Date:  2020-05-15
 *       Author:  YOUR_NAME
 *      License:  YOUR_LICENSE
 *
 * Description:
 *  Programa que lee el ADC canal 3 usando el voltajes
 *	de referencia y lo envia por el puerto serie en
 *	formatos entero y flotante.

 *	Se almacena el valor en una memoria 24AA512
 *
 *****************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <uart.h>
#include <i2cmaster.h>

//macros para setear
#define setbit(sfr,bit) (_SFR_BYTE(sfr)) |= (_BV(bit))
#define clrbit(sfr,bit) (_SFR_BYTE(sfr)) &=~(_BV(bit))
#define togglebit(sfr,bit) (_SFR_BYTE(sfr)) ^= (_BV(bit))

#define Dev24AA512		0xA6  //Direccion de la memoria EEPROM
//define el tamano del buffer
#define lenbuff 15

//variables para el manejo de comunicacion serial
volatile bool flagcommand= false;
unsigned char xbuff=0x00;
char cbuff[lenbuff];


void AVRInit();

void adc_setup(void);
unsigned int adc_read(char channel);
void write2EEPROM(unsigned char data, unsigned int direccion);
unsigned char read2EEPROM(unsigned int direccion);


void menu(void);
void comando(void);
/**
* funcion que limpia el buffer de caracteres para la comunicacion serial
*/
void initBuff(void);
/**
* funcion para agregar un caracter al buffer de comunicacion serial
*/
void add2cbuff(unsigned char c);

/**
* funcion que imprime un echo a la terminal, solo caracteres imprimibles
*/
void echosel(unsigned char c);


volatile char rcvchar;
//interrupciones
ISR(USART_RX_vect)
{
    rcvchar = 0x00;     //Se inicializa el caracter recibido

    rcvchar = UDR0;//Se lee el buffer de recepcion
    add2cbuff(rcvchar); //se agrega al buffer de comando
    echosel(rcvchar);   //Se envia un eco hacia la PC
		togglebit(PORTB, PB0);
}

int main()
{
	unsigned int n; char buff[8]; //valor binario ADC

	AVRInit();
	initBuff();
	menu();

	// Infinite loop
	while(1)
	{

		if(flagcommand)
		{
			comando();
			togglebit(PORTB, PB0);
      flagcommand = false;
		}

	}

	return 0;
}

void AVRInit()
{
	//led para latido
	setbit(DDRB, PB0);
	setbit(PORTB, PB0);

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

	i2c_init();

	//habilitando las interrupciones
	setbit(UCSR0B, RXCIE0);
	sei();
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


void write2EEPROM(unsigned char data, unsigned int direccion)
{
	unsigned char dirh, dirl;
	dirh = (unsigned char) (direccion >> 8);
	dirl = (unsigned char) (direccion);
	i2c_start_wait(Dev24AA512 + I2C_WRITE);
	i2c_write(dirh);
	i2c_write(dirl);
	i2c_write(data);
	i2c_stop();
	_delay_ms(2);
}

unsigned char read2EEPROM(unsigned int direccion)
{
	unsigned char leido, dirh, dirl;
	dirh = (unsigned char) (direccion >> 8);
	dirl = (unsigned char) (direccion);
	i2c_start_wait(Dev24AA512 + I2C_WRITE);
	i2c_write(dirh);
	i2c_write(dirl);
	i2c_rep_start(Dev24AA512 + I2C_READ);
	leido = i2c_readNak();
	i2c_stop();
	return leido;
}


void menu(void)
{
	_delay_ms(30);
	uart_puts("\r\n");
	uart_puts("EEPROM I2C\r\n");
	uart_puts("CONTROL DE BUFFER\r\n\n");
	uart_puts("[ENTER] Procesa comando\r\n");
	uart_puts("[ESC] Borra todo el buffer\r\n");
	uart_puts("[DEL] Borra el ultimo caracter del buffer\r\n\n");

	uart_puts("Comandos EEPROM\r\n\n");
	uart_puts("/? Presenta menu\r\n");
	uart_puts("/B Formatea la EEPROM iniciando a 0\r\n");
	uart_puts("/r Lee el contenido completo de la EEPROM en RS232\n\r");
	uart_puts("/w <dat> Escribe la EEPROM a partir de indice\n\r");
	uart_puts("/i <dir> Coloca el indice de la EEPROM a 0xdir sin borrar contenido\r\n");

}


void comando(void)
{
	int i,j,u,h;
	unsigned char hh,hl; //variables para extraer la dir de memoria
	bool flagValido =  false;
	char buffer[5];
  char buf[lenbuff];
	char arg[lenbuff];
	clrbit(UCSR0B, RXCIE0);  //no admite recepcion de nuevo comando

	for(i=0; i< lenbuff; i++){
        arg[i]= 0x00;
    }

		//Código para procesar /?
    if(cbuff[0]=='/' && cbuff[1]=='?'){
        flagValido = true;
        menu();
    }

    //Codigo para procesar /B
    if(cbuff[0]=='/' && cbuff[1]=='B'){
        flagValido = true;
        uart_puts("\r\nFormateando");
        j=0;
        for(j=0;j<0x10000;j++){
            write2EEPROM(0x00,i);
        }
        //Escribiendo la direccion indice
        write2EEPROM(0x00,0);
        write2EEPROM(0x02,1);
    }


		//Codigo para procesar /r
    if(cbuff[0]=='/' && cbuff[1]=='r'){
        flagValido = true;
        for(i=0; i<16;i++){
            sprintf(buffer,"%X",i);
            uart_puts(buffer);
        }
        uart_puts("\r\n");

        for(j=0; j<16;j++)
            uart_puts("==");
        uart_puts("\r\n");

        for(i=0;i<0x10000;i++){
            u = read2EEPROM(i);
            sprintf(buffer,"%X",u);
            uart_puts(buffer);
        }
        uart_puts("\r\n\r\n");
    }


		//Procesar comando /w dat
    if(cbuff[0]=='/' && cbuff[1]=='w'){
        flagValido = true;
        i=3;//Se estrae la cadena a escribir n la eeprom
        do{
            arg[i-3] = cbuff[i];
        }while(cbuff[++i]!=0x00);

        hh = read2EEPROM(0x0000);
        hl = read2EEPROM(0x0001);
        h = hh<<8;
        h = h|hl;
        uart_puts("Escribir ");
        uart_puts(arg);
        uart_puts(" a partir de ");
        sprintf(buffer,"%X",h);
        uart_puts(buffer);
        uart_puts("\r\n\r\n");
        i=0;
        do{
            write2EEPROM(arg[i],h);
            ++h;//colocate en la siguinte direccion
            ++i;//escribe el siguiente caracter en dat
        }while(arg[i]!=0x00);

        //actualizar el indice
        --h;
        hh=(unsigned char) (h>>8);
        hl=(unsigned char) (h);

        write2EEPROM(hh,0x0000);
        write2EEPROM(hl,0x0001);

        uart_puts("Buffer escrito\r\n\r\n");
    }


		//procesando comando /i dir
    //la direccion se procesa como hexadecimal
    if(cbuff[0]=='/' && cbuff[1]=='i'){
        flagValido =  true;
        i=3;
        do{
            arg[i-3] = cbuff[i];
        }while(cbuff[++i]!=0x00);

        h= (16*ascii2hex(arg[1]) + (ascii2hex(arg[0])) +
            (16*16*ascii2hex(arg[2])) +
            (16*16*16*ascii2hex(arg[3])));

        //Se calcula la direccion a partir de lo recibido

        //Se escribe el nuevo indice
        hh=(unsigned char) (h>>8);
        hl=(unsigned char) (h);
        write2EEPROM(hh,0x0000);
        write2EEPROM(hl,0x0001);

    }


		if(flagValido == false){
        uart_puts("¿");
        //sprintf(buf,"%x",cbuff);
        //uart_puts(buf);
				uart_puts(cbuff);
        uart_puts("?");
    }
    initBuff();
    setbit(UCSR0B,RXCIE0);
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
			  TransmitByte(RETROCESO);
        break;
    case ESCAPE:
        TransmitByte(ESCAPE);
        break;
    default:
        TransmitByte(c);
    }
}
