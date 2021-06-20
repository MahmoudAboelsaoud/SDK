/*
 * machine.h
 *
 *  Created on: May 12, 2020
 *      Author: M.Aboelsaoud
 */

#include "machine.h"

static uint_8 g_u8PressedKey;
static uint_16 temp_sensor_read=0;

uint_8 buffer_adc_lcd_out [10];
static void Mcal_adc_callback(void)
{
  temp_sensor_read = ADCL/4;
  itoa(temp_sensor_read, buffer_adc_lcd_out, 10);
	/*the call back code when the interrupt come*/
}

gstr_hal_adc_t str_adc_obg_2 =
{
	.hal_adc_cb = Mcal_adc_callback,
	.freq = PRESCALER_32,
	.volt_ref = INERNAL_265_VREF,

};



bool_t Init_all_drivers()
{
	bool_t ret_val =E_TRUE;
	/************GPIO*****************/
	GPIO_PortDirection(PORTA, PIN0, INPUT);
	GPIO_PortDirection(PORTA, PIN1, INPUT);
	while(GPIO_GET_PIN(PINA,PIN0)==1);
	GPIO_PortDirection(PORTA, PIN6, OUTPUT);
	GPIO_Pin_Clear(PORTA,PIN6);

	/************LCD*****************/
	Lcd_Init();
	LCD_Display_RowColumn(0,5,"Welcome");
	LCD_Display_RowColumn(1,2,"COFFEE MACHINE");
	_delay_ms(100);
	Lcd_Clean();
	LCD_Display_RowColumn(0,0,"SELECT: 1-START");
	LCD_Display_RowColumn(1,0,"2-INFO 3-SETTING");
    /***************ADC**************/
	hal_adc_init(&str_adc_obg_2);
    hal_adc_read_channel(2);

	return ret_val;
}

bool_t Start_machine_working()
{
	bool_t ret_val =E_TRUE;
	g_u8PressedKey = KeyPad_getPressedKey();
	switch(g_u8PressedKey)
	{
		case 1  : {Lcd_Clean();
			       LCD_Display_RowColumn(0,0,"Select your Coffee:");
			       LCD_Display_RowColumn(1,0,"1-Lata    2-Max ");
			       LCD_Display_RowColumn(2,4,"3-Black   3-Patchno");
                   break;}

		case 2  : {Lcd_Clean();
                   LCD_Display_RowColumn(0,0,"The Water Temp:");
		           //LCD_Display_RowColumn(0,16,HAL_u8LM35SensorLcdPrint());
		           LCD_Display_RowColumn(0,16,buffer_adc_lcd_out);
		           LCD_Display_RowColumn(0,19,"C");
		           break;}

		case 3  : {Lcd_Clean();
		           LCD_Display_RowColumn(0,0,"SETTING");
		           break;}

		default :{Lcd_Clean();
				   LCD_Display_RowColumn(0,1,"Wrong Choice^_^");
				   GPIO_PortDirection(PORTA, PIN7, OUTPUT);
				   GPIO_Pin_Clear(PORTA,PIN7);
				   GPIO_Pin_Set(PORTA,PIN6);
				   break;}

	}



	return ret_val;
}


bool_t Sotp_machine_working()
{
	bool_t ret_val =E_TRUE;



	return ret_val;
}
