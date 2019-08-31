/*
 * hal_adc.c
 *
 *  Created on: Aug 12, 2018
 *      Author: Aboelsaoud ^_^
 */

#include"common.h"
#include"hal_adc.h"
#include "avr/interrupt.h"

static ecore_u16 *value;
static void(*cb_adc)();
ISR(ADC_vect)
{
*value=ADCL+(ADCH*256);

	//(*cb_adc)();
}

static void interrupt_config()
{
	*(volatile unsigned char*)0x5f |=(1<<7);
	*(volatile unsigned char*)0x26 |=(1<<3);
	*(volatile unsigned char*)0x26 |=(1<<7);

}
bool_t hal_adc_init(gstr_hal_adc_t *adc_info, ecore_u8*cb, ecore_u16 *value_digital)
{
	bool_t ret_val=E_TRUE;
	if((adc_info!=NULL) && (cb!=NULL))
	{
		cb_adc=cb;
		value=value_digital;
		if(adc_info->volt==EXTERNAL_VCC)
		{
			// ADMUX
			*(volatile unsigned char*)0x27 |=(1<<6)&~(1<<7);
		}
		else if(adc_info->volt== AREF_INTERNAL)
		{
			*(volatile unsigned char*)0x27 &=~(1<<7)&~(1<<6);
		}
		else if(adc_info->volt==INERNAL_265_VREF)
		{
			*(volatile unsigned char*)0x27 |=(1<<7)|(1<<6);
		}
		else
		{
			ret_val=E_FALSE;
		}

		if(adc_info->freq==PRESCALER_128)
		{
			//	ADCSRA  prescaler config
			*(volatile unsigned char*)0x26 |=(1<<2)|(1<<0)|(1<<1);
			interrupt_config();
		}
		else
		{
			ret_val=E_FALSE;
		}



	}
	else
	{
		 ret_val=E_FALSE;
	}


	return ret_val ;
}



bool_t hal_adc_read_channel(ecore_u8 channel)
{
	bool_t ret_val=E_TRUE;

	if(channel<8)
	{
		//DDRA input
		*(volatile unsigned char*)0x3a &=~(1<<channel);
		//channel select
		 ADMUX=(ADMUX & 0xf0)|channel;
		// ADCSRA ADC enable and start convertion
		*(volatile unsigned char*)0x26 |=(1<<6);
		//ADCH value
		}
	else
	{
		 ret_val=E_FALSE;
	}


	return ret_val;
}


