/*
 * external_interrupt.h
 *
 *  Created on: Jul 29, 2019
 *      Author: M.Aboelsaoud
 */

#ifndef EXTERNAL_INTERRUPT_H_
#define EXTERNAL_INTERRUPT_H_

#include <avr/interrupt.h>
#include "common.h"

//#define INT2

#define GICR    *(volatile unsigned char*)0x5b
#define GIFR    *(volatile unsigned char*)0x5a
#define MCUCR   *(volatile unsigned char*)0x55
#define MCUCSR  *(volatile unsigned char*)0x54
#define SREG    *(volatile unsigned char*)0x5f

#define  DIR_PORTD   (*(volatile unsigned char*)0x31)
#define  INPUT_PORTD (*(volatile unsigned char*)0x30)
#define  OUTPUT_PORTD (*(volatile unsigned char*)0x32)

#define  DIR_PORTB   (*(volatile unsigned char*)0x37)
#define  INPUT_PORTB (*(volatile unsigned char*)0x36)
#define  OUTPUT_PORTB (*(volatile unsigned char*)0x38)


#define  DIR_PORTA   (*(volatile unsigned char*)0x3a)
#define  INPUT_PORTA (*(volatile unsigned char*)0x39)
#define  OUTPUT_PORTA (*(volatile unsigned char*)0x3b)

#define SET_PIN(reg ,pin) (reg |=(1<<pin))
#define CLEAR_PIN(reg ,pin) (reg &= ~(1<<pin))
#define TOGGAL_PIN(reg ,pin) (reg ^=(1<<pin))


typedef enum
{
	INT_0,
	INT_1,
	INT_2
}enum_interrupt_num;


typedef enum
{
	LOW_LEVEL,
	ANY_CHANGE,
	FALLING_EDAGE,
	RISING_EDAGE,
}enum_level_control;

typedef struct
{
	enum_interrupt_num interrupt_number;
	enum_level_control interrupt_level;
	void * cb_fun_ptr; //void(cb_fun*)(void);

}gstr_ext_interrupt_config;



bool_t hal_ex_interrupt_Initi(gstr_ext_interrupt_config *str_config);


#endif /* EXTERNAL_INTERRUPT_H_ */
