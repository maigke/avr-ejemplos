/******************************************************
 * main.c
 *
 * Program Name:  Practica4
 *         Date:  2021-03-07
 *       Author:  YOUR_NAME
 *      License:  YOUR_LICENSE
 *
 * Description:
 *  This is my program description..
 *
 *****************************************************/
 #include <avr/io.h>
 #include <util/delay.h>
 #include <src/lcd.h>


 uint8_t Leeteclado(void);
 void delay_ms(int valor);
 void AVRInit(void);
 int main()
 {
 	uint8_t val = 0;
 	// Initialize the AVR modules
 	AVRInit();
 	lcd_home();
 	lcd_puts("Micros AVR");
 	delay_ms(3000);
 	// Infinite loop
 	while(1)
 		{
 			//lcd_command(LCD_DISP_OFF);
			 val = Leeteclado();
			 //lcd_command(LCD_DISP_ON);
			 lcd_gotoxy(5,1);
			 if (val < 10)
			 lcd_putc(0x30+val);
			 else if((val > 9) && (val < 16))
			 lcd_putc(0x57+val);
			 else
			 lcd_putc(' ');
			 delay_ms(50);
 	 }
 return 0;
}

 uint8_t Leeteclado()
 {
 uint8_t tiempo = 20;
 uint8_t c; //columnas - In
 uint8_t r; //renglones - Out
 uint8_t val=0;
 DDRB = 0x0F;
 PORTB |= 0xF0;
 PORTB |= 0x0F; //Pone en alto las filas del keypad
 for(r = 0; r < 4; r++)
 {
	 PORTB &=~(1<<r); //se escribe un cero al renglon i esimo
	 delay_ms(10);
		 for(c = 0; c < 4; c++)
		 {
			 if( (PINB & (1<<(c+4)))== 0)
			 {
			 val = (r<<2) + c;
			 return (val);
			 }
		 while( (PINB &(1 <<(c+4))) == 0);
		 delay_ms(tiempo);
		 }
	 	PORTB |= (1<<r); //se restaura el uno
}
 PORTB |= 0x0F; //Pone en alto las filas del keypad
 return 16;
}


 void delay_ms(int valor)
 {
 	for (int i = 0; i< valor; i++)
 	_delay_ms(1);
 }

 void AVRInit()
 {
		 lcd_init(LCD_DISP_ON_CURSOR_BLINK);
		 DDRB = 0x0F; //del B7 al B4 In del B3 al B0 Out
		 PORTB |= 0xF0; //Se escriben los pull up
		 PORTB |= 0x0F; //Pone en alto las filas del keypad
 }
