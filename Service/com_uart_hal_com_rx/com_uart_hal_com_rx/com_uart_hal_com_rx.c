/*
 * UART_AVR_STACK_Test.c
 *
 * Created: 2/24/2019 9:33:58 PM
 *  Author: M.Aboelsaoud
 */ 

#include"comm.h"
#include"hal_uart.h"
#include "lcd_driver.h"
int main(void) 
{
	DDRC=0xff;
	
	//Lcd_Init();
	
	comm_init();
	comm_recieve();
	//comm_send (x, sizeof(x));
	/*LCD_Display_RowColumn(1,4,"hi");
	Lcd_Display_Character('2');*/
	
   
	
	while(1)
	{
		comm_dispatch();
		PORTC=UDR;
		
	}

}
