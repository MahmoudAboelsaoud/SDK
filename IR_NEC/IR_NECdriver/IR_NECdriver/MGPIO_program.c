/***********************************************/
/* Auther     : Mahmoud Aboelsaoud             */
/* Date       : 30 Jun 2021                    */
/* Version    : V02                            */
/*Description : code file                      */
/***********************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MGPIO_interface.h"
#include "MGPIO_private.h"
#include "MGPIO_config.h"


bool_t MGPIO_SetPortDirection( u8 Copy_Port, u8 Copy_Pin, u8 Copy_ProtDir)
{
	bool_t ret_val = E_TRUE;
	if(Copy_ProtDir == OUTPUT)
	{
		if     (Copy_Port == PORTA)  SET_BIT(DIR_DDRA,Copy_Pin);
		else if(Copy_Port == PORTB)  SET_BIT(DIR_DDRB,Copy_Pin);
		else if(Copy_Port == PORTC)  SET_BIT(DIR_DDRC,Copy_Pin);
		else if(Copy_Port == PORTD)  SET_BIT(DIR_DDRD,Copy_Pin);
		else ret_val = E_FALSE;
	}
	else
	{
		if     (Copy_Port == PORTA)  CLR_BIT(DIR_DDRA,Copy_Pin);
		else if(Copy_Port == PORTB)  CLR_BIT(DIR_DDRB,Copy_Pin);
		else if(Copy_Port == PORTC)  CLR_BIT(DIR_DDRC,Copy_Pin);
		else if(Copy_Port == PORTD)  CLR_BIT(DIR_DDRD,Copy_Pin);
		else ret_val = E_FALSE;
		
	}
	return ret_val;
}


bool_t MGPIO_SetPin  (u8 Copy_Port, u8 Copy_Pin)
{
	bool_t ret_val = E_TRUE;
	
	if     (Copy_Port == PORTA)  SET_BIT(OUT_PORTA,Copy_Pin);
	else if(Copy_Port == PORTB)  SET_BIT(OUT_PORTB,Copy_Pin);
	else if(Copy_Port == PORTC)  SET_BIT(OUT_PORTC,Copy_Pin);
	else if(Copy_Port == PORTD)  SET_BIT(OUT_PORTD,Copy_Pin);
	else ret_val = E_FALSE;
	
	return ret_val;
}


bool_t MGPIO_ClearPin(u8 Copy_Port, u8 Copy_Pin)
{
	bool_t ret_val = E_TRUE;
	if     (Copy_Port == PORTA)  CLR_BIT(OUT_PORTA,Copy_Pin);
	else if(Copy_Port == PORTB)  CLR_BIT(OUT_PORTB,Copy_Pin);
	else if(Copy_Port == PORTC)  CLR_BIT(OUT_PORTC,Copy_Pin);
	else if(Copy_Port == PORTD)  CLR_BIT(OUT_PORTD,Copy_Pin);
	else ret_val = E_FALSE;
	
	
	return ret_val;
}


bool_t MGPIO_TogalPin(u8 Copy_Port, u8 Copy_Pin)
{
	bool_t ret_val = E_TRUE;
	
	if     (Copy_Port == PORTA)  TOG_BIT(OUT_PORTA,Copy_Pin);
	else if(Copy_Port == PORTB)  TOG_BIT(OUT_PORTB,Copy_Pin);
	else if(Copy_Port == PORTC)  TOG_BIT(OUT_PORTC,Copy_Pin);
	else if(Copy_Port == PORTD)  TOG_BIT(OUT_PORTD,Copy_Pin);
	
	return ret_val;
}
