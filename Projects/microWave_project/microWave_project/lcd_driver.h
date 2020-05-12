/*
 * lcd_driver.h
 *
 *  Created on: Feb 12, 2019
 *      Author: M.Aboelsaoud
 */

#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_


#include"DataTypes.h"
#include"macros_commen.h"
#include"micro_config.h"

/*lcd 4 bit mode*/
#define DATA_BITS_MODE 4

/* Use higher 4 bits in the data port */
#if (DATA_BITS_MODE == 4)
#define UPPER_PORT_PINS
#endif



/*Lcd control commands*/
#define CLEAR_COMMAND 0x01
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80
#define LCD_OFF 0x0E


/*Lcd HW configration */
#define RS 0    //PD0
#define RW 1   //PD1
#define E  2   //PD2
#define LCD_CNTR_PORT_DIR    DDRD //*(volatile unsigned char*)0x31 //DDIRD
#define LCD_CNTR_PORT_PORT   PORTD1 //*(volatile unsigned char*)0x32 // PORTD
#define LCD_DATA_PORT_DIR    DDRC//*(volatile unsigned char*)0x34// DDIRC   DDRB
#define LCD_DATA_PORT_PORT   PORTC1 //*(volatile unsigned char*)0x35 //PORTC  PORTB


/*Lcd Interface APIS*/
bool_t Lcd_Init();
bool_t Lcd_Send_Command(uint_8 comm);
bool_t Lcd_Display_Character(uint_8 ch);
bool_t Lcd_Display_String(const uint_8* str);
bool_t Lcd_Off();
bool_t Lcd_Clean();
bool_t LCD_goToRowColumn(uint_8 row, uint_8 col);

bool_t LCD_Display_RowColumn(uint_8 row, uint_8 col, const uint_8* str);



#endif /* LCD_DRIVER_H_ */
