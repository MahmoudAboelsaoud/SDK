/*
 * ADC_hal_driver_test.c
 *
 * Created: 8/12/2018 7:21:01 PM
 *  Author: Aboelsaoud ^_^
 */ 

#include"common.h"
#include"hal_adc.h"

ecore_u16 digital_val;
void fun1();
int main(void)
{
	//portb output
	*(volatile unsigned char*)0x37=0xff;
	gstr_hal_adc_t adc1=
	{
		                 
		.freq= PRESCALER_128,
		.volt=EXTERNAL_VCC,
		//.adc_cb=fun1,
	};
	
  hal_adc_init(&adc1, fun1, &digital_val);	
  hal_adc_read_channel(1);
    while(1)
    {
      fun1();
	    //TODO:: Please write your application code 
    }
}

void fun1()
{
	*(volatile unsigned char*)0x38= digital_val ;//* 0.0048;
}

