/***********************************************/
/* Auther     : Mahmoud Aboelsaoud             */
/* Date       : 21 Jun 2021                    */
/* Version    : V01                            */
/*Description : Interface file                 */
/***********************************************/
#ifndef MSPI_INTERFACE_H
#define MSPI_INTERFACE_H


#include "MSPI_private.h"
#include "STD_TYPES.h"



typedef struct
{
	enum_SpiMode                SpiMode            ;
	enum_SpiPrescaler           SpiPrescaler       ;
	enum_SpiEnable              SpiEnable          ;
	enum_SpiDoubleSpeed         SpiDoubleSpeed     ;
	enum_SpiClockPolarity       SpiClockPolarity   ;/* the clock stutes in the idel low/high */
	enum_SpiClockPhase          SpiClockPhase      ;/* what to do first at the leadind edge*/
	enum_SpiInterruptEnable     SpiInterruptEnable ;
	enum_SpiDataOrder           SpiDataOrder       ;

}str_SpiConfigguration;


void SPI_initSlave(void);
u8 SPI_recieveByte(void);
void SPI_sendByte(const u8 data);

bool_t MSPI_boolInit(str_SpiConfigguration *str_ptrSpiCOnfig);

bool_t MSPI_boolSendReceiveSynch (u8 copy_u8DateToSend, u8 * copy_u8DataToReceive);

bool_t MSPI_boolSendReceiveAsynch(u8 copy_u8DateToSend, void(*spi_callback)(u8));








#endif 
