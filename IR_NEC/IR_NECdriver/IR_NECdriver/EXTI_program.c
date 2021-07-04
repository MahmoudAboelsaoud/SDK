/**********************************************/
/* Auther : Mahmoud Aboelsaoud                */
/* Version: v2                                */
/* Data   : 28 may 2021                       */
/* Description   : external interupt code     */
/**********************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "EXTI_config.h"
#include "EXTI_private.h"
#include "EXTI_interface.h"

static void  (*cb_int0)(void);
static void  (*cb_int1)(void);
static void  (*cb_int2)(void);


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

ISR(INT2_vect)
{
	/*callback function from INT2*/
	 (*cb_int2)();
}

bool_t Hal_Ext_Interrupt_Init(gstr_ext_interrupt_config *str_config)
{

 bool_t ret_val =E_TRUE ;

 if(str_config != NULL)
 {
	 if((str_config ->interrupt_number == INT_0))
	 {
		 
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
			  
			  GICR = (1<<6);
			  CLR_BIT(DDRD,2);
			 
	 }


	 else if((str_config ->interrupt_number == INT_1))
		 {
				  
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
				  GICR = (1<<7);
				 CLR_BIT(DDRD,3);
			  
		 }

	 else if((str_config ->interrupt_number == INT_2))
	  	 {
			 /*set the level configuration */
			 if(str_config->interrupt_level==RISING_EDAGE)
				 /*RISING_EDAGE*/
		     	  MCUCSR |=(1<<6);
			if(str_config->interrupt_level==FALLING_EDAGE)
				 /*FALLING_EDAGE*/
	    	  MCUCSR &=~(1<<6);

				   /*enable INT2*/
				 CLR_BIT(DDRB,2);
				 GICR = (1<<5);
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
 
  SREG = (1<<7);
	
return ret_val;
}

bool_t Hal_Ext_Interrupt_Cb_INT0(void (*ext_cb_function)(void))
{
	cb_int0 = ext_cb_function;
}


bool_t Hal_Ext_Interrupt_Cb_INT1(void (*ext_cb_function)(void))
{
	cb_int1 = ext_cb_function;
}


bool_t Hal_Ext_Interrupt_Cb_INT2(void (*ext_cb_function)(void))
{
	cb_int2 = ext_cb_function;
}
