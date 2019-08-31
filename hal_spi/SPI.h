/*
 * SPI.h
 *
 *  Created on: Jul 6, 2019
 *      Author: M.Aboelsaoud
 */


#ifndef SPI_H_
#define SPI_H_

#include"common.h"

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

typedef enum
{
	SPI_MASTER =1,
	SPI_SLAVE=0
}enum_spi_slave_mode;

typedef enum
{
	SPI_FOSC4 = 0b00,
	SPI_FOSC16 = 0b01,
	SPI_FOSC64 = 0b10,
	SPI_FOSC128 = 0b11,
}enum_spi_prescaler;

typedef enum
{
	SPI_ENABLE_ON =1,
	SPI_ENABLE_OFF=0
}enum_spi_enable;

typedef enum
{
	SPI_DOUBLE_SPEED_MODE_OFF,
	SPI_DOUBLE_SPEED_MODE_ON,
}enum_spi_bouble_speed;

typedef enum
{
	SPI_IDLE_LOW,
	SPI_IDLE_HIGH
}enum_spi_operation_level;

typedef enum
{
	SPI_RISING=1,
	SPI_FALLING=0
}enum_spi_sampling_edge;


typedef enum
{
	SPI_INI_OFF=0,
	SPI_INI_ON
}enum_spi_ini_enable;

typedef enum
{
	SPI_LSB_FIRST=1,
	SPI_MSB_FIRST=0
}enum_spi_data_order;


typedef struct
{
	enum_spi_slave_mode slave_mode;
	enum_spi_prescaler prescaler;
	enum_spi_enable enable;
	enum_spi_bouble_speed bouble_speed;
	enum_spi_operation_level operation_level;
	enum_spi_sampling_edge sampling_edge;
	enum_spi_ini_enable ini_enable;
	enum_spi_data_order data_order;

}s_spi_configuration;




bool_t hal_spi_init( s_spi_configuration *spi_config);
unit_8 hal_spi_send_and_receive(unit_8 data);
unit_8 hal_spi_checks_for_collision(void);

bool_t hal_spi_read(unit_8 *data);

bool_t hal_spi_write(unit_8 *data);

void spi_callback_fun_assign(void(*PtrToSPI_Isr)(void));






#endif /* SPI_H_ */
