#include <avr/io.h>
#include "uart.h"
#include <string.h>
#include <ctype.h>


void uart_init(unsigned char baudrate)
{
  UBRR0L = baudrate;
  UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
  UCSR0C = (1<<USBS0) | (3 << UCSZ00);
}

unsigned char ReceiveByte(void)
{
  while(!(UCSR0A & (1<<RXC0)));
  return UDR0;
}


void TransmitByte(unsigned char data)
{
  while(!(UCSR0A & (1<<UDRE0)));
  UDR0 = data;
}

void uart_puts(const char *s)
{
  while ( *s ) {
      TransmitByte(*s);
      s++;
  }
}

int ascii2hex(char d)
{
    int r = 0x00;
    if(isxdigit(d))
    {
        if(isdigit(d))
        {
            r = d-'0';
        }
        if(isalpha(d))
        {
            d = toupper(d);
            r = 10+(d-'A');
        }
    }
    return(r);
}

// check if there are any chars to be read
int uart_dataAvailable(void)
{
    if ( UCSR0A & ( 1 << RXC0) )
        return 1;

    return 0;
}
