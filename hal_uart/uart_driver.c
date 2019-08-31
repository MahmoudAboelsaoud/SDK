/*
 * UART_AVR_STACK_Test.c
 *
 * Created: 2/24/2019 9:33:58 PM
 *  Author: M.Aboelsaoud
 */ 

#include"comm.h"
#include"hal_uart.h"
ecore_u8 x;
void test()
{
	//DDRB=1;
	//PORTB=x;
}
int main(void) {



	gstr_uart_t obj=
	{
		.speed=BAUD_RATE_9600,
	};

	
	ecore_u8 arr[]={"Mahmoud Aboelsaoud"};
	//ecore_u8 arr='H';
	hal_init_uart(&obj,comm_cb_tx);
	comm_send(arr,sizeof(arr));

	//hal_init_uart(&obj,test);
	//hal_sent_uart(&arr);
	//hal_recive_uart(&x);
	while(1)
	{
		comm_dispatch();
	}

}
