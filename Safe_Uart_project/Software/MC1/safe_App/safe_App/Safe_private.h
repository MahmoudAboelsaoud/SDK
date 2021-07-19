/***********************************************/
/* Auther     : Mahmoud Aboelsaoud             */
/* Date       : 17 Jun 2021                    */
/* Version    : V01                            */
/*Description : Private file                   */
/***********************************************/
#ifndef SAFE_PRIVATE_H
#define SAFE_PRIVATE_H




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
#endif