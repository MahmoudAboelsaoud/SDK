
#include "hal_system_errors.h"
#include "hal_timer.h"
#include "common.h"
#include "hal_timer_config.h"


static void(*cb_fun_ovf_t)();

ISR(timer0_ovf_vect)
{
#ifdef RESOLUTION_IS_USED
	tmu_logic();

#else
  (*cb_fun_ovf_t)();
#endif
}

/*	ISR(timer0_comp_vect)
{
	(*cb_comp_ovf)();
}*/


void config_interrupt_timer ()
{
	/* Interrupt configure the timer*/
	SREG  |=(1<<7);
#ifdef TIMER0
	TIMSK |=(1<<0); /* interrupt enable TOIE0*/
#endif

#ifdef TIMER1
	TIMSK |=(1<<2); /* interrupt enable TOIE1*/
#endif

#ifdef TIMER2
	TIMSK |=(1<<6); /* interrupt enable TOIE2*/
#endif
}



ecore_s8 hal_init_timer(gcfg_hal_timer_t * obj, ecore_u8* cb_fun_ovf)
{
	ecore_s8 ret_val = E_OK;
	if(obj != NULL)
	{
		if(obj->freq && obj->ins_timer && obj->timer_fun &&(cb_fun_ovf!=NULL))
		{
			 cb_fun_ovf_t = cb_fun_ovf;
			 if(obj->ins_timer==TIMER_0)
			 {
				 if(obj->timer_fun==NORMAL_MODE)
				 *(volatile unsigned char*)TIMER_0 &=~(1<<3) &~(1<<6);
				 else if(obj->timer_fun==PWM_PHASE_CORRECT)
				 *(volatile unsigned char*)TIMER_0 |=(1<<3) &~(1<<6);
				 else if(obj->timer_fun==CTC_MODE)
				 *(volatile unsigned char*)TIMER_0 &=~(1<<3) |(1<<6);
				 else if(obj->timer_fun==FAST_PWM)
				 *(volatile unsigned char*)TIMER_0 |=(1<<3) |(1<<6);
				 config_interrupt_timer();
				 /*timer clock*/
				/* *(volatile unsigned char*)obj->ins_timer=obj->freq;*/
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
				  config_interrupt_timer();
				   /*timer clock*/
				  /* *(volatile unsigned char*)obj->ins_timer=obj->freq;*/
			  }

			  else if(obj->ins_timer==TIMER_1)
			  {
				  if(obj->timer_fun==NORMAL_MODE)
				  {
				  *(volatile unsigned char*)(TIMER_1+1) &=~(1<<0) &~(1<<1);
				  *(volatile unsigned char*)TIMER_1 &=~(1<<3) &~(1<<4);
				  }
				  else if(obj->timer_fun==PWM_PHASE_CORRECT)
				  {
				  *(volatile unsigned char*)(TIMER_1+1) |=(1<<0) &~(1<<1);
				  *(volatile unsigned char*)TIMER_1 &=~(1<<3) &~(1<<4);
				  }
				  else if(obj->timer_fun==CTC_MODE)
				  {
				  *(volatile unsigned char*)(TIMER_1+1) &=~(1<<0) &~(1<<1);
				  *(volatile unsigned char*)TIMER_1 |=(1<<3) &~(1<<4);
				  }
				  else if(obj->timer_fun==FAST_PWM)
				  {
				  *(volatile unsigned char*)(TIMER_1+1) &=~(1<<0) &~(1<<1);
			      *(volatile unsigned char*)TIMER_1 &=~(1<<3) |(1<<4);
				  }
				  config_interrupt_timer();
				 	   /*timer clock*/
				 /* *(volatile unsigned char*)obj->ins_timer=obj->freq;*/

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




ecore_s8 hal_start_timer(gcfg_hal_timer_t * obj)
{
	ecore_s8 ret_val = E_OK;
	if(obj != NULL)
	{
		if(obj->freq && obj->ins_timer && obj->timer_fun)
		{
         #if obj->ins_timer==TIMER_1
			*(volatile unsigned char*)obj->(ins_timer-1)=obj->freq;
         #endif

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




ecore_s8 hal_read_timer(gcfg_hal_timer_t * obj, ecore_u16 *timer_contain)
{
	ecore_s8 ret_val = E_OK;
	if(obj != NULL)
	{
        //#if obj->ins_timer==TIMER_1
		*timer_contain =*(volatile unsigned char*)obj->(ins_timer-2);
		*timer_contain >> 8 =*(volatile unsigned char*)obj->(ins_timer-3);
       // #endif

		*timer_contain=*(volatile unsigned char*)obj->ins_timer +1;
	}
    else
    {
	   	ret_val = INVALID_ARG;
    }
return ret_val;
}




ecore_s8 hal_is_timer_finish(gcfg_hal_timer_t * obj , bool_t * res)
{
	ecore_s8 ret_val = E_OK;
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




ecore_s8 hal_update_timer(gcfg_hal_timer_t * obj , ecore_u8 value)
{
	ecore_s8 ret_val = E_OK;
	if(obj != NULL)
	{
		*(volatile unsigned char*)obj->ins_timer +1 =value;

	}
    else
    {
	   	ret_val = INVALID_ARG;
    }
	return ret_val;
}




ecore_s8 hal_update_cmp_timer(gcfg_hal_timer_t * obj , ecore_u8 value)
{
	ecore_s8 ret_val = E_OK;
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



ecore_s8 hal_deinit_timer(gcfg_hal_timer_t * obj)
{
	ecore_s8 ret_val = E_OK;
	if(obj != NULL)
	{

         #if obj->ins_timer==TIMER_1
			*(volatile unsigned char*)obj->(ins_timer-1)=0;
         #endif
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

#ifdef RESOLUTION_IS_USED
ecore_s8 hal_init_timer_with_resolution(gcfg_hal_timer_t * obg, genum_res_t obj)
{
	ecore_s8 ret_val = E_OK;
	if((obg!=NULL)&&(ENUM_MIN_INDEX<obj)&&(ENUM_MIX_INDEX>obj))
	{
		if(obj==ONE_MICRO_SEC)
		{
			/*for timer0 resolution 1us*/
			TCCR0 |=(1<<0); // no pre_scaler 1us for each increase in timer0 256us
			TIMSK |=(1<<0); // interrupt enable TOIE0
			SREG  |=(1<<7);

		}
		else
		{
			/*the resolution in ms for timer1*/
			//static ecore_u16 val=((resolution*10^-3)/(0.125*10^-6));
			//val=(val-1+65535);
			TCNT1H=0xe0;//(val>>8);
			TCNT1L=0xc0;//(val<<8);
			TCCR1A=0;
			TCCR1B=0;
			TIMSK |=(1<<2); // interrupt enable TOIE1
			SREG  |=(1<<7);
		}

	}
	else
	{
		ret_val = INVALID_ARG;
	}



	return ret_val;

}
#endif
