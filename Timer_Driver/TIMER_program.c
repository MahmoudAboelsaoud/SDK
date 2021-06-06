/**********************************************/
/* Auther : Mahmoud Aboelsaoud                */
/* Version: v2                                */
/* Data   : 31 may 2021                       */
/* Description   : Timers code                */
/**********************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_config.h"
#include "TIMER_private.h"
#include "TIMER_interface.h"

static u8 timer_init_flag = 0;

static void (*cb_fun_t0_ovf_normal)(void);
static void (*cb_comp_t0_ctc)(void);

static void (*cb_fun_t2_ovf_normal)(void);
static void (*cb_comp_t2_ctc)(void);


ISR(TIMER0_OVF_vect)
{
   (*cb_fun_t0_ovf_normal)();
}

ISR(TIMER0_COMP_vect)
{
	(*cb_comp_t0_ctc)();
}


ISR(TIMER2_OVF_vect)
{
   (*cb_fun_t2_ovf_normal)();
}

ISR(TIMER2_COMP_vect)
{
	(*cb_comp_t2_ctc)();
}


static void  interupt_config()
{
	*(volatile unsigned char*)0x5f |=(1<<7); // I
}

su8 hal_init_timer(gcfg_hal_timer_t * obj)
{
	su8 ret_val = E_OK;
	if(obj != NULL)
	{
		if( obj->freq && obj->ins_timer && obj->timer_fun && obj->ptr_to_timer_handler!=NULL )
		{
			 if( obj->ins_timer==TIMER_0)
			 {
				 if(obj->timer_fun==NORMAL_MODE)
				 {
					 cb_fun_t0_ovf_normal = obj->ptr_to_timer_handler;
					 TCCR0 &=~(1<<3) &~(1<<6); /*mode select*/
					 TIMSK |= (1<<0);          /*Interrupt Enable*/
					 timer_init_flag = 1;
				 }
				 else if(obj->timer_fun==PWM_PHASE_CORRECT)
				 {
					 TCCR0 |=(1<<3) &~(1<<6); /*mode select*/
					 timer_init_flag = 0;
				 }
				 else if(obj->timer_fun==CTC_MODE)
				 {
					 cb_comp_t0_ctc = obj->ptr_to_timer_handler;
					 TCCR0 |=(1<<6) &~(1<<3); /*mode select*/
					 TIMSK |= (1<<1);         /*Interrupt Enable*/
					 timer_init_flag = 0;
				 }
				 else if(obj->timer_fun==FAST_PWM)
				 {
					  TCCR0 |=(1<<3) |(1<<6); /*mode select*/
					  timer_init_flag = 0;
				 }
				 else
				 {
					 ret_val = MODE_ERROR;
				 }
				 interupt_config();	 
			 }
			 
			  else if(obj->ins_timer==TIMER_2)
			  {
				 if(obj->timer_fun==NORMAL_MODE)
				 {
					 cb_fun_t2_ovf_normal = obj->ptr_to_timer_handler;
					 TCCR2 &=~(1<<3) &~(1<<6); /*mode select*/
					 TIMSK |= (1<<6);          /*Interrupt Enable*/
					 timer_init_flag = 2;
				 }
				 else if(obj->timer_fun==PWM_PHASE_CORRECT)
				 {
					 TCCR2 |=(1<<3) &~(1<<6); /*mode select*/
					 timer_init_flag = 2;
				 }
				 else if(obj->timer_fun==CTC_MODE)
				 {
					 cb_comp_t2_ctc = obj->ptr_to_timer_handler;
					 TCCR2 |=(1<<6) &~(1<<3); /*mode select*/
					 TIMSK |= (1<<7);         /*Interrupt Enable*/
					 timer_init_flag = 2;
				 }
				 else if(obj->timer_fun==FAST_PWM)
				 {
					 TCCR2 |=(1<<3) |(1<<6); /*mode select*/
					 timer_init_flag = 2;
				 }
				 else
				 {
					 ret_val = MODE_ERROR;
				 }
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


su8 hal_start_timer(gcfg_hal_timer_t * obj)
{
	su8 ret_val = E_OK;
	if(obj != NULL && timer_init_flag !=0)
	{
	  if (obj->ins_timer == TIMER_0)
	  {
		  TCCR0 |= obj->freq;
	  }
	  else if(obj->ins_timer == TIMER_1)
	  {
		  /*Not handled yet*/
	  }
	  else if(obj->ins_timer == TIMER_2)
	  {
		  TCCR2 |= obj->freq;
	  }
	  else
	  {
		ret_val = INVALID_TIMER;
	  } 
	}
	else
	{
		ret_val = E_NOK;
	}
	
	return ret_val;
}

su8 hal_read_timer(gcfg_hal_timer_t * obj, u8 *timer_contain)
{
	su8 ret_val = E_OK;
	if(obj != NULL && timer_contain!= NULL &&timer_init_flag !=0)
	{
		if (obj->ins_timer == TIMER_0)
		{
			*timer_contain = TCNT0;
		}
		else if(obj->ins_timer == TIMER_1)
		{
			/*Not handled yet*/
		}
		else if(obj->ins_timer == TIMER_2)
		{
			*timer_contain = TCNT2;
		}
		else
		{
			ret_val = INVALID_TIMER;
		}
	}
	else
	{
		ret_val = E_NOK;
	}

	return ret_val;
}


su8 hal_is_timer_finish(gcfg_hal_timer_t * obj , bool_t * res)
{
	su8 ret_val = E_OK;
	if(obj != NULL && res!= NULL &&timer_init_flag !=0)
	{
		if (obj->ins_timer == TIMER_0)
		{
			if(obj->timer_fun == NORMAL_MODE)
				*res = GET_BIT(TIFR, 0);
			else
				*res = GET_BIT(TIFR, 1);
		}
		else if(obj->ins_timer == TIMER_1)
		{
			/*Not handled yet*/
		}
		else if(obj->ins_timer == TIMER_2)
		{
			if(obj->timer_fun == NORMAL_MODE)
				*res = GET_BIT(TIFR, 6);
			else
				*res = GET_BIT(TIFR, 7);
		}
		else
		{
			ret_val = INVALID_TIMER;
		}
	}
	else
	{
		ret_val = E_NOK;
	}

	return ret_val;
	
}


su8 hal_update_init_timer_value(gcfg_hal_timer_t * obj , u8 value)
{
	su8 ret_val = E_OK;
	if(obj != NULL &&timer_init_flag !=0)
	{
		if (obj->ins_timer == TIMER_0)
		{
			 TCNT0 = value;
		}
		else if(obj->ins_timer == TIMER_1)
		{
			/*Not handled yet*/
		}
		else if(obj->ins_timer == TIMER_2)
		{
			TCNT2 = value;
		}
		else
		{
			ret_val = INVALID_TIMER;
		}
	}
	else
	{
		ret_val = E_NOK;
	}

	return ret_val;
}

su8 hal_update_cmp_timer(gcfg_hal_timer_t * obj , u8 value)
{
	 su8 ret_val = E_OK;
	 if(obj != NULL &&timer_init_flag !=0)
		{
			if (obj->ins_timer == TIMER_0)
			{
				OCR0 = value;
			}
			else if(obj->ins_timer == TIMER_1)
			{
				/*Not handled yet*/
			}
			else if(obj->ins_timer == TIMER_2)
			{
				OCR2 = value;
			}
			else
			{
				ret_val = INVALID_TIMER;
			}
		}
		else
		{
			ret_val = E_NOK;
		}

		return ret_val;
}

su8 hal_deinit_timer(gcfg_hal_timer_t * obj)
{
	   su8 ret_val = E_OK;
	   if(obj != NULL &&timer_init_flag !=0)
		 {
			 if (obj->ins_timer == TIMER_0)
			 {
				 obj->freq = NO_CLOCK;
				 timer_init_flag =0;
			 }
			 else if(obj->ins_timer == TIMER_1)
			 {
				 /*Not handled yet*/
			 }
			 else if(obj->ins_timer == TIMER_2)
			 {
				obj->freq = NO_CLOCK;
				timer_init_flag = 0;
			 }
			 else
			 {
				 ret_val = INVALID_TIMER;
			 }
		 }
		 else
		 {
			 ret_val = E_NOK;
		 }

		 return ret_val;
}