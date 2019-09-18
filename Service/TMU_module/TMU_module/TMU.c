/*
 * TMU.c
 *
 *  Created on: Jul 15, 2018
 *      Author: Aboelsaoud ^_^
 */
#include"commen.h"
#include"TMU.h"
#include <avr/interrupt.h>


static str_obj *ga_str_t[NO_AVAILABLE_TIMERS] ={NULL};
static ecore_u8 init_flag=0;
static ecore_u8 used_timers=0;
static ecore_u8 resolution;

ISR(TIMER0_OVF_vect)
{

	for(ecore_u8 i =0; i<used_timers;i++)
	{
		ga_str_t[i]->curent_time--;
	}

}

void config_timer ()
{
	//configure the timer

	TCCR0_t |=(1<<1); // no pre_scaler 1us for each increase in timer0 256us
	TCNT0_t  =0;
	TIMSK_t |=(1<<0); // interrupt enable TOIE0
	SREG_t  |=(1<<7);
}



bool_t tmu_init(base_timer timer , ecore_u8 res)
{
	bool_t ret_val =E_TRUE;
	if((timer < INVALID_MAX_INDEX)|(timer > INVALID_MAX_INDEX) && (res !=0) && (init_flag==0))
//    if(1)
	{

	    config_timer();
	    resolution = res;
		init_flag=1;

	}
	else
	{
		ret_val=E_FALSE;
	}

	return ret_val;
}



bool_t start_timer(void(*cb)(), type_timer type, ecore_u8 time, str_obj * obg_adrs)
{

	bool_t ret_val=E_TRUE;
	if((cb!= NULL) && (type < 2) && (obg_adrs != NULL) && (time>0) && (init_flag!=0))
	{
		if(used_timers < NO_AVAILABLE_TIMERS)
		{
		  for(ecore_u8 i =0; i < NO_AVAILABLE_TIMERS; i++)
		   {
			if(ga_str_t[i]==NULL)
			{
			ga_str_t[i]=obg_adrs;
			obg_adrs->cb=cb;
			obg_adrs->time=time;
			obg_adrs->type=type;
			obg_adrs->curent_time=time;
			used_timers++;
			break;
			}
			else if(ga_str_t[i] ==obg_adrs)
		    {
				break;
		    }

			else
			{
				ret_val=E_FALSE;
			}
		   }

	    }
		else
		{
			ret_val=E_FALSE;
		}
	}
	else
	{
		ret_val=E_FALSE;
	}

	return ret_val;
}



bool_t stop_timer(str_obj * obg_adrs)
{
	bool_t ret_val=E_TRUE;
	if((obg_adrs !=NULL) && (used_timers!=0))
	{
		for(ecore_u8 i =0; i<used_timers;i++)
		{
			if(ga_str_t[i]==obg_adrs)
			{
				ga_str_t[i]=NULL;
				used_timers--;
				break;
			}
		}
	}
	else
	{
		ret_val=E_FALSE;
	}

	return ret_val;
}


bool_t tum_dispatch()
{

	bool_t ret_val=E_TRUE;
	for(ecore_u8 i =0; i < used_timers; i++)
    {
		//if((ga_str_t[i]!=NULL) && (ga_str_t[i]->curent_time <=0))
		if((ga_str_t[i]->curent_time <= 0))
		{
			(ga_str_t[i]->cb)();
			if(ga_str_t[i]->type==ONE_SHOT)
			{
				stop_timer(ga_str_t[i]);
			}
			else
			{
				ga_str_t[i]->curent_time =ga_str_t[i]->time + ga_str_t[i]->curent_time;
			}

		}
		else
		{
			ret_val = E_FALSE;
		}
   }
	return ret_val;

}



