#ifndef UART_H
#define UART_H

//definicion de teclas
#define INTRO 0x0D
#define RETROCESO 0x08
#define ESCAPE 0x1B

void uart_init(unsigned char baudrate);
unsigned char ReceiveByte(void);
void TransmitByte(unsigned char data);
void uart_puts(const char *s);
int ascii2hex(char d);
int uart_dataAvailable(void);
#endif // UART_H
