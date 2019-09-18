/*
 * ROTTS.c
 *
 * Created: 8/11/2018 1:26:12 PM
 *  Author: Aboelsaoud ^_^
 */ 

#include "FreeRTOS.h"
#include "task.h"
#include <avr/io.h>
#include <avr/delay.h>
#define  DIR_PORTD (*(volatile unsigned char*)0x31)
#define  INPUT_PORTD (*(volatile unsigned char*)0x30)
#define  OUTPUT_PORTD (*(volatile unsigned char*)0x32)

#define SET_PIN(reg ,pin) (reg |=(1<<pin))
#define CLEAR_PIN(reg ,pin) (reg &= ~(1<<pin))
#define togel(reg ,pin) (reg ^=(1<<pin))



void fun1()
{
while(1){
togel(OUTPUT_PORTD,0);
_delay_ms(100);

vTaskDelay(10);	
}

}

void fun2()
{

while(1)
{
togel(OUTPUT_PORTD,1);
_delay_ms(150);
vTaskDelay(15);
}
}


int main(void)
{
	DIR_PORTD |= 1<<0 | 1<<1;

	 xTaskCreate(fun2,NULL,100,NULL,2,NULL);
     xTaskCreate(fun1,NULL,100,NULL,3,NULL);
	 vTaskStartScheduler();
   
}