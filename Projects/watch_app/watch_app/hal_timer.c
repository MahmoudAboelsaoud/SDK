
#include "hal_system_errors.h"
#include "hal_timer.h"
#include "commen.h"

#include <avr/interrupt.h>
static void(*cb_fun_ovf_t)();
ISR(TIMER0_OVF_vect)
{
  (*cb_fun_ovf_t)();
}
/*	ISR(timer0_comp_vect)
{
	(*cb_comp_ovf)();
}*/

static void  interupt_config()
{
	// timer0 interrupt setting
	*(volatile unsigned char*)0x5f |=(1<<7);
	*(volatile unsigned char*)0x59 |=(1<<0);
}
ecore_su8 hal_init_timer(gcfg_hal_timer_t * obj, ecore_u8* cb_fun_ovf)
{
   // static ecore_s8 check=obj->ins_timer;
	ecore_su8 ret_val = E_OK;
	if(obj != NULL)
	{
		if(obj->freq && obj->ins_timer && obj->timer_fun &&(cb_fun_ovf!=NULL))
		{
			 cb_fun_ovf_t = cb_fun_ovf;
			 if( obj->ins_timer==TIMER_0)
			 {
				 if(obj->timer_fun==NORMAL_MODE)
				 *(volatile unsigned char*)TIMER_0 &=~(1<<3) &~(1<<6);
				 else if(obj->timer_fun==PWM_PHASE_CORRECT)
				 *(volatile unsigned char*)TIMER_0 |=(1<<3) &~(1<<6);
				 else if(obj->timer_fun==CTC_MODE)
				 *(volatile unsigned char*)TIMER_0 &=~(1<<3) |(1<<6);
				 else if(obj->timer_fun==FAST_PWM)
				 *(volatile unsigned char*)TIMER_0 |=(1<<3) |(1<<6);
				 interupt_config();
				 *(volatile unsigned char*)obj->ins_timer=obj->freq;
			 }
			  else if(obj->ins_timer==TIMER_2)
			  {
				  if(obj->timer_fun==NORMAL_MODE)
				  *(volatile unsigned char*)TIMER_0 &=~(1<<3) &~(1<<6);
				  else if(obj->timer_fun==PWM_PHASE_CORRECT)
				  *(volatile unsigned char*)TIMER_0 |=(1<<3) &~(1<<6);
				  else if(obj->timer_fun==CTC_MODE)
				  *(volatile unsigned char*)TIMER_0 &=~(1<<3) |(1<<6);
				  else if(obj->timer_fun==FAST_PWM)
				  *(volatile unsigned char*)TIMER_0 |=(1<<3) |(1<<6);
				   interupt_config();
				   
			  }
			  else
			  {
				  ret_val = INVALID_ARG;
			  }
			
		}
		else
		{
			ret_val = INVALID_ARG;
		}
	}
	else
	{
		ret_val = INVALID_ARG;
	}
	return ret_val;
}

ecore_su8 hal_start_timer(gcfg_hal_timer_t * obj)
{
	ecore_su8 ret_val = E_OK;
	if(obj != NULL)
	{
		if(obj->freq && obj->ins_timer && obj->timer_fun)
		{

			 *(volatile unsigned char*)obj->ins_timer=obj->freq;

		}
		else
		{
			ret_val = INVALID_ARG;
		}
	}
    else
    {
	   	ret_val = INVALID_ARG;
    }
	return ret_val;
}


ecore_su8 hal_read_timer(gcfg_hal_timer_t * obj, ecore_u8 *timer_contain)
{
	ecore_su8 ret_val = E_OK;
	if(obj != NULL)
	{
		*timer_contain=*(volatile unsigned char*)obj->ins_timer +1;
	}
    else
    {
	   	ret_val = INVALID_ARG;
    }
	return ret_val;
}

ecore_su8 hal_is_timer_finish(gcfg_hal_timer_t * obj , bool_t * res)
{
	ecore_su8 ret_val = E_OK;
	if(obj != NULL)
	{
      obj->freq=0;

	}
    else
    {
	   	ret_val = INVALID_ARG;
    }
	return ret_val;
}


ecore_su8 hal_update_timer(gcfg_hal_timer_t * obj , ecore_u8 value)
{
	ecore_su8 ret_val = E_OK;
	if(obj != NULL)
	{
		//*(volatile unsigned char*)obj->ins_timer +1 =value;

	}
    else
    {
	   	ret_val = INVALID_ARG;
    }
	return ret_val;
}


ecore_su8 hal_update_cmp_timer(gcfg_hal_timer_t * obj , ecore_u8 value)
{
	ecore_su8 ret_val = E_OK;
	if(obj != NULL)
	{
		*(volatile unsigned char*)0x5c=value;
	}
    else
    {
	   	ret_val = INVALID_ARG;
    }
	return ret_val;
}

ecore_su8 hal_deinit_timer(gcfg_hal_timer_t * obj)
{
	ecore_su8 ret_val = E_OK;
	if(obj != NULL)
	{
		obj->ins_timer=0;
		obj->freq=0;
		obj->timer_fun=0;

	}
    else
    {
	   	ret_val = INVALID_ARG;
    }
	return ret_val;
}
