/*
 * hal_adc.c
 *
 *  Created on: Aug 12, 2018
 *      Author: Aboelsaoud ^_^
 */


#include"hal_adc.h"

static void (*cb_adc)();
ISR(ADC_vect)
{
	DDRC =0xff;
	PORTC^=0xff;
	(*cb_adc)();
}

static void interrupt_config()
{
	SREG|=(1<<7);
	ADCSRA|=(1<<3);
}

bool_t hal_adc_init(gstr_hal_adc_t *adc_info/*, void *cb_ptr*/)
{
	bool_t ret_val=E_TRUE;
	if(adc_info!=NULL)
	{
		cb_adc=(void(*)())(adc_info->hal_adc_cb);
		/*ADC Enable*/
		ADCSRA|=(1<<7);
		interrupt_config();

		/*ADMUX Vref REFS0 , REFS1*/
		if(adc_info->volt_ref==AREF_INTERNAL)
		{
			ADMUX &=~(1<<7)&~(1<<6);
		}
		else if(adc_info->volt_ref==EXTERNAL_VCC)
		{
			ADMUX &=~(1<<7)|(1<<6);
		}
		else if(adc_info->volt_ref==INERNAL_265_VREF)
		{
			ADMUX |=(1<<7)|(1<<6);
		}
		else
		{
			ret_val=E_FALSE;
		}

		if(adc_info->freq==PRESCALER_128)
		{
			/*ADCSRA  prescaler config*/
			ADCSRA |=(1<<2)|(1<<1)|(1<<0);
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


	return ret_val;
}



bool_t hal_adc_read_channel(uint_8 channel)
{
	bool_t ret_val=E_TRUE;

	if(channel<8)
	{
		/*portA input*/
		 DDRA|=(1<<channel);
		/*channel select*/
		 ADMUX|=(ADMUX & 0xf0)|channel;
		/* ADCSRA ADC start convertion*/
		 ADCSRA |=(1<<6)|(1<<5);
		/* while((ADCSRA&(1<<4))==0);
		 DDRB=0xff;
		 PORB=ADCL;*/
	}
	else
	{
		 ret_val=E_FALSE;
	}


	return ret_val;
}


