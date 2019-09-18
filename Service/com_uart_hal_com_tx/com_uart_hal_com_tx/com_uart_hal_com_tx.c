/*
 * UART_AVR_STACK_Test.c
 *
 * Created: 2/24/2019 9:33:58 PM
 *  Author: M.Aboelsaoud
 */ 

#include"comm.h"
#include"hal_uart.h"

void test()
{
	//DDRB=1;
	//PORTB=x;
}
int main(void) {
	
	DDRC=0xff;
	//ecore_u8 arr[]={"Mahmoud Aboelsaoud"};
	ecore_u8 arr='5';
	//hal_init_uart(&obj,comm_cb_tx);
	comm_init();
	comm_send(&arr,sizeof(arr));

	while(1)
	{
		comm_dispatch();
		PORTC=UDR;
	}

}
