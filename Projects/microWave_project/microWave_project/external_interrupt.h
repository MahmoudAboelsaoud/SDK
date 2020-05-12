/*
 * external_interrupt.h
 *
 *  Created on: Jul 29, 2019
 *      Author: M.Aboelsaoud
 */

#ifndef EXTERNAL_INTERRUPT_H_
#define EXTERNAL_INTERRUPT_H_

#include <avr/interrupt.h>
#include "DataTypes.h"
#include"AVR_registers.h"

//#define INT2

#define GETBIT(REG, BITNO)      ((REG>>BITNO)&1)
#define CLRBIT(REG, BITNO)      (REG &=~(BITNO<<1))
#define SETBIT(REG, BITNO)      (REG |=(BITNO<<1))
#define TOGGELBIT(REG, BITNO)   (REG ^=(BITNO<<1))


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
