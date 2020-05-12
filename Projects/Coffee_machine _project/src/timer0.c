/*
 * timer0.c

 *
 *  Created on: Apr 28, 2020
 *      Author: M.Aboelsaoud
 */

#include "timer0.h"


static void (*ptr_to_OVFI)(void);
static void (*ptr_to_OCMI)(void);

ISR(TIMER0_OVF_vect)
{
	(*ptr_to_OVFI)();
}

ISR(TIMER0_COMP_vect)
{
	(*ptr_to_OCMI)();
}
static uint_8 TOV_Number;

bool_t TMR0_INIT(STIMER0_SETTINGS * tmr0_configuration)
{
	bool_t ret_val = E_TRUE;
	if(tmr0_configuration != NULL)
	{
	/** TIMER0 Adjust Mode**/
		if(tmr0_configuration->Timer0_Mode==NORMAL)
		{
			TCCR0 &=~(1<<WGM00);
			TCCR0 &=~(1<<WGM01);
		}
		else if(tmr0_configuration->Timer0_Mode==CTC)
		{
			TCCR0 &=~(1<<WGM00);
			TCCR0 |=(1<<WGM01);
		}
		else
		{
			ret_val = E_FALSE;
		}

		/** TIMER0 Adjust prescalar**/
		TCCR0 |=(tmr0_configuration->Timer0_Prescalar);
		/**TMR0 Enbale/Disable**/
		if(tmr0_configuration->Timer0_OVFI ==TOIE0_ENABLE)
		{
			TIMSk|=(1<<TOIE0);
		}
		else if(tmr0_configuration->Timer0_OVFI ==TOIE0_DISABLE)
		{
			TIMSk&=~(1<<TOIE0);
		}
		else
		{
			ret_val = E_FALSE;
		}

		/**OCR0 Enbale/Disable**/
		if(tmr0_configuration->Timer0_OCIE ==OCIE0_ENABLE)
		{
			TIMSk|=(1<<OCIE0);
		}
		else if(tmr0_configuration->Timer0_OCIE ==OCIE0_DISABLE)
		{
			TIMSk&=~(1<<OCIE0);
		}
		else
		{
			ret_val = E_FALSE;
		}

	}
	else
	{
		ret_val = E_FALSE;
	}


	return ret_val;
}
bool_t TMR0_ReadCounterValue(uint_8 *numberOfTicks)
{
	bool_t ret_val = E_TRUE;

   *numberOfTicks=TCNT0;

	return ret_val;
}

bool_t TMR0_Set_Counter_Value(uint_8 val)
{
	bool_t ret_val = E_TRUE;

	TCNT0 =val;
	return ret_val;
}
bool_t TMR0_Set_Compare_Value(uint_8 val)
{
	bool_t ret_val = E_TRUE;

	OCR0 = val;

	return ret_val;
}

bool_t TMR0_Set_TOV_Number(uint_8 val)
{
	bool_t ret_val = E_TRUE;

	TOV_Number=val;

	return ret_val;
}
bool_t TMR0_Get_TOV_Number(uint_8 *val)
{
	bool_t ret_val = E_TRUE;
	*val=TOV_Number;
	return ret_val;
}

/** SW counter**/
bool_t TMR0_Get_Ticks_of_SWcounter(uint_32 *val)
{
	bool_t ret_val = E_TRUE;
	*val =256*TOV_Number + TCNT0;
	return ret_val;
}

bool_t callback_TMR0_Overflow_Interrupt(void(*Ptr_to_OVI_function)(void))
{
	bool_t ret_val = E_TRUE;
	ptr_to_OVFI = Ptr_to_OVI_function;
	return ret_val;

}
bool_t callback_TMR0_Compare_Match_Interrupt(void(*Ptr_to_OCM_function)(void))
{
	bool_t ret_val = E_TRUE;
	ptr_to_OCMI = Ptr_to_OCM_function;
	return ret_val;

}


