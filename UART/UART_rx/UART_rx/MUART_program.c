/***********************************************/
/* Auther     : Mahmoud Aboelsaoud             */
/* Date       : 5 Jul 2021                     */
/* Version    : V01                            */
/*Description : cdoe file                      */
/***********************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "MUART_private.h"
#include "MUART_interface.h"
#include "MUART_config.h"

static void (*uart_RxCallBack)(void);
static void (*uart_TxCallBack)(void);


ISR(USART_RXC_vect)
{
	(*uart_RxCallBack)();
}

ISR(USART_TXC_vect)
{
	(*uart_TxCallBack)();
}


ISR(USART_UDRE_vect)
{
	(*uart_TxCallBack)();
}


bool_t MUART_boolInit(gstr_uart_t *obj)
{
	bool_t ret_val = E_TRUE;
	if(obj != NULL)
	{
	/**set the URSEL bit to can writing on UCSRC register SET_BIT(UCSRC,URSEL);***/
			SET_BIT(UCSRC,URSEL);
			/*******mode selection*******/
		if(obj->usart_mode==ASYENCHRONOUS_USART)
			CLR_BIT(UCSRC,UMSEL);
			/******parity selection*******/
		if(obj->parity==USART_PARITY_OFF)
			{
				CLR_BIT(UCSRC,UPM0);
				CLR_BIT(UCSRC,UPM1);
			}
		else if(obj->parity==USART_PARITY_EVEN)
			{
				CLR_BIT(UCSRC,UPM0);
				SET_BIT(UCSRC,UPM1);
			}
		else
			{
				SET_BIT(UCSRC,UPM0);
				SET_BIT(UCSRC,UPM1);
			}
	  /***********stop bit number**********/
		if(obj->stop_bit_num==USART_ONE_STOP_BIT)
				CLR_BIT(UCSRC,USBS);
		else
		     	SET_BIT(UCSRC,USBS);
	 /***********data size send**********/
		if(obj->data_size==USART_8_BITS)
			{
				//UCSRC |=(1<<UCSZ0)|(1<<UCSZ1)|(1<<URSEL);
				SET_BIT(UCSRC,UCSZ0);
				SET_BIT(UCSRC,UCSZ1);
				CLR_BIT(UCSRB,UCSZ2);
			}
		else if(obj->data_size==USART_5_BITS)
			{
			//UCSRC &=~(1<<UCSZ1)&(1<<UCSZ1)|(1<<URSEL);
			CLR_BIT(UCSRC,UCSZ0);
			CLR_BIT(UCSRC,UCSZ1);
			CLR_BIT(UCSRC,UCSZ2);
			}
		else if(obj->data_size==USART_6_BITS)
			{
			SET_BIT(UCSRC,UCSZ0);
			CLR_BIT(UCSRC,UCSZ1);
			CLR_BIT(UCSRC,UCSZ2);
			}
		else if(obj->data_size==USART_7_BITS)
			{
				CLR_BIT(UCSRC,UCSZ0);
				SET_BIT(UCSRC,UCSZ1);
				CLR_BIT(UCSRC,UCSZ2);
			}
		else 
			{
			SET_BIT(UCSRC,UCSZ0);
			SET_BIT(UCSRC,UCSZ1);
			SET_BIT(UCSRC,UCSZ2);
			}
	/************ clock polarity selection******/
		if(obj->clock_polarity==USART_RISING_EDEG)
			CLR_BIT(UCSRC,UCPOL);
		else
			SET_BIT(UCSRC,UCPOL);
	/*********** RX enable*****************/
		if(obj->rx_enable==UART_RX_ON)
			SET_BIT(UCSRB,RXEN);	
		else
			CLR_BIT(UCSRB,RXEN);
	/*************** TX enable************/
		if(obj->tx_enable==UART_TX_ON)
			SET_BIT(UCSRB,TXEN);
		else
			CLR_BIT(UCSRB,TXEN);
	/*********TX interrupt enable*******/	
		if(obj->tx_interrupt_enable==UART_TX__INT_ON)
			SET_BIT(UCSRB,TXCIE);
		else
			CLR_BIT(UCSRB,TXCIE);
   /*********RX interrupt enable********/
		if(obj->rx_interrupt_enable==UART_RX__INT_ON)
			SET_BIT(UCSRB,RXCIE);
		else
			CLR_BIT(UCSRB,RXCIE);
	/**********UDRIE interrupt enable********/
		if(obj->UDRIE_interrupt_enable==UART_UDRIE__INT_ON)
			SET_BIT(UCSRB,UDRIE);
		else
			CLR_BIT(UCSRB,UDRIE);
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

void MUART_voidTransmitChar(u8 copy_u8Data)
{
	UDR = copy_u8Data;
	while(!GET_BIT(UCSRA,UDRE));
}

void MUART_voidTransmitString(u8 * copy_u8Data)
{
	u8 counter = 0;
	while(*(copy_u8Data + counter) != '\0')
	{
		UDR = *(copy_u8Data + counter);
		while(!GET_BIT(UCSRA,UDRE));
		counter++;
	}
}

u8   MUART_u8Receive(void)
{
	while(!GET_BIT(UCSRA,RXC));
	return (u8)UDR;
}


void MUART_voidDeinitTransmition(gstr_uart_t *obj)
{
	/*********** RX enable*****************/
	if(obj->rx_enable==UART_RX_ON)
	CLR_BIT(UCSRB,RXEN);
	/*************** TX enable************/
	if(obj->tx_enable==UART_TX_ON)
	CLR_BIT(UCSRB,TXEN);
	
	UBRL =0x00;
	UBRH =0x00;
}

void MUART_voidTxCallbackFunction(void(*copy_cbPtr)(void))
{
	uart_TxCallBack = copy_cbPtr;	
}
void MUART_voidRxCallbackFunction(void(*copy_cbPtr)(void))
{
	uart_RxCallBack =  copy_cbPtr;
}

