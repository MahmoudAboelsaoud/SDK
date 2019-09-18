/*
 * watch_app.c
 *
 * Created: 7/23/2018 6:32:02 PM
 *  Author: Aboelsaoud ^_^
 */ 


#include <avr/io.h>

#include"TMU.h"
#include"sevenseg.h"
#include "hal_timer.h"

void watch_fun();

ecore_u8 seg1, seg2, seg3 ;
str_obj obg1;   //timer

void counter_time();
int main(void) {
	
	gcfg_hal_timer_t hal_timer_obj=
	{
		.ins_timer=TIMER_0,
		.freq=PRESCALER_64,
		.timer_fun=NORMAL_MODE,
	};
	

	seven_seg_init(BASE_D, COMMON_CATHOD, &seg1);
	seven_seg_init(BASE_C, COMMON_CATHOD, &seg2);
	seven_seg_init(BASE_B, COMMON_CATHOD, &seg3);
	tmu_init(TIMER0 , 10);
	seven_seg_display(seg1,0);
	seven_seg_display(seg2,0);
	seven_seg_display(seg3,0);
	hal_init_timer(&hal_timer_obj, counter_time);
	start_timer(watch_fun, PERIODIC, 100, &obg1);
	while(1)
	{
		tum_dispatch();
	}
	return 0;
}

void watch_fun()
{
	
	static ecore_u8 sec=0;
	static ecore_u8 min=0;
	static ecore_u8 i=0;
	
    i++;
	seven_seg_display(seg1,i);
	if(i>9)
	{
		i=0;
		seven_seg_display(seg1,i);
		seven_seg_display(seg2,++sec);
		if(sec>6)
		{
			sec=0;
			seven_seg_display(seg2,sec);
			seven_seg_display(seg3,min++);
			if(min > 9)
			{
				i=sec=min=0;
				seven_seg_display(seg1,0);
				seven_seg_display(seg2,0);
				seven_seg_display(seg3,0);
			}
		}
	}
}

