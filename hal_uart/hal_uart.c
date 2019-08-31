/*
 * hal_uart.c
 *
 *  Created on: Jul 31, 2018
 *      Author: Aboelsaoud ^_^
 */
#include"hal_uart.h"

static void(*rx)();
//static void(*tx)();
static void(*udr_emp)();

#ifdef RX
ISR(USART_RXC_vect)
{
	(*rx)();
}
#endif
/*
ISR(USART_TXC_vect)
{
	(*tx)();
}
*/
#ifdef TX
ISR(USART_UDRE_vect)
{
	(*udr_emp)();
}
#endif

static void interrput_config()
{
	SREG|=(1<<7);
	UCSRB |=(1<<5)|(1<<6)|(1<<7);

}
bool_t hal_init_uart(gstr_uart_t *obj, void*tx_rx_cb)
{

	bool_t ret_val=E_TRUE;
	if((obj!=NULL)&&(tx_rx_cb!=NULL))
	{
#ifdef TX
		udr_emp = tx_rx_cb;
#else
		rx = tx_rx_cb;
#endif

		
		/*UCSRB RXEN TXEN*/
		UCSRB |=(1<<3)|(1<<4);
		/*UCSRC 8 bit*/
		UCSRC |=(1<<1)|(1<<2)|(1<<7);

	
		if(obj->speed==BAUD_RATE_9600)
		{
		/*baud rate 9600   UBRRH UBRRL 0x0033*/
			UBRL =0x33;
			UBRH =0x00;
			interrput_config();
		}
		else if(obj->speed==BAUD_RATE_2400)
		{
			UBRL =0x00;

		}
	    else if(obj->speed==BAUD_RATE_4800)
		{
	    	UBRL =0x00;

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

#ifdef TX
bool_t hal_sent_uart(ecore_u8* tx_data)
{
  bool_t ret_val=E_TRUE;
  if(tx_data!=NULL)
  {
	  while(IS_BIT_CLEAR(UCSRA,5));
	  UDR=*tx_data;
  }
  else
  {
	  ret_val=E_FALSE;
  }

  return ret_val;
}
#endif

#ifdef RX
bool_t hal_recive_uart(ecore_u8 *rx_data)
{
bool_t ret_val=E_TRUE;
	if(rx_data!=NULL)
	{ 
		*rx_data=0;
		while(IS_BIT_CLEAR(UCSRA,7));
		*rx_data=UDR;
	}
	else
	{
		 ret_val=E_FALSE;
	}

	return ret_val;
}
#endif
