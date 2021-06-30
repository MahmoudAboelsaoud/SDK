/*
 * SPI_Driver.c
 *
 * Created: 6/22/2021 9:03:14 PM
 *  Author: M.Aboelsaoud
 */ 

#include "MSPI_interface.h"

#include <avr/io.h>
#include <util/delay.h>

str_SpiConfigguration obg1=
{
	.SpiClockPhase = WRITE_THEN_READ,
	.SpiClockPolarity = CLOCK_IS_ZERO_IN_IDEL,
	.SpiDataOrder = SPI_LSB_FIRST,
	.SpiDoubleSpeed = SPI_DOUBLE_SPEED_MODE_OFF,
	.SpiEnable = SPI_ENABLE_ON,
	.SpiInterruptEnable = SPI_INI_ON,
	.SpiMode = SPI_MASTER,
	.SpiPrescaler = SPI_FOSC4,
};
#define F_CPU 1000000UL
int main(void)
{
	u8 arr[]={0xaf,0xfa,0xaf,0xfa};
	u8 data_received;
   // SPI_initMaster();
    MSPI_boolInit(&obg1);
	//MSPI_boolSendReceiveSynch(0xff, &data_received);
	for (u8 i=0;i<3;i++)
	{
		
	    MSPI_boolSendReceiveSynch(arr[i], &data_received);
		
	    PORTD=0xff;
		_delay_ms(1000);
		MSPI_boolSendReceiveSynch(arr[i], &data_received);
		
		PORTD=0x00;
		_delay_ms(1000);
	}
	
	
    while(1)
    {
		MSPI_boolSendReceiveSynch(0x00, &data_received);
		
		PORTD=0xff;
		_delay_ms(1000);
	
		MSPI_boolSendReceiveSynch(0xff, &data_received);	
		PORTD=0x00;
		_delay_ms(1000);
    }
}