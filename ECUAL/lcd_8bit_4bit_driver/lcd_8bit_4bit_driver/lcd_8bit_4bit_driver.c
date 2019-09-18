/*
 * lcd_8bit_4bit_driver.c
 *
 * Created: 2/14/2019 2:13:01 PM
 *  Author: M.Aboelsaoud
 */ 

#include "lcd_driver.h"
//#include <avr/io.h>

int main(void)
{
	Lcd_Init();
	LCD_Display_RowColumn(0,4,"MAHMOUD");
	LCD_Display_RowColumn(1,3,"ABOELSAOUD");
	//Lcd_Display_Character('A');
    while(1)
    {
		
		Lcd_Send_Command(0x1c);
		_delay_us(5500);
		Lcd_Send_Command(0x18);
        //TODO:: Please write your application code 
    }
}