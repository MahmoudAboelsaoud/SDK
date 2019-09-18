/*
 * lcd.c
 *
 *  Created on: Feb 12, 2019
 *      Author: M.Aboelsaoud
 */

#include "lcd_driver.h"

bool_t Lcd_Init()
{
	bool_t ret_val=E_TRUE;
	/* set lcd data port and RS E Rw as output  */
	LCD_CNTR_PORT_DIR |=(1<<RS)|(1<<RW)|(1<<E);
	#if(DATA_BITS_MODE == 4)
		#ifdef UPPER_PORT_PINS
	       LCD_DATA_PORT_DIR=0xf0; /* Configure the highest 4 bits of the data port as output pins */
 	 	#else
	       LCD_DATA_PORT_DIR=0x0f; /* Configure the lowest 4 bits of the data port as output pins */
		#endif
	       Lcd_Send_Command(FOUR_BITS_DATA_MODE); /* initialize LCD in 4-bit mode */
	       Lcd_Send_Command(TWO_LINE_LCD_Four_BIT_MODE);
    #elif(DATA_BITS_MODE == 8)
	       LCD_DATA_PORT_DIR=0xff; /* initialize LCD in 8-bit mode */
	       Lcd_Send_Command(TWO_LINE_LCD_Eight_BIT_MODE);
	#endif
	Lcd_Send_Command(CURSOR_OFF);
	Lcd_Send_Command(CLEAR_COMMAND);

	return ret_val;
}


bool_t Lcd_Send_Command(ecore_u8 comm)
{
	bool_t ret_val=E_TRUE;
	/* Clear RS, RW */
	CLEAR_BIT(LCD_CNTR_PORT_PORT, RS);
	CLEAR_BIT(LCD_CNTR_PORT_PORT, RW);
	_delay_ms(1);
	CLEAR_BIT(LCD_CNTR_PORT_PORT, E);
	_delay_ms(1);

#if(DATA_BITS_MODE==4)
	/* out the upper 4 bits of the required command to the data bus D4 --> D7 */
	#ifdef UPPER_PORT_PINS
		LCD_DATA_PORT_PORT= (comm & 0xf0);
    #else
		LCD_DATA_PORT_PORT= ((comm >>4)& 0xf0);
	#endif

		_delay_ms(1);
		/*SET the enable pulse*/
		SET_BIT(LCD_CNTR_PORT_PORT, E);
		_delay_ms(1);
		CLEAR_BIT(LCD_CNTR_PORT_PORT, E);
		_delay_ms(1);
    #ifdef UPPER_PORT_PINS
		LCD_DATA_PORT_PORT= ((comm<<4)&0xf0);
	#else
		LCD_DATA_PORT_PORT= (comm &0x0f);
	#endif

		_delay_ms(1);
		/*SET the enable pulse*/
		SET_BIT(LCD_CNTR_PORT_PORT, E);
		_delay_ms(1);
		CLEAR_BIT(LCD_CNTR_PORT_PORT, E);
		_delay_ms(1);

#elif(DATA_BITS_MODE==8)
		LCD_DATA_PORT_PORT=comm;
		_delay_ms(1);
		/*SET the enable pulse*/
		SET_BIT(LCD_CNTR_PORT_PORT, E);
		_delay_ms(1);
		CLEAR_BIT(LCD_CNTR_PORT_PORT, E);
		_delay_ms(1);


#endif


	return ret_val;
}


bool_t Lcd_Display_Character(ecore_u8 ch)
{
	bool_t ret_val=E_TRUE;
	/* Clear RS, RW */
	SET_BIT(LCD_CNTR_PORT_PORT, RS);
	CLEAR_BIT(LCD_CNTR_PORT_PORT, RW);
	_delay_ms(1);
	CLEAR_BIT(LCD_CNTR_PORT_PORT, E);
	_delay_ms(1);

#if(DATA_BITS_MODE==4)
	/* out the lowest 4 bits of the required command to the data bus D4 --> D7 */
	#ifdef UPPER_PORT_PINS
		LCD_DATA_PORT_PORT= (ch & 0xf0);
    #else
		LCD_DATA_PORT_PORT= ((ch >>4)& 0xf0);
	#endif

		_delay_ms(1);
		/*SET the enable pulse*/
		SET_BIT(LCD_CNTR_PORT_PORT, E);
		_delay_ms(1);
		CLEAR_BIT(LCD_CNTR_PORT_PORT, E);
		_delay_ms(1);
    #ifdef UPPER_PORT_PINS
		LCD_DATA_PORT_PORT= ((ch<<4)&0xf0);
	#else
		LCD_DATA_PORT_PORT= (ch &0x0f);
	#endif

		_delay_ms(1);
		/*SET the enable pulse*/
		SET_BIT(LCD_CNTR_PORT_PORT, E);
		_delay_ms(1);
		CLEAR_BIT(LCD_CNTR_PORT_PORT, E);
		_delay_ms(1);

#elif(DATA_BITS_MODE==8)
		LCD_DATA_PORT_PORT=ch;
		_delay_ms(1);
		/*SET the enable pulse*/
		SET_BIT(LCD_CNTR_PORT_PORT, E);
		_delay_ms(1);
		CLEAR_BIT(LCD_CNTR_PORT_PORT, E);
		_delay_ms(1);


#endif

	return ret_val;
}

bool_t Lcd_Display_Int(ecore_u16 ch)
{
	bool_t ret_val=E_TRUE;
	/* Clear RS, RW */
	SET_BIT(LCD_CNTR_PORT_PORT, RS);
	CLEAR_BIT(LCD_CNTR_PORT_PORT, RW);
	_delay_ms(1);
	CLEAR_BIT(LCD_CNTR_PORT_PORT, E);
	_delay_ms(1);

	#if(DATA_BITS_MODE==4)
	/* out the lowest 4 bits of the required command to the data bus D4 --> D7 */
	#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT_PORT= (ch & 0xf0);
	#else
	LCD_DATA_PORT_PORT= ((ch >>4)& 0xf0);
	#endif

	_delay_ms(1);
	/*SET the enable pulse*/
	SET_BIT(LCD_CNTR_PORT_PORT, E);
	_delay_ms(1);
	CLEAR_BIT(LCD_CNTR_PORT_PORT, E);
	_delay_ms(1);
	#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT_PORT= ((ch<<4)&0xf0);
	#else
	LCD_DATA_PORT_PORT= (ch &0x0f);
	#endif

	_delay_ms(1);
	/*SET the enable pulse*/
	SET_BIT(LCD_CNTR_PORT_PORT, E);
	_delay_ms(1);
	CLEAR_BIT(LCD_CNTR_PORT_PORT, E);
	_delay_ms(1);

	#elif(DATA_BITS_MODE==8)
	LCD_DATA_PORT_PORT=ch;
	_delay_ms(1);
	/*SET the enable pulse*/
	SET_BIT(LCD_CNTR_PORT_PORT, E);
	_delay_ms(1);
	CLEAR_BIT(LCD_CNTR_PORT_PORT, E);
	_delay_ms(1);


	#endif

	return ret_val;
	
}

bool_t Lcd_Display_String(const ecore_u8* str)
{
	bool_t ret_val=E_TRUE;

	/* Clear RS, RW */
	SET_BIT(LCD_CNTR_PORT_PORT, RS);
	CLEAR_BIT(LCD_CNTR_PORT_PORT, RW);

	while(*str){
		Lcd_Display_Character(*str);
/*
	LCD_DATA_PORT_PORT=*str;
	_delay_ms(1);

	//SET the enable pulse
	SET_BIT(LCD_CNTR_PORT_PORT, E);
	_delay_ms(1);
	CLEAR_BIT(LCD_CNTR_PORT_PORT, E);
	_delay_ms(1);*/
	str++;
	}

	return ret_val;
}

bool_t LCD_goToRowColumn(ecore_u8 row, ecore_u8 col)
{
	bool_t ret_val=E_TRUE;

	 static	ecore_u8 Address;

	switch(row)
		{
			case 0:
					Address=col;
					break;
			case 1:
					Address=col+0x40;
					break;
			case 2:
					Address=col+0x10;
					break;
			case 3:
					Address=col+0x50;
					break;
		}
	 /* we need to apply the corresponding command 0b10000000+Address */
	Lcd_Send_Command(Address | SET_CURSOR_LOCATION);



	return ret_val;
}

bool_t LCD_Display_RowColumn(ecore_u8 row, ecore_u8 col, const ecore_u8* str)
{

	bool_t ret_val=E_TRUE;

	 LCD_goToRowColumn(row, col);
	 Lcd_Display_String(str);

	return ret_val;
}




bool_t Lcd_Off()
{
	bool_t ret_val=E_TRUE;

  Lcd_Send_Command(LCD_OFF);

	return ret_val;
}

bool_t Lcd_Clean()
{
	bool_t ret_val=E_TRUE;

  Lcd_Send_Command(CLEAR_COMMAND);

	return ret_val;
}
