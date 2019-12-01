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
			
			
			   
				
	/**set the URSEL bit to can writing on UCSRC register SET_BIT(UCSRC,URSEL);***/
			SET_BIT(UCSRC,URSEL);
			/*******mode selection*******/
		if(obj->usart_mode==ASYENCHRONOUS_USART)
			CLEAR_BIT(UCSRC,UMSEL);
			/******parity selection*******/
		if(obj->parity==USART_PARITY_OFF)
			{
				CLEAR_BIT(UCSRC,UPM0);
				CLEAR_BIT(UCSRC,UPM1);
			}
		else if(obj->parity==USART_PARITY_EVEN)
			{
				CLEAR_BIT(UCSRC,UPM0);
				SET_BIT(UCSRC,UPM1);
			}
		else
			{
				SET_BIT(UCSRC,UPM0);
				SET_BIT(UCSRC,UPM1);
			}
	  /***********stop bit number**********/
		if(obj->stop_bit_num==USART_ONE_STOP_BIT)
				CLEAR_BIT(UCSRC,USBS);
		else
		     	SET_BIT(UCSRC,USBS);
	 /***********data size send**********/
		if(obj->data_size==USART_8_BITS)
			{
				//UCSRC |=(1<<UCSZ0)|(1<<UCSZ1)|(1<<URSEL);
				SET_BIT(UCSRC,UCSZ0);
				SET_BIT(UCSRC,UCSZ1);
				CLEAR_BIT(UCSRB,UCSZ2);
			}
		else if(obj->data_size==USART_5_BITS)
			{
			//UCSRC &=~(1<<UCSZ1)&(1<<UCSZ1)|(1<<URSEL);
			CLEAR_BIT(UCSRC,UCSZ0);
			CLEAR_BIT(UCSRC,UCSZ1);
			CLEAR_BIT(UCSRC,UCSZ2);
			}
		else if(obj->data_size==USART_6_BITS)
			{
			SET_BIT(UCSRC,UCSZ0);
			CLEAR_BIT(UCSRC,UCSZ1);
			CLEAR_BIT(UCSRC,UCSZ2);
			}
		else if(obj->data_size==USART_7_BITS)
			{
				CLEAR_BIT(UCSRC,UCSZ0);
				SET_BIT(UCSRC,UCSZ1);
				CLEAR_BIT(UCSRC,UCSZ2);
			}
		else 
			{
			SET_BIT(UCSRC,UCSZ0);
			SET_BIT(UCSRC,UCSZ1);
			SET_BIT(UCSRC,UCSZ2);
			}
	/************ clock polarity selection******/
		if(obj->clock_polarity==USART_RISING_EDEG)
				CLEAR_BIT(UCSRC,UCPOL);
		else
			SET_BIT(UCSRC,UCPOL);
	/*********** RX enable*****************/
		if(obj->rx_enable==UART_RX_ON)
			SET_BIT(UCSRB,RXEN);	
		else
			CLEAR_BIT(UCSRB,RXEN);
	/*************** TX enable************/
		if(obj->tx_enable==UART_TX_ON)
			SET_BIT(UCSRB,TXEN);
		else
			CLEAR_BIT(UCSRB,TXEN);
	/*********TX interrupt enable*******/	
		if(obj->tx_interrupt_enable==UART_TX__INT_ON)
			SET_BIT(UCSRB,TXCIE);
		else
			CLEAR_BIT(UCSRB,TXCIE);
   /*********RX interrupt enable********/
		if(obj->rx_interrupt_enable==UART_RX__INT_ON)
			SET_BIT(UCSRB,RXCIE);
		else
			CLEAR_BIT(UCSRB,RXCIE);
	/**********UDRIE interrupt enable********/
		if(obj->UDRIE_interrupt_enable==UART_UDRIE__INT_ON)
			SET_BIT(UCSRB,UDRIE);
		else
			CLEAR_BIT(UCSRB,UDRIE);
	/************Baud rate setting***********/
		if(obj->baud_rate==BAUD_RATE_9600)
			{
				UBRL =0x33;
				UBRH =0x00;
			}
		else if(obj->baud_rate==BAUD_RATE_2400)
		{
			UBRL =0x00;
			UBRH =0x00;
		}
		else if(obj->baud_rate==BAUD_RATE_4800)
		{
			UBRL =0x00;
			UBRH =0x00;
		}
		
		/***turn on the galoble interrupt***/
		SET_BIT(SREG,7);
		
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
	if(/*rx_data!=NULL*/ 1)
	{ 
		//*rx_data=0xff;         
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
