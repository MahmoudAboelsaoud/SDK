/*
 * lm35_lcd.c
 *
 * Created: 4/12/2019 10:19:33 PM
 *  Author: M.Aboelsaoud
 */ 
#include "hal_adc.h"
#include "lcd_driver.h"
void test()
{
	ecore_u8 arr[11]="0123456789";
	ecore_u16 reading = ADCL+(ADCH*256);
	reading*=4.88;
	LCD_Display_RowColumn(1,4,arr[reading/100%10]);
	LCD_Display_RowColumn(1,5,arr[reading/10%10]);
	LCD_Display_RowColumn(1,6,".");
	LCD_Display_RowColumn(1,7,arr[reading%10]);
	/*Lcd_Display_Character(arr[reading/100%10]);
	Lcd_Display_Character(arr[reading/10%10]);
	Lcd_Display_Character(arr[reading%10]);*/
	PORB=ADCL;
	/*PORTD=ADCH;*/
}
int main(void)
{
	DDRB=0xff;
	gstr_hal_adc_t obg1=
	{
		.hal_adc_cb=test,
		.freq=PRESCALER_128,
		.volt_ref=INERNAL_265_VREF,
	};
	Lcd_Init();
	LCD_Display_RowColumn(0,2,"THE TEMP IS ");
	hal_adc_init(&obg1);
	hal_adc_read_channel(0);
	
	/*LCD_Display_RowColumn(1,4,"ADCL");*/
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}