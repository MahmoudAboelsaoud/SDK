/***********************************************/
/* Auther     : Mahmoud Aboelsaoud             */
/* Date       : 21 Jun 2021                    */
/* Version    : V01                            */
/*Description : cdoe file                      */
/***********************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO.h"


#include "MSPI_interface.h"
#include "MSPI_private.h"
#include "MSPI_config.h"



/*callback function*/
static void (*ISP_Cb_fun)(u8);


ISR(SPI_STC_vect)
{
	
}



void SPI_initSlave(void)
{ 
	/******** Configure SPI Slave Pins *********
	 * SS(PB4)   --> Input
	 * MOSI(PB5) --> Input
	 * MISO(PB6) --> Output
	 * SCK(PB7) --> Input
	 ********************************************/
	DDRB = DDRB & (~(1<<PB4));  
	DDRB = DDRB & (~(1<<PB5));
	DDRB = DDRB | (1<<PB6);
	DDRB = DDRB & (~(1<<PB7));
	SPCR = (1<<SPE); // just enable SPI + choose SPI clock = Fosc/4
	
	//SPDR = 0;
}


bool_t MSPI_boolInit(str_SpiConfigguration *str_ptrSpiCOnfig)
{
	bool_t ret_val = E_TRUE;
	if(str_ptrSpiCOnfig != NULL)
	{
	/******** Configure SPI Slave Pins *********
	 * SS(PB4)   --> Input
	 * MOSI(PB5) --> Input
	 * MISO(PB6) --> Output
	 * SCK(PB7) --> Input
	 ********************************************/
		DDRB = DDRB & (~(1<<PB4));
		DDRB = DDRB & (~(1<<PB5));
		DDRB = DDRB | (1<<PB6);
		DDRB = DDRB & (~(1<<PB7));
		
		/*Ser the SPI Interrupt Enable */
		if((str_ptrSpiCOnfig-> SpiInterruptEnable) == SPI_INI_ON)  SET_BIT(SPCR, SPIE);
		else CLR_BIT(SPCR, SPIE);
		
		
		/*Ser the SPI Data Format MSB or LSB sent first */
		if((str_ptrSpiCOnfig-> SpiDataOrder) == SPI_LSB_FIRST)  SET_BIT(SPCR, DORD);
		else CLR_BIT(SPCR, DORD);
		
		/*Set the node mode**/
		if((str_ptrSpiCOnfig-> SpiMode) == SPI_MASTER)     SET_BIT(SPCR, MSTR);
		else CLR_BIT(SPCR, MSTR);
		
		
		/*Ser the SPI Clock Polarity */
		if((str_ptrSpiCOnfig-> SpiClockPolarity) == CLOCK_IS_ONE_IN_IDEL)  SET_BIT(SPCR, CPOL);
		else CLR_BIT(SPCR, CPOL);
		
		/*Ser the SPI Clock Phase */
		if((str_ptrSpiCOnfig-> SpiClockPhase) == WRITE_THEN_READ)  SET_BIT(SPCR, CPHA);
		else CLR_BIT(SPCR, CPHA);
		
		/*the prescaler*/
		SPCR |= (str_ptrSpiCOnfig->SpiPrescaler);
		
		/*Enable the SPI Duble Speed Mode*/
		if((str_ptrSpiCOnfig-> SpiDoubleSpeed) == SPI_DOUBLE_SPEED_MODE_ON)  SET_BIT(SPSR, SPI2X);
		else CLR_BIT(SPSR, SPI2X);
		
		
		/*Enable the SPI*/
		if((str_ptrSpiCOnfig-> SpiEnable) == SPI_ENABLE_ON)   SET_BIT(SPCR, SPE);
		else CLR_BIT(SPCR, SPE);
		
		
		SPCR = (1<<SPE) | (1<<MSTR);
		
		
		
		SET_BIT(SREG,7);
	}
	else
	{
		
	}
	return ret_val;
}


void SPI_sendByte(const u8 data)
{
	CLR_BIT(PORTA1,0);
	SPDR = data; //send data by SPI
	while(GET_BIT(SPSR,SPIF)==0); //wait until SPI interrupt flag=1 (data is sent correctly)
	SET_BIT(PORTA1,0);
}


u8 SPI_recieveByte(void)
{
	while(GET_BIT(SPSR,SPIF)==0); //wait until SPI interrupt flag=1(data is receive correctly)
	return SPDR; //return the received byte from SPI data register
}


bool_t MSPI_boolSendReceiveSynch (u8 copy_u8DateToSend, u8 * copy_u8DataToReceive)
{
	bool_t ret_val = E_TRUE;
	
	if(copy_u8DataToReceive != NULL)
	{
	/*slave select pin is low*/
	GPIO_Pin_Clear(SLAVE_SELECT_PIN);
	/*put the data on the MOIS pin*/
	 SPDR = copy_u8DateToSend;
	/*wait for the data sent*/
	while((GET_BIT(SPSR, SPIF))== 0);
	/*put the received data from the MISO in the copy_u8DataToReceive */
	*copy_u8DataToReceive = SPDR;
	/*slave select pin is high*/
	GPIO_Pin_Set(SLAVE_SELECT_PIN);
	}
	else
	{
		ret_val = E_FALSE;
	}
	return ret_val;
}


bool_t MSPI_boolSendReceiveAsynch(u8 copy_u8DateToSend, void(*spi_callback)(u8))
{
	bool_t ret_val = E_TRUE ;
	
	if(spi_callback != NULL)
	{
	}
	else
	{
		ret_val = E_FALSE;
	}
	
	return ret_val;
}

