/*
 * UART_driver.c
 *
 * Created: 7/12/2021 4:29:03 AM
 *  Author: M.Aboelsaoud
 */ 
#include <avr/io.h>

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
	DDRA   =0xff;
	PORTA = 0xff;
}
int main(void)
{
	u8 str[] ="Mahmoud Aboelsaoud "; 
	//DDRD = 0xff;
	DDRB = 0xff;
	
	MUART_boolInit(&obj);
	for(u8 i=0;i<10;i++)
	PORTB = MUART_u8Receive();
    while(1)
    {
        
    }
}