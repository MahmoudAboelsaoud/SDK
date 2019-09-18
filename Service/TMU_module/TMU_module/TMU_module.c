/*
 * TMU_module.c
 *
 * Created: 7/23/2018 7:55:01 PM
 *  Author: Aboelsaoud ^_^
 */ 

#include "TMU.h"
#include "commen.h"
#include <avr/io.h>

void fun1();
void fun2();
#define  DIR_PORTA (*(volatile unsigned char*)0x3a)
#define  INPUT_PORTA (*(volatile unsigned char*)0x39)
#define  OUTPUT_PORTA (*(volatile unsigned char*)0x3b)

#define SET_PIN(reg ,pin) (reg |=(1<<pin))
#define CLEAR_PIN(reg ,pin) (reg &= ~(1<<pin))

int main(void)
{
	 str_obj obg1, obg2;
	 tmu_init(TIMER0, 100);
	 
	SET_PIN(DIR_PORTA, 0);
	start_timer(fun1, PERIODIC, 100, &obg1);
	start_timer(fun2, PERIODIC, 100, &obg2);
    while(1)
    {
       
	 tum_dispatch();
	   
    }
}

void fun1()
{
	SET_PIN(OUTPUT_PORTA, 0);
}


void fun2()
{
	CLEAR_PIN(OUTPUT_PORTA, 0);
}
