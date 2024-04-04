#ifndef LCD_DEFINITIONS_H_INCLUDED
#define LCD_DEFINITIONS_H_INCLUDED

#define LCD_CONTROL_PORT   PORTB
#define LCD_RS_PORT LCD_CONTROL_PORT
#define LCD_RS_PIN  1

#define LCD_RW_PORT LCD_CONTROL_PORT
#define LCD_RW_PIN  2

#define LCD_E_PORT  LCD_CONTROL_PORT
#define LCD_E_PIN   3

#define LCD_DATA0_PORT  PORTB
#define LCD_DATA1_PORT  PORTB
#define LCD_DATA2_PORT  PORTB
#define LCD_DATA3_PORT  PORTB


#define LCD_DATA0_PIN  4
#define LCD_DATA1_PIN  5
#define LCD_DATA2_PIN  6
#define LCD_DATA3_PIN  7


//Definicion de retardos
//#define F_CPU 1000000UL
#define LCD_DELAY_BOOTUP   20000      /**< delay in micro seconds after power-on  */
#define LCD_DELAY_INIT      15000      /**< delay in micro seconds after initialization command sent  */
#define LCD_DELAY_INIT_REP    2500      /**< delay in micro seconds after initialization command repeated */
#define LCD_DELAY_INIT_4BIT   2500      /**< delay in micro seconds after setting 4-bit mode */
#define LCD_DELAY_BUSY_FLAG    4000      /**< time in micro seconds the address counter is updated after busy flag is cleared */
#define LCD_DELAY_ENABLE_PULSE 2000      /**< enable signal pulse width in micro seconds */



#endif // LCD_DEFINITIONS_H_INCLUDED
