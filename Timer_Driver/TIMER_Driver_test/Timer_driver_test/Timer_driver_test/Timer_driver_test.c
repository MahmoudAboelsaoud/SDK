/*
 * Timer_driver_test.c
 *
 * Created: 6/3/2021 2:38:21 AM
 *  Author: M.Aboelsaoud
 */ 

#include <avr/io.h>
#include "TIMER_interface.h"

void fun0()
{
	DDRB = 0xff;
	PORTB = 0xff;	
}


void fun2()
{
	DDRC = 0xff;
	PORTC = 0xff;	
}


gcfg_hal_timer_t obj0 =
{
 .ins_timer = TIMER_0,
 .freq = PRESCALER_1024,
 .timer_fun = NORMAL_MODE,
 .ptr_to_timer_handler =fun0,
};


gcfg_hal_timer_t obj2 =
{
	.ins_timer = TIMER_2,
	.freq = PRESCALER_1024,
	.timer_fun = CTC_MODE,
	.ptr_to_timer_handler =fun2,
};

int main(void)
{
	hal_init_timer(&obj0);
	hal_init_timer(&obj2);
	
	hal_update_init_timer_value(&obj0,100);
	hal_update_cmp_timer(&obj2,50);
	
	hal_start_timer(&obj0);
	hal_start_timer(&obj2);
	
	
	//hal_deinit_timer(&obj2);
	
	
    while(1)
    {
         
    }
}