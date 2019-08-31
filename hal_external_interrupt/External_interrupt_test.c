/*
 * External_interrupt_test.c
 *
 * Created: 7/29/2019 2:28:21 AM
 *  Author: M.Aboelsaoud
 */ 


#include "external_interrupt.h"

void fun0(void);
void fun1(void);

unit_16 car_counter = 0;
unit_8 sensor_door_1 = 0;
unit_8 sensor_door_2 = 0;

gstr_ext_interrupt_config obg0=
{
	.interrupt_level = RISING_EDAGE,
	.interrupt_number = INT_0,
	.cb_fun_ptr = &fun0,
};

gstr_ext_interrupt_config obg1=
{
	.interrupt_level = RISING_EDAGE,
	.interrupt_number = INT_1,
	.cb_fun_ptr = &fun1,
};

int main(void)
{
	/*output*/
	SET_PIN(DIR_PORTB,0);
	SET_PIN(DIR_PORTB,1);
	
	/* 7 seg port*/
	DIR_PORTA=0xff;
	
	/*port d init*/
	

	CLEAR_PIN(OUTPUT_PORTB,0);
	CLEAR_PIN(OUTPUT_PORTB,1);
	
	OUTPUT_PORTA = car_counter;

	
	hal_ex_interrupt_Initi(&obg0);
	hal_ex_interrupt_Initi(&obg1);
	
	SREG = (1<<7);
	
     sensor_door_2=0;
	 sensor_door_1=0;
	 	
	 while(1)
	 {
		 if (sensor_door_1 == 1)
		 {
			 if (sensor_door_2 == 1)
			 {
				 car_counter++;
				 TOGGAL_PIN(OUTPUT_PORTB,0);
				 OUTPUT_PORTA=car_counter;
				 sensor_door_2=0;
				 sensor_door_1=0;
			 }
		 }
		 
	 if(sensor_door_2 == 1)
		 {
		 if(sensor_door_1 == 1)
			 {
				 car_counter--;
				 TOGGAL_PIN(OUTPUT_PORTB,1);
				 OUTPUT_PORTA=car_counter;
				 sensor_door_1=0;
				 sensor_door_2=0;
				 //break;
			 }
			 
		 }
	 }
	 
	 
	 sensor_door_2=0;
	 sensor_door_1=0;
}


void fun0(void)
{
	/*first door at get in the garage*/
	sensor_door_1 = 1;
}

void fun1(void)
{
	/*second door at get in the garage*/
	sensor_door_2 = 1;
}