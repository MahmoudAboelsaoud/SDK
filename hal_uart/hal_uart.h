/*
 * uart.h
 *
 *  Created on: Jul 31, 2018
 *      Author: Aboelsaoud ^_^
 */
#ifndef HAL_UART_H_
#define HAL_UART_H_
#include"commen.h"
#include"hal_uart_config.h"
#include"macros_commen.h"
/*********************Registers*******************/
#define SREG   *(volatile unsigned char*)0x5f
#define UDR    *(volatile unsigned char*)0x2c
#define UCSRA  *(volatile unsigned char*)0x2b
#define UCSRB  *(volatile unsigned char*)0x2a
#define UCSRC  *(volatile unsigned char*)0x40
#define UBRL   *(volatile unsigned char*)0x29
#define UBRH   *(volatile unsigned char*)0x40
/******************UCSRA**************************/
#define  MPCM   0
#define  U2X    1
#define  PE     2
#define  U2X    3
#define  FE     4
#define  UDRE   5
#define  TXC    6
#define  RXC    7
/******************UCSRB**************************/
#define  TXB8    0
#define  RXB8    1
#define  UCSZ2   2
#define  TXEN    3
#define  RXEN    4
#define  UDRIE   5
#define  TXIC    6
#define  RXIC    7
/******************UCSRC**************************/
#define  UCPOL  0
#define  UCSZ0  1
#define  UCSZ1  2
#define  USBS   3
#define  UPM0   4
#define  UPM1   5
#define  UMSEL  6
#define  URSEL  7

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
	USART_PARITY_OFF=0b00,
	USART_PARITY_EVEN=0b01,
	USART_PARITY_ODD=0b11
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
	enum_tx_enable tx_enable;
	enum_rx_enable rx_enable;
	enum_rx_interrupt_enable rx_interrupt_enable;
	enum_tx_interrupt_enable tx_interrupt_enable;
	enum_DR_empty_interrupt_enable UDRIE_interrupt_enable;
	enum_uart_baud_rate baud_rate; 
	enum_usart_mode usart_mode;
	enum_usart_parity_mode parity;
	enum_uart_stop_bit_num stop_bit_num ;
	enum_uart_data_size data_size; 
	enum_uart_clock_polarity clock_polarity;
}gstr_uart_t;





bool_t hal_init_uart(gstr_uart_t *obj, void* tx_rx_cb);
#ifdef TX
bool_t hal_sent_uart(ecore_u8 *tx_data);
#endif
#ifdef RX
bool_t hal_recive_uart(ecore_u8* rx_data);
#endif

#endif /* HAL_UART_H_ */
