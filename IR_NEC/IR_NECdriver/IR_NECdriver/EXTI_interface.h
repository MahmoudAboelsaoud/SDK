/**********************************************/
/* Auther : Mahmoud Aboelsaoud                */
/* Version: v2                                */
/* Data   : 28 may 2021                       */
/* Description   : external interupt code     */
/**********************************************/

#ifndef EXTI_INTERFACE_H
#define  EXTI_INTERFACE_H

#include "STD_TYPES.h"


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
	//void * cb_fun_ptr; //void(cb_fun*)(void);
}gstr_ext_interrupt_config;



bool_t Hal_Ext_Interrupt_Init(gstr_ext_interrupt_config *str_config);

bool_t Hal_Ext_Interrupt_Cb_INT0(void (*ext_cb_function)(void));


bool_t Hal_Ext_Interrupt_Cb_INT1(void (*ext_cb_function)(void));


bool_t Hal_Ext_Interrupt_Cb_INT2(void (*ext_cb_function)(void));









#endif