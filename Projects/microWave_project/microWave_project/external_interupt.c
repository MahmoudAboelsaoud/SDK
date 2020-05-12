/*
 * external_interupt.c
 *
 *  Created on: Jul 29, 2019
 *      Author: M.Aboelsaoud
 */

#include "external_interrupt.h"

static void (*cb_int0)(void);
static void (*cb_int1)(void);

#ifdef INT2
static void (*cb_int2)(void);
#endif

ISR(INT0_vect)
{
	/*callback function from INT0 */
	 (*cb_int0)();
}

ISR(INT1_vect)
{
	/*callback function from INT1 */
	 (*cb_int1)();
}

#ifdef INT2
ISR(INT2_vect)
{
	/*callback function from INT2*/
	 (*cb_int2)();
}
#endif

static void interrupt_config(void)
{
	
	 /*enable INT0 , INT1, INT2*/
	GICR |=(1<<6)|(1<<7);
	//SREG  = (1<<7);
			 
}


bool_t hal_ex_interrupt_Initi(gstr_ext_interrupt_config *str_config)
{

 bool_t ret_val =E_TRUE ;

 if(str_config != NULL)
 {
	
		interrupt_config();
	 if((str_config ->interrupt_number == INT_0) && (str_config->cb_fun_ptr !=NULL))
	 {
		 
			cb_int0 = (void(*)(void))(str_config->cb_fun_ptr);
			
			 /*set the level configuration */
			 if(str_config->interrupt_level==LOW_LEVEL)
				 /*LOW_LEVEL*/
			  MCUCR &=~(1<<0)&~(1<<1);

			 if(str_config->interrupt_level==ANY_CHANGE)
				 /*ANY_CHANGE*/
			   MCUCR |=(1<<0)&~(1<<1);

			 if(str_config->interrupt_level==RISING_EDAGE)
				 /*RISING_EDAGE*/
			  MCUCR |=(1<<0)|(1<<1);

			 if(str_config->interrupt_level==FALLING_EDAGE)
				 /*FALLING_EDAGE*/
			  MCUCR &=~(1<<0)|(1<<1);
			  
			  
			  CLEAR_PIN(DIR_PORTD,2);
			 
	 }


	 else if((str_config ->interrupt_number == INT_1) && (str_config->cb_fun_ptr !=NULL))
		 {
		  		
			cb_int1 = (void(*)(void))(str_config->cb_fun_ptr);
				  
			 /*set the level configuration */
			 if(str_config->interrupt_level==LOW_LEVEL)
				 /*LOW_LEVEL*/
			  MCUCR &=~(1<<2)&~(1<<3);

			 if(str_config->interrupt_level==ANY_CHANGE)
			 	 /*ANY_CHANGE*/
			   MCUCR |=(1<<2)&~(1<<3);

			 if(str_config->interrupt_level==RISING_EDAGE)
			 	 /*RISING_EDAGE*/
			  MCUCR |=(1<<2)|(1<<3);

			 if(str_config->interrupt_level==FALLING_EDAGE)
			     /*FALLING_EDAGE*/
			  MCUCR &=~(1<<2)|(1<<3);
	
				 CLEAR_PIN(DIR_PORTD,3);
			  
		 }
#ifdef INT2
	 else if((str_config ->interrupt_number == INT_2) && (str_config->cb_fun_ptr !=NULL))
	  	 {
		 cb_int2 = (void(*)(void))(str_config->cb_fun_ptr);
			 /*set the level configuration */
			 if(str_config->interrupt_level==RISING_EDAGE)
				 /*RISING_EDAGE*/
		     	  MCUCSR |=(1<<6);
			if(str_config->interrupt_level==FALLING_EDAGE)
				 /*FALLING_EDAGE*/
	    	  MCUCSR &=~(1<<6);

				   /*enable INT2*/
				 CLEAR_PIN(DIR_PORTB,2);
				 GICR = (1<<5);
				// SREG = (1<<7);
	  	 }
#endif
	 else
	 {
		 ret_val = E_FALSE;
	 }

 }
 else
 {
	 ret_val = E_FALSE;
 }
 
 // SREG = (1<<7);
	
return ret_val;
}
