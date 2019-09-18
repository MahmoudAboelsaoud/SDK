/*
 * uart.c
 *
 *  Created on: Sep 11, 2019
 *      Author: M.Aboelsaoud
 */

#include "uart.h"

static  USART_Config *gstr_config_ptr;

static void (*ptr_to_rec_int)();
static void (*ptr_to_trans_int)();

ISR(USART_RXC_vect)
{
	(*ptr_to_rec_int)();
}

ISR(USART_TXC_vect)
{
	(*ptr_to_trans_int)();
}

bool_t USART_Init(USART_Config *gstr_config_uart)
{
	bool_t ret_val = E_TRUE;
	if(gstr_config_uart !=NULL)
	{
		gstr_config_ptr = gstr_config_uart;
		uint32 UBRR_VAL;
		if((gstr_config_uart->SYNCH_MOOD == USART_ASYNCH) && (gstr_config_uart->SPEED_MOOD == USART_NORMAL_SPEED))
		{
			UBRR_VAL= (uint32)((USART_FOSC/(16*USART_BAUD))-1);
		}
		else if((gstr_config_uart->SYNCH_MOOD == USART_ASYNCH) && (gstr_config_uart->SPEED_MOOD == USART_DOUBLE_SPEED))
		{
			UBRR_VAL= (uint32)((USART_FOSC/(8*USART_BAUD))-1);
		}
		else if(gstr_config_uart->SYNCH_MOOD == USART_ASYNCH)
		{
			UBRR_VAL= (uint32)((USART_FOSC/(2*USART_BAUD))-1);
		}
			/*for 1200 , 1000000 , UBRRH= 0011011>>8 , UBRRL=00110011*/
		UBRRH =(uint32)(UBRR_VAL >> 8);
		UBRRL =(uint32)UBRR_VAL;

		/****************Enable Transmitter*********/
		if(gstr_config_uart->TRANMIT == USART_TRANSMIT_ENABLE)
		{
			UCSRB = UCSRB |(1<<TXEN);
		}
		else if(gstr_config_uart->TRANMIT == USART_TRANSMIT_DISABLE)
		{
			UCSRB &= ~(1<<TXEN);
		}

		/****************Enable Receiver*********/
		if(gstr_config_uart->RECIEVE == USART_RECIEVE_ENABLE)
		{
			UCSRB = UCSRB |(1<<RXEN);
		}
		else if(gstr_config_uart->RECIEVE == USART_RECIEVE_DISABLE)
		{
			UCSRB &= ~(1<<RXEN);
		}

		/**********************Set character size*************/
		if(gstr_config_uart->CHAR_SIZE != USART_9_BIT_CHAR)
		{
			/* UCSRC = 10000000 | 00000110 =10000110 */
			UCSRC =(1 << URSEL)|(gstr_config_uart->CHAR_SIZE);
		}
		else if(gstr_config_uart->CHAR_SIZE == USART_9_BIT_CHAR)
		{
			/* UCSRC = 10000000 | (00001110 & 00000011)=10000110 ?!*/
			UCSRC =(1 << URSEL)|((gstr_config_uart->CHAR_SIZE)&0b11);
			UCSRB |=(1<<2);
		}
		/*************Set Double Bit*****************/
		if((gstr_config_uart->SYNCH_MOOD == USART_ASYNCH)&&(gstr_config_uart->SPEED_MOOD==USART_DOUBLE_SPEED))
		{
			UCSRA |= (1<<U2X);
		}
		/*****************Set Parity Bit**************/
		UCSRC|=(1<<URSEL)|(gstr_config_uart->PARITY_MOOD);
		/*****************Set Synch Asynch**************/
		UCSRC|=(1<<URSEL)|(gstr_config_uart->SYNCH_MOOD);
		/*****************Set Stop Bit**************/
		UCSRC|=(1<<URSEL)|(gstr_config_uart->STOPBIT);
		/*****************Reciever Intterput enable**************/
		UCSRB|=(gstr_config_uart->RECIVER_INT);
		/*****************Transmitter Intterput enable*********/
		UCSRB|=(gstr_config_uart->TRANSMITER_INT);

	}
	else
	{
		ret_val = NOT_VAILED_INPUT_PARMETERS;
	}
	return ret_val;
}



bool_t USART_Transmit(uint16 data)
{
	bool_t ret_val = E_TRUE;
	while(!(UCSRA &(1<<UDRE)));
	/**if the data is 9 bit , write the MSB first**/
	if(gstr_config_ptr->CHAR_SIZE == USART_9_BIT_CHAR)
	{
		UCSRB |= ((data>>8)&1);
	}

	UDR=(uint8)data;

	return ret_val;
}

uint8 USART_Receive(uint8* Ptr_To_Val)
{
	if(Ptr_To_Val != 0)
	{
	uint8 local_u8partityError = 0;
	* Ptr_To_Val =0;
	while(!(UCSRA &(1<<RXC)));
	/*************check parity error*********/
	if((((UCSRA>>PE))& 1)!=1)
	{
		if(gstr_config_ptr->CHAR_SIZE == USART_9_BIT_CHAR)
		{
			* Ptr_To_Val =((((UCSRA>>PE))& 1) <<8);
		}
		* Ptr_To_Val |=UDR;
		local_u8partityError =1;/*no error*/
	}
	return local_u8partityError;
	}

	else
	{
		return NOT_VAILED_INPUT_PARMETERS;
	}
}

bool_t USART_Rec_Int_Enable(void)
{
	bool_t ret_val = E_TRUE;

	UCSRB |=1<<RXCIE;

	return ret_val;
}

bool_t USART_Rec_Int_Disable(void)
{
	bool_t ret_val = E_TRUE;

	UCSRB &=~(1<<RXCIE);

	return ret_val;
}

bool_t USART_Trans_Int_Enable(void)
{
	bool_t ret_val = E_TRUE;

	UCSRB |=1<<TXCIE;

	return ret_val;
}

bool_t USART_Trans_Int_Disable(void)
{
	bool_t ret_val = E_TRUE;

	UCSRB &=~(1<<TXCIE);

	return ret_val;
}

bool_t USART_Rec_Enable(void)
{
	bool_t ret_val = E_TRUE;

	UCSRB |=1<<RXEN;

	return ret_val;
}

bool_t USART_Rec_Disable(void)
{
	bool_t ret_val = E_TRUE;

	UCSRB &=~(1<<RXEN);

	return ret_val;
}

bool_t USART_Trans_Enable(void)
{
	bool_t ret_val = E_TRUE;

	UCSRB |=1<<TXEN;

	return ret_val;
}

bool_t USART_Trans_Disable(void)
{
	bool_t ret_val = E_TRUE;

	UCSRB &=~(1<<TXEN);

	return ret_val;
}

bool_t USART_Callback_Res_Int(void(*Ptr_to_Func)(void))
{
	bool_t ret_val = E_TRUE;

	ptr_to_rec_int = Ptr_to_Func;

	return ret_val;
}

bool_t USART_Callback_Trans_Int(void(*Ptr_to_Func)(void))
{
	bool_t ret_val = E_TRUE;

	ptr_to_trans_int = Ptr_to_Func;

	return ret_val;
}





