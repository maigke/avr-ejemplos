/******************************************************
 * main.c
 *
 * Program Name:  twi_2
 *         Date:  2020-05-05
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

#define Dev24AA512		0xA6

void AVRInit()
{
	// AVR Initialization
	i2c_init();
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
	_delay_ms(5);
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

int main()
{
	unsigned char ret;
	unsigned int dir;
	// Initialize the AVR modules
	AVRInit();

	// Infinite loop
	while(1)
	{
			for(dir = 0;dir < 0xFFFF;dir++)
			{
				write2EEPROM(0xA0,dir);
				ret = read2EEPROM(dir);
			}
	}

	return 0;
}
