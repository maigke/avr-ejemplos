/******************************************************
 * main.c
 *
 * Program Name:  twi_1
 *         Date:  2020-05-04
 *       Author:  YOUR_NAME
 *      License:  YOUR_LICENSE
 *
 * Description:
 *  This is my program description..
 *
 *****************************************************/
#include <avr/io.h>
#include <util/delay.h>
#include <i2cmaster.h>

#define Dev24C02		0xA2   //direccion de una eeprom

void AVRInit()
{

	i2c_init();
}

int main()
{
	unsigned char ret;
	// Initialize the AVR modules
	AVRInit();

	//Escribe 0x75 en la direccion 0x05 de la eeprom
	i2c_start_wait(Dev24C02 + I2C_WRITE); //poner la mem en modo WR
	i2c_write(0xAA); //se indica la direccion a donde se va a escribir 1111 0010
	i2c_write(0x75); //dato que se escribe en la eeprom
	i2c_stop(); //Libera el bus

	//Ahora se procede a leer la direccion escrita
	i2c_start_wait(Dev24C02 + I2C_WRITE); //se pone a eeprom en modo WR
	i2c_write(0xAA); //se indica la direccion de la eeprom
	i2c_start_wait(Dev24C02 + I2C_READ);//se pone a eeprom en modo RD
	ret = i2c_readNak(); //Solo lee un dato y detiene la comunicacion
	i2c_stop();

	// Infinite loop
	while(1)
	{

	}

	return 0;
}
