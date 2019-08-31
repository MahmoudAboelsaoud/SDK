/*
 * hal_adc.h
 *
 *  Created on: Aug 12, 2018
 *      Author: Aboelsaoud ^_^
 */

#ifndef HAL_ADC_H_
#define HAL_ADC_H_
#define ADCSRA (*(volatile unsigned char*)0x26)
#define  ADCH *(volatile unsigned char*)0x25
#define  ADCL *(volatile unsigned char*)0x24
#define  ADMUX *(volatile unsigned char*)0x27
#include"common.h"
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

typedef struct
{
	//void (*adc_cb)();
	enum_adc_freq_t freq;
	enum_adc_voltage_ref_t volt;
	//enum_adc_mode_t mode;
}gstr_hal_adc_t;

bool_t hal_adc_init(gstr_hal_adc_t *adc_info, ecore_u8*cb, ecore_u16 *value_digital);
bool_t hal_adc_read_channel(ecore_u8 channel);


#endif /* HAL_ADC_H_ */
