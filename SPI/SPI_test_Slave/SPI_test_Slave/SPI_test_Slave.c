/*
 * SPI_Driver.c
 *
 * Created: 6/22/2021 9:03:14 PM
 *  Author: M.Aboelsaoud
 */ 

#include "MSPI_interface.h"
#include <avr/io.h>


str_SpiConfigguration obg1=
{
	.SpiClockPhase = WRITE_THEN_READ,
	.SpiClockPolarity = CLOCK_IS_ZERO_IN_IDEL,
	.SpiDataOrder = SPI_MSB_FIRST,
	.SpiDoubleSpeed = SPI_DOUBLE_SPEED_MODE_OFF,
	.SpiEnable = SPI_ENABLE_ON,
	.SpiInterruptEnable = SPI_INI_ON,
	.SpiMode = SPI_SLAVE,
	.SpiPrescaler = SPI_FOSC4,
};

int main(void)
{
	DDRA=0xff;
	MSPI_boolInit(&obg1);
	//SPI_initSlave();
    while(1)
    {
       
    }
}