/*
 * ADC_device_driver_test.c
 *
 * Created: 4/10/2019 12:11:51 AM
 *  Author: M.Aboelsaoud
 */ 


#include "hal_adc.h"
void test()
{
	PORB=ADCL;
	PORTD=ADCH;	
}
	
int main(void)
{
	DDRB=0xff;
	DDRD=0xff;
	ecore_u8 x=0;
	gstr_hal_adc_t obg1=
	{
		.hal_adc_cb=test,
		.freq=PRESCALER_128,
		.volt_ref=INERNAL_265_VREF,
	};
	
	hal_adc_init(&obg1);
	hal_adc_read_channel(0);
    while(1)
    {
        //TODO:: Please write your application code 
    }
}