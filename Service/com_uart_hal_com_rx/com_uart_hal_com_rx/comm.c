/*
 * comm.c
 *
 *  Created on: Aug 3, 2018
 *      Author: Aboelsaoud ^_^
 */
#include"hal_uart.h"
#include "comm.h"
#include "lcd_driver.h"


static ecore_u8 rx_flag_new_data =0;

static ecore_u8 rx_buffer[MAX_SIZE_DATA]={NULL};

static ecore_u16 rx_buffer_conuter=0;

static ecore_u8 *ptr_rx=NULL;


gstr_uart_t obj=
{
	.speed=BAUD_RATE_9600,
};



typedef enum{
	IDLE =0,
	RECIEVING_HEADER,
	RECIEVING_DATA,
	RECIEVING_COMPLETE,
}Comm_state;



Comm_state Comm_state_g = IDLE ;


/*call back function at rx byte complete*/
void comm_cb_rx()
{
	rx_flag_new_data =1;
	/*store data byte*/
	hal_recive_uart(&rx_buffer[rx_buffer_conuter++]);
	
		/*PORTC=rx_buffer[0];
	Lcd_Display_Character(rx_buffer[0]);*/
}



static void comm_buffer_free(void)
{
	hal_uart_deinit();
	rx_buffer_conuter=0;
	for(ecore_u16 i=0; i<MAX_SIZE_DATA; i++)
	rx_buffer[i]=NULL;

}


bool_t comm_init(void)
{
	bool_t ret_val=E_TRUE;
	
	hal_init_uart(&obj,comm_cb_rx);
	
	return ret_val;
}



bool_t comm_recieve()
{
	bool_t ret_val=E_TRUE;
		Comm_state_g = IDLE;
		
	return ret_val;
}



bool_t comm_dispatch ()
{
	bool_t ret_val=E_TRUE;
if(rx_flag_new_data ==1)
{
	switch (Comm_state_g)
	{
		
     	case IDLE:
				{
					if(rx_buffer_conuter < MAX_SIZE_DATA)
						{
						Comm_state_g = RECIEVING_DATA;
						}
					rx_flag_new_data=0;
					break;
				}
				
		case RECIEVING_DATA:
				{

						if( rx_buffer_conuter >= MAX_SIZE_DATA)
						{
							Comm_state_g = RECIEVING_COMPLETE;	
						}
						else
						{
							Comm_state_g = RECIEVING_DATA;
						}


					rx_flag_new_data=0;
					break;
				 }
				
		case RECIEVING_COMPLETE:
				{	
					if(rx_buffer_conuter >= MAX_SIZE_DATA)
					{
						/*pointer on the rx buffer*/
						ptr_rx = rx_buffer;
						Comm_state_g = IDLE;
						
					}	

					rx_flag_new_data=0;
					break;
				 }


		}
}
	return ret_val;

}
