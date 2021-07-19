/*
 * UART_driver.c
 *
 * Created: 7/12/2021 4:29:03 AM
 *  Author: M.Aboelsaoud
 */ 
#include <avr/io.h>
#include <util/delay.h>

#include "MUART_interface.h"
gstr_uart_t obj=
{
	.usart_mode					=ASYENCHRONOUS_USART,
	.tx_enable					=UART_TX_ON,
	.rx_enable					=UART_TX_ON,
	.UDRIE_interrupt_enable		=UART_UDRIE__INT_ON,
	.tx_interrupt_enable		=UART_TX__INT_ON,
	.rx_interrupt_enable		=UART_RX__INT_ON,
	.baud_rate					=BAUD_RATE_9600,
	.data_size					=USART_8_BITS,
	.clock_polarity				=USART_RISING_EDEG,
	.parity						=USART_PARITY_OFF,
	.stop_bit_num				=USART_ONE_STOP_BIT,
};

void fun()
{
	DDRA=DDRB=0xff;
	PORTA =PORTB =0xff;
}
u8 pattern[10]= {0b0111111,0b0110000, 0b1011011,0b1001111,0b1100110,0b1101101,0b1111101,0b0000111,0b1111111,0b1101111};

int main(void)
{
	u8 str[] ="Mahmoud Aboelsaoud "; 	
	u8 x;
	
	MUART_voidTxCallbackFunction(fun);
	MUART_boolInit(&obj);
	
	/*for(u8 i=0;i<10;i++)
	{
	  MUART_voidTransmitChar(pattern[i]);
	  _delay_ms(1000);
	}*/
	MUART_voidTransmitChar(10);
	//MUART_voidTransmitString(str);
	
    while(1)
    {
        
    }
}