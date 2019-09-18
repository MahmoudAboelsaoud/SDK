/*
 * hal_adc.h
 *
 *  Created on: Aug 12, 2018
 *      Author: Aboelsaoud ^_^
 */

#ifndef HAL_ADC_H_
#define HAL_ADC_H_
#include"common.h"
#include<avr/interrupt.h>

#define ADCSRA *(volatile unsigned char*)0x26
#define ADCL   *(volatile unsigned char*)0x24
#define ADCH   *(volatile unsigned char*)0x25
#define ADMUX  *(volatile unsigned char*)0x27
#define SFIOR  *(volatile unsigned char*)0x50
#define SREG   *(volatile unsigned char*)0x5f
#define DDRA   *(volatile unsigned char*)0x3a
#define DDRB   *(volatile unsigned char*)0x37
#define PORB   *(volatile unsigned char*)0x38

typedef enum
{
	PRESCALER_2=0x0,
	PRESCALER_4,
	PRESCALER_8,
	PRESCALER_16,
	PRESCALER_32,
	PRESCALER_64,
	PRESCALER_128,
}enum_adc_freq_t;

typedef enum
{
	AREF_INTERNAL,
	EXTERNAL_VCC,
	INERNAL_265_VREF,
}enum_adc_voltage_ref_t;
/*
typedef enum
{
	SINGEL_ENDED_INPUT,
	DIFFERENTIAL,
}enum_adc_mode_t;*/

/*typedef enum{
	ADC0=00000,
	ADC1=00001,
	ADC2=00010,
	ADC3=00011,
	ADC4=00100,
	ADC5=00101,
	ADC6=00110,
	ADC7=00111,
}enum_single_ended_ch_t;*/

typedef struct
{
	void (*hal_adc_cb)();
	enum_adc_freq_t freq;
	enum_adc_voltage_ref_t volt_ref;
	//enum_adc_mode_t mode;
}gstr_hal_adc_t;

bool_t hal_adc_init(gstr_hal_adc_t *adc_info);
bool_t hal_adc_read_channel(ecore_u8 channel);


#endif /* HAL_ADC_H_ */
