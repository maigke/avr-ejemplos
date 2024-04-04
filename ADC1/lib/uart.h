#ifndef UART_H
#define UART_H
void uart_init(unsigned char baudrate);
unsigned char ReceiveByte(void);
void TransmitByte(unsigned char data);
void uart_puts(const char *s);
#endif // UART_H
