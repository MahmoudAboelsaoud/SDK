/***********************************************/
/* Auther     : Mahmoud Aboelsaoud             */
/* Date       : 21 Jun 2021                    */
/* Version    : V01                            */
/*Description : Private file                   */
/***********************************************/
#ifndef MSPI_PRIVATE_H
#define MSPI_PRIVATE_H



#define  SPCR *(volatile unsigned char*)0x2d
#define  SPSR *(volatile unsigned char*)0x2e
#define  SPDR *(volatile unsigned char*)0x2f
#define  SREG *(volatile unsigned char*)0x5f


/***************SPCR*****************/
#define SPIE  7
#define SPE   6
#define DORD  5
#define MSTR  4
#define CPOL  3
#define CPHA  2
#define SPR1  1
#define SPR0  0
/****************SPSR***********/
#define SPIF  7
#define WCOL  5
#define SPI2X 0
/******************************/


typedef enum
{
	SPI_MASTER =1,
	SPI_SLAVE  =0
}enum_SpiMode;

typedef enum
{
	SPI_FOSC4   = 0b00,
	SPI_FOSC16  = 0b01,
	SPI_FOSC64  = 0b10,
	SPI_FOSC128 = 0b11,
}enum_SpiPrescaler;

typedef enum
{
	SPI_ENABLE_ON  =1,
	SPI_ENABLE_OFF =0
}enum_SpiEnable;

typedef enum
{
	SPI_DOUBLE_SPEED_MODE_OFF = 0,
	SPI_DOUBLE_SPEED_MODE_ON  = 1,
}enum_SpiDoubleSpeed;

typedef enum
{
	READ_THEN_WRITE =0,
	WRITE_THEN_READ =1,
}enum_SpiClockPhase;

typedef enum
{
	/*the shape of the clock in the idel case*/
	CLOCK_IS_ZERO_IN_IDEL  =0,
	CLOCK_IS_ONE_IN_IDEL   =1
}enum_SpiClockPolarity;


typedef enum
{
	SPI_INI_OFF = 0,
	SPI_INI_ON  = 1
}enum_SpiInterruptEnable;

typedef enum
{
	SPI_LSB_FIRST = 1,
	SPI_MSB_FIRST = 0
}enum_SpiDataOrder;




#endif 
