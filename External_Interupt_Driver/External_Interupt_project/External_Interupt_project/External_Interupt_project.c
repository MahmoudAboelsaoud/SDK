/*
 * External_Interupt_project.c
 *
 * Created: 5/29/2021 6:35:53 PM
 *  Author: M.Aboelsaoud
 */ 

#include <avr/io.h>
#include "EXTI_interface.h"
#include "BIT_MATH.h"

void fun0(void)
{
SET_BIT (DDRB,6);
SET_BIT (PORTB,6);
}

void fun1(void)
{
	SET_BIT (DDRC,6);
	SET_BIT (PORTC,6);
} 

void fun2(void)
{
	SET_BIT (DDRC,7);
	SET_BIT (PORTC,7);
}

gstr_ext_interrupt_config ob0 =
{
	.interrupt_number = INT_0,
	.interrupt_level  = RISING_EDAGE,
	.cb_fun_ptr = fun0
};

gstr_ext_interrupt_config ob1 =
{
	.interrupt_number = INT_0,
	.interrupt_level  = RISING_EDAGE,
	.cb_fun_ptr = fun1
};

gstr_ext_interrupt_config ob2 =
{
	.interrupt_number = INT_2,
	.interrupt_level  = RISING_EDAGE,
	.cb_fun_ptr = fun2
};


int main(void)
{
	
	Hal_Ext_Interrupt_Init(&ob1);
	Hal_Ext_Interrupt_Init(&ob2);
	Hal_Ext_Interrupt_Init(&ob0);
	
    while(1)
    {
		
        //TODO:: Please write your application code 
    }
}