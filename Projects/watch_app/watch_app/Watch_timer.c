/*
 ============================================================================
 Name        : Watch_timer.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include"TMU.h"
#include"sevenseg.h"

void funtion1();

ecore_u8 seg1, seg2, seg3 ;
str_obj obg1;   //timer


int main(void) {


	seven_seg_init(BASE_D, COMMON_ANOD, &seg1);
	seven_seg_init(BASE_C, COMMON_ANOD, &seg2);
	seven_seg_init(BASE_A, COMMON_ANOD, &seg3);
	tmu_init(TIMER0 , 1);
	start_timer(funtion1, PERIODIC, 10, &obg1);
	while(1)
	{
		tum_dispatch();
	}
	return 0;
}

void funtion1()
{
	static ecore_u8 sec = 0;
	static ecore_u8 min=0;
	static ecore_u8 i=0;


	    	 seven_seg_display(seg1,i);
	    	 i++;
	    	 if(i==9)
	    	 {
	    		 seven_seg_display(seg2,sec++);
	    		 i=0;
	    		 if(sec==6)
	    		 {

	    			 seven_seg_display(seg3,min++);
	    			 sec=i=0;
	    			 if(min==9)
	    			 {
	    				 seven_seg_display(seg1,0);
	    				 seven_seg_display(seg2,0);
	    				 seven_seg_display(seg3,0);
	    				 i=sec=min=0;
	    			 }
	    		 }
	    	 }
}

