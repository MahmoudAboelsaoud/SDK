/***********************************************/
/* Auther     : Mahmoud Aboelsaoud             */
/* Date       : 5 Jul 2021                    */
/* Version    : V01                            */
/*Description : Private file                   */
/***********************************************/
#ifndef MUART_PRIVATE_H
#define MUART_PRIVATE_H


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



#endif 
