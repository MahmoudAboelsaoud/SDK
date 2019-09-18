/*
 * uart.h
 *
 *  Created on: Sep 11, 2019
 *      Author: M.Aboelsaoud
 */

#ifndef UART_H_
#define UART_H_
#include "commen.h"
#include"ERRORS_DEF.h"

#define USART_BAUD 1200
#define USART_FOSC 1000000

/**********************UCSRA************************/
#define RXC 	7
#define TXC 	6
#define UDRE 	5
#define FE 		4
#define DOR		3
#define PE 		2
#define U2X		1
#define MPCM	0

/**********************UCSRB************************/
#define RXCIE 	7
#define TXCIE	6
#define UDRIE	5
#define RXEN 	4
#define TXEN	3
#define UCSZ2	2
#define RXB8	1
#define TXB8	0

/**********************UCSRC************************/
#define URSEL	7
#define UMSEL	6
#define UPM1	5
#define UPM0	4
#define USBS	3
#define UCSZ1	2
#define UCSZ0	1
#define UCPOL	0
/***********************UASRT REGISTERS************/

#define SREG   *(volatile unsigned char*)0x5f
#define UDR    *(volatile unsigned char*)0x2c
#define UCSRA  *(volatile unsigned char*)0x2b
#define UCSRB  *(volatile unsigned char*)0x2a
#define UCSRC  *(volatile unsigned char*)0x40
#define UBRRL  *(volatile unsigned char*)0x29
#define UBRRH  *(volatile unsigned char*)0x40

/*************************************************/

enum USART_SYNCH_MOOD
{
	USART_ASYNCH =0,
	USART_SYNCH = (1<<6),
};

enum USART_SPEED_MOOD
{
	USART_NORMAL_SPEED,
	USART_DOUBLE_SPEED,
};

enum USART_TRANMIT
{
	USART_TRANSMIT_DISABLE,
	USART_TRANSMIT_ENABLE,
};

enum USART_RECIEVE
{
	USART_RECIEVE_DISABLE,
	USART_RECIEVE_ENABLE,
};

enum USART_CHAR_SIZE
{
	USART_5_BIT_CHAR = (0b00<<1),
	USART_6_BIT_CHAR = (0b01<<1),
	USART_7_BIT_CHAR = (0b10<<1),
	USART_8_BIT_CHAR = (0b11<<1),
	USART_9_BIT_CHAR = (0b111<<1),
};

enum USART_PARITY_MOOD
{
	USART_NO_PARITY   = (0<<4),
	USART_EVEN_PARITY = (2<<4),
	USART_ODD_PARITY  = (3<<4),
};

enum USART_STOPBIT
{
	USART_1_STOPBIT = (0<<3),
	//USART_1_STOPBIT = (1<<3),
};

enum USART_RECIVER_INT
{
	USART_RECEIVER_ENABLE =  (1<<7),
	USART_RECEIVER_DISABLE = (0<<7),
};

enum USART_TRANSMITER_INT
{
	USART_TRANSMITER_ENABLE =  (1<<6),
	USART_TRANSMITER_DISABLE = (0<<6),
};



typedef struct
{
	enum USART_SYNCH_MOOD SYNCH_MOOD ;
	enum USART_SPEED_MOOD SPEED_MOOD;
	enum USART_TRANMIT TRANMIT;
	enum USART_RECIEVE RECIEVE;
	enum USART_CHAR_SIZE CHAR_SIZE;
	enum USART_PARITY_MOOD PARITY_MOOD;
	enum USART_STOPBIT STOPBIT;
	enum USART_RECIVER_INT RECIVER_INT;
	enum USART_TRANSMITER_INT TRANSMITER_INT;
}USART_Config;





/*******************APIS******************/
bool_t USART_Init(USART_Config *config_uart);
bool_t USART_Transmit(uint16 data);
uint8 USART_Receive(uint8* Ptr_To_Val);
bool_t USART_Rec_Int_Enable(void);
bool_t USART_Rec_Int_Disable(void);
bool_t USART_Trans_Int_Enable(void);
bool_t USART_Trans_Int_Disable(void);
bool_t USART_Rec_Enable(void);
bool_t USART_Rec_Disable(void);
bool_t USART_Trans_Enable(void);
bool_t USART_Trans_Disable(void);
bool_t USART_Callback_Res_Int(void(*Ptr_to_Func)(void));
bool_t USART_Callback_Trans_Int(void(*Ptr_to_Func)(void));
/******************************************************/










#endif /* UART_H_ */
