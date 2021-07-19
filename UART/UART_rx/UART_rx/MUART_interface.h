/***********************************************/
/* Auther     : Mahmoud Aboelsaoud             */
/* Date       : 21 Jun 2021                    */
/* Version    : V01                            */
/*Description : Interface file                 */
/***********************************************/
#ifndef MUART_INTERFACE_H
#define MUART_INTERFACE_H

#include "STD_TYPES.h"

typedef enum
{
	UART_TX_OFF=0,
	UART_TX_ON =1 
}enum_tx_enable;

typedef enum
{
	UART_RX_OFF=0,
	UART_RX_ON =1
}enum_rx_enable;

typedef enum
{
	UART_RX_INT_OFF=0,
	UART_RX__INT_ON =1
}enum_rx_interrupt_enable;

typedef enum
{
	UART_TX_INT_OFF=0,
	UART_TX__INT_ON =1
}enum_tx_interrupt_enable;

typedef enum
{
	UART_UDRIE_INT_OFF=0,
	UART_UDRIE__INT_ON =1
}enum_DR_empty_interrupt_enable;

typedef enum
{
	ASYENCHRONOUS_USART=0,
	SYENCHRONOUS_USART=1
}enum_usart_mode;

typedef enum
{
	USART_PARITY_OFF  =0b00,
	USART_PARITY_EVEN =0b01,
	USART_PARITY_ODD  =0b11
}enum_usart_parity_mode;

typedef enum
{
	USART_ONE_STOP_BIT=0,
	USART_TWO_STOP_BIT=1
}enum_uart_stop_bit_num;

typedef enum
{
	USART_5_BITS=0b000,
	USART_6_BITS=0b001,
	USART_7_BITS=0b010,
	USART_8_BITS=0b011,
	USART_9_BITS=0b111,
}enum_uart_data_size; 

typedef enum
{
	USART_RISING_EDEG =0,
	USART_FALLING_EDEG =1
}enum_uart_clock_polarity;

typedef enum
{
	BAUD_RATE_2400=2400,
	BAUD_RATE_4800=4800,
	BAUD_RATE_9600=9600,
}enum_uart_baud_rate;


typedef enum
{
	ONE_CHARACTER,
	BULK_OF_CHARACTER,
}uart_data_t;



typedef struct
{
	enum_tx_enable 					 tx_enable;
	enum_rx_enable 			    	 rx_enable;
	enum_rx_interrupt_enable         rx_interrupt_enable;
	enum_tx_interrupt_enable         tx_interrupt_enable;
	enum_DR_empty_interrupt_enable   UDRIE_interrupt_enable;
	enum_uart_baud_rate              baud_rate; 
	enum_usart_mode                  usart_mode;
	enum_usart_parity_mode           parity;
	enum_uart_stop_bit_num           stop_bit_num ;
	enum_uart_data_size              data_size; 
	enum_uart_clock_polarity         clock_polarity;
}gstr_uart_t;






bool_t MUART_boolInit(gstr_uart_t *obj);
void   MUART_voidDeinitTransmition(gstr_uart_t *obj);
void   MUART_voidTransmitChar(u8 copy_u8Data);
void   MUART_voidTransmitString(u8 * copy_u8Data);
u8     MUART_u8Receive(void);
void   MUART_voidTxCallbackFunction(void(*copy_cbPtr)(void));
void   MUART_voidRxCallbackFunction(void(*copy_cbPtr)(void));







#endif 
