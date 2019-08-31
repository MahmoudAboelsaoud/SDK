/*
 * SPI.c
 *
 *  Created on: Jul 6, 2019
 *      Author: M.Aboelsaoud
 */

#include "SPI.h"
#include "avr/interrupt.h"

static void (*SPI_ISR)(void);

ISR(SPI_STC_vect)
{
	SPI_ISR();
}

static void interupt_config()
{
	SETBIT(SREG,7);
}

bool_t hal_spi_init( s_spi_configuration *spi_config)
{
	bool_t ret_val=E_TRUE;
	if(spi_config !=NULL)
	{
		/* Enable SPI*/
		if(spi_config->ini_enable==SPI_INI_ON)
			SETBIT(SPCR, SPIE);
		else if (spi_config->ini_enable==SPI_INI_OFF)
			CLRBIT(SPCR, SPIE);
		/* Data Order*/
		if(spi_config->data_order==SPI_LSB_FIRST)
			SETBIT(SPCR, DORD);
		else if (spi_config->data_order==SPI_MSB_FIRST)
			CLRBIT(SPCR, DORD);

		/* Master/Slave select*/
		if(spi_config->slave_mode==SPI_SLAVE)
			CLRBIT(SPCR, MSTR);
		else if (spi_config->slave_mode==SPI_MASTER)
		{
			SETBIT(SPCR, MSTR);
			/*spi prescaler in the master mode*/
			SPCR = SPCR | (spi_config->prescaler);

			/* double spi speed if master*/
			if(spi_config->bouble_speed==SPI_DOUBLE_SPEED_MODE_ON)
				SETBIT(SPCR, SPI2X);
			else if (spi_config->bouble_speed==SPI_DOUBLE_SPEED_MODE_OFF)
				CLRBIT(SPCR, SPI2X);

		}

		/* clock polarity*/
		if(spi_config->operation_level==SPI_IDLE_LOW)
			SETBIT(SPCR, CPOL);
		else if (spi_config->operation_level==SPI_IDLE_HIGH)
			CLRBIT(SPCR, CPOL);
		/* clock phase*/
		if(spi_config->sampling_edge==SPI_RISING)
			SETBIT(SPCR, CPOL);
		else if (spi_config->sampling_edge==SPI_FALLING)
			CLRBIT(SPCR, CPOL);

		/* spi enable*/
		if(spi_config->enable==SPI_ENABLE_ON)
			SETBIT(SPCR, SPE);
		else if (spi_config->enable==SPI_ENABLE_OFF)
			CLRBIT(SPCR, SPE);

		
		interupt_config();

	}
	else
	{
		ret_val=E_FALSE;
	}
 
   
return ret_val;
}



unit_8 hal_spi_send_and_receive(unit_8 data)
{

	SPDR=data;
	while(!(SPSR&(1<<SPIF)));
	return SPDR;

}


bool_t hal_spi_read(unit_8 *data)
{
	bool_t ret_val =E_TRUE;
	
	*data=SPDR;
	while(!(SPSR&(1<<SPIF)));
	
	return ret_val;
}

bool_t hal_spi_write(unit_8 *data)
{
	
	bool_t ret_val =E_TRUE;
	
	SPDR=*data;
	while(!(SPSR&(1<<SPIF)));
	
	
	

	return ret_val;
}










unit_8 spi_checks_for_collision(void)
{
	unit_8 local_coll_status = GETBIT(SPSR,WCOL);
	return local_coll_status;
}



void spi_callback_fun_assign(void(*PtrToSPI_Isr)(void))
{
	SPI_ISR = PtrToSPI_Isr;
}
