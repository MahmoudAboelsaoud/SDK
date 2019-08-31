/*
 * SPI_driver_1.c
 *
 * Created: 7/6/2019 4:24:03 PM
 *  Author: M.Aboelsaoud
 */ 
#include <util/delay.h>
#include <avr/io.h>
#include "SPI.h"

#define F_CPU 1000000UL
#define MISO  6
#define MOSI  5
#define SS    4
#define SCK   7



int main(void)
{
	DDRB |=(1<<MOSI)|(1<<SCK)|(1<<SS);
	DDRB &=~(1<<MISO);
	
	SPCR=(1<<SPE);

	unsigned char ch=0;
	DDRA=0xff;
	s_spi_configuration str_obj =
	{
		/*.bouble_speed = SPI_DOUBLE_SPEED_MODE_OFF,
		.data_order = SPI_MSB_FIRST,
		.enable = SPI_ENABLE_ON,
		.ini_enable = SPI_INI_ON,
		.operation_level = SPI_IDLE_LOW,
		.prescaler = SPI_FOSC16,
		.sampling_edge = SPI_FALLING,
		.slave_mode = SPI_MASTER,*/
	};
	
	  hal_spi_init(&str_obj);
	 for(ch=0; ch<=255; ch++)
	 {
		_delay_ms(1000);
		//hal_spi_write(&ch);
		 PORTA =hal_spi_send_and_receive(ch);

	 }
	
	
}