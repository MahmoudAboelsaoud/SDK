/***********************************************/
/* Auther     : Mahmoud Aboelsaoud             */
/* Date       : 17 Jun 2021                    */
/* Version    : V01                            */
/*Description : code file                      */
/***********************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MUART_interface.h"

#include "lcd_driver.h"

#include "MGPIO_interface.h"
#include "MGPIO_private.h"

#include "Safe_private.h"
#include "Safe_interface.h"
#include "Safe_config.h"

static u8 buffer_spi_lcd_out [10];
static u8 data = 0; 
u8 count= 0;
u8 i=0;
u8 val =0;
u8 CorectFalg =0;

static void GetPassword(void)
{
	data = 0;
	data = MUART_u8Receive();
	_delay_ms(250);
	userEnteredPassword[i] = data;
	itoa(data, buffer_spi_lcd_out,10);
	LCD_Display_RowColumn(2,i ,buffer_spi_lcd_out);
	_delay_ms(50);
	LCD_Display_RowColumn(2,i ,'#');
}
	
static u8 PasswordCheck(u8 * password)
{
	for(u8 i=0;i<4;i++)
	{
	if (password[i] == userPassword [i])
		count++;
	}
	return count;
}	


static void Passworderrorhandel()
{
	val = PasswordCheck(userEnteredPassword);
	
	if(val == 4)
	{
		Lcd_Clean();
		MGPIO_ClearPin(PORTB,PIN6);
		MGPIO_SetPin(PORTB,PIN4);
		LCD_Display_RowColumn(2,0," Safe Is Open^_^");
		CorectFalg=1;
	}
	else
	{
		Lcd_Clean();
		LCD_Display_RowColumn(0,0,"Error Password");
		MGPIO_ClearPin(PORTB,PIN7);
		_delay_ms(2000);
		Lcd_Clean();
		LCD_Display_RowColumn(0,0,"TryOtherPassword");
		MGPIO_SetPin(PORTB,PIN7);
		MGPIO_SetPin(PORTB,PIN5);
	}
}



void Safe_Init(void)
{
	MGPIO_SetPortDirection(PORTB,PIN4,OUTPUT);
	MGPIO_SetPortDirection(PORTB,PIN5,OUTPUT);
	MGPIO_SetPortDirection(PORTB,PIN6,OUTPUT);
	MGPIO_SetPortDirection(PORTB,PIN7,OUTPUT);
	MGPIO_ClearPin(PORTB,PIN4);
	MGPIO_ClearPin(PORTB,PIN5);
	MGPIO_SetPin(PORTB,PIN6);
	MGPIO_SetPin(PORTB,PIN7);
	MUART_boolInit(&obj);
	Lcd_Init();	
}


void Safe_Start(void)
{
	
	Lcd_Clean();
	LCD_Display_RowColumn(0,4," Welcome");
	_delay_ms(250);
	Lcd_Clean();
	LCD_Display_RowColumn(0,0," Enter Password:"); 
	
		i=val=count=0;
	do{
		GetPassword();
		i++;
	  } while(i!=4);
	  Passworderrorhandel();
	  
	while(CorectFalg);  
	
	  i=val=count=0;
	  do{
		  GetPassword();
		  i++;
	  } while(i!=4);
	  Passworderrorhandel();
	  
	  while(CorectFalg);
	  
		 i=val=count=0;
	   do{
		   GetPassword();
		   i++;
	   } while(i!=4);
	   Passworderrorhandel();
	   
	   while(CorectFalg);
	   
	   Lcd_Clean();
	   LCD_Display_RowColumn(1,3,"No Chance!");
	   LCD_Display_RowColumn(2,3,"Safe Closed");
}

