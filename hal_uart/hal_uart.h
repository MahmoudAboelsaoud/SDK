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

#define SREG   *(volatile unsigned char*)0x5f
#define UDR    *(volatile unsigned char*)0x2c
#define UCSRA  *(volatile unsigned char*)0x2b
#define UCSRB  *(volatile unsigned char*)0x2a
#define UCSRC  *(volatile unsigned char*)0x40
#define UBRL   *(volatile unsigned char*)0x29
#define UBRH   *(volatile unsigned char*)0x40



typedef enum
{
	ONE_CHARACTER,
	BULK_OF_CHARACTER,
}uart_data_t;

typedef enum
{
	BAUD_RATE_2400=2400,
	BAUD_RATE_4800=4800,
	BAUD_RATE_9600=9600,

}uart_speed_t;

typedef struct
{
	//uart_data_t data;
	uart_speed_t speed;

}gstr_uart_t;

bool_t hal_init_uart(gstr_uart_t *obj, void* tx_rx_cb);
#ifdef TX
bool_t hal_sent_uart(ecore_u8 *tx_data);
#endif
#ifdef RX
bool_t hal_recive_uart(ecore_u8* rx_data);
#endif

#endif /* HAL_UART_H_ */
