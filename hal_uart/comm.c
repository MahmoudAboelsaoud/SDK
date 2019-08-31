/*
 * comm.c
 *
 *  Created on: Aug 3, 2018
 *      Author: Aboelsaoud ^_^
 */
#include"hal_uart.h"
#include "comm.h"


static ecore_u16 tx_counter =0;

static ecore_u8 rx_flag_new_data =0;

static ecore_u8 rx_buffer[MAX_SIZE_DATA]={NULL};

static ecore_u16 rx_buffer_conuter=0;

static ecore_u8 *ptr_rx;


typedef struct
{
	ecore_u8 * data_ptr;
	ecore_u16 size;
	ecore_u8 lock_flag;

}gstr_comm_t;


static gstr_comm_t gstr_comm =
{
		.data_ptr = NULL,
		.size = 0,
		.lock_flag= 0
};

typedef enum{
	IDLE =0,
	SEND_BYTE,
	SEND_FRAME,
	SEND_DONE,
	RECIEVING_HEADER,
	RECIEVING_DATA,
	RECIEVING_COMPLETE,
}Comm_state;

Comm_state Comm_state_g = IDLE;

/*call back function at tx byte complete*/
void comm_cb_tx()
{
	Comm_state_g=SEND_DONE;
}

/*call back function at rx byte complete*/
void comm_cb_rx()
{
	if(MAX_SIZE_DATA > rx_buffer_conuter)
	{
	rx_flag_new_data =1;
	/*store data byte*/
	hal_recieve_uart(rx_buffer[rx_buffer_conuter++]);
	rx_buffer_conuter++;
	}
	else
	{
		/* do nothing*/
	}

}

static void comm_buffer_free(void)
{
	hal_recieve_uart_deinit();
	rx_buffer_conuter=0;
	for(ecore_u16 i=0; i<MAX_SIZE_DATA; i++)
	rx_buffer[i]=NULL;

}
/*
bool_t comm_init(void)
{
	bool_t ret_val=E_TRUE;

		hal_init_uart(&obj, comm_cb_tx, comm_cb_rx);

	return ret_val;

}*/


bool_t comm_send (ecore_u8 * data_ptr, ecore_u16 size)
{
	bool_t ret_val=E_TRUE;

	if ((data_ptr != NULL) && (size > 0 && size <= MAX_SIZE_DATA) && (gstr_comm.lock_flag == 0))
	{
		/*Header construction ..command ..size.. */
		/*hal_sent_uart(&command);
		hal_sent_uart(&size);  */       /*  should send two bytes  */
		gstr_comm.data_ptr = data_ptr;
		gstr_comm.size = size;
		gstr_comm.lock_flag = 1;
		Comm_state_g = SEND_FRAME;

	}
	else
	{
		ret_val = E_FALSE;
	}

	return ret_val;

}

#ifdef RX

bool_t comm_recieve (ecore_u8 * data_ptr_rx)
{
	bool_t ret_val=E_TRUE;
	  data_ptr_rx = ptr_rx;

	return ret_val;
}

#endif


bool_t comm_dispatch ()
{
	bool_t ret_val=E_TRUE;
if(gstr_comm.lock_flag == 1)
{
		switch (Comm_state_g)
		{
#ifdef TX
	
		case SEND_FRAME :
					{
						Comm_state_g = SEND_BYTE;
						hal_sent_uart (gstr_comm.data_ptr);
						tx_counter++;
						break;
					}
					
		case SEND_DONE:
				{
					if(tx_counter < gstr_comm.size)
					{
						Comm_state_g = SEND_BYTE;
						/*gstr_comm.data_ptr++;*/
						hal_sent_uart (gstr_comm.data_ptr++);
						tx_counter++; /*modfiy*/
					}
					else
					{
						Comm_state_g = IDLE;
						gstr_comm.lock_flag = 0;
						tx_counter=0;

					}
					break;
					
				}
				
				}
#endif

#ifdef RX //(rx_flag_new_data==1)
		case IDLE:
				{
					if(rx_buffer_conuter < MAX_SIZE_HEADER)
						{
						Comm_state_g = RECIEVING_HEADER;
						}
					else if(rx_buffer_conuter > MAX_SIZE_HEADER)
						{
							if((rx_buffer[1]+rx_buffer[2])== MAX_SIZE_DATA)
							{
								Comm_state_g = RECIEVING_DATA;
							}
							else
							{
								comm_buffer_free();
							}
						}
					else if(rx_buffer_conuter == MAX_SIZE_DATA)
						{
						Comm_state_g = RECIEVING_COMPLETE;
						}
					rx_flag_new_data=0;
					break;
				}
		case RECIEVING_HEADER:
				{
					if(rx_buffer_conuter >= MAX_SIZE_HEADER)
					{
						/*check the rx buffer size can be carry all the coming data or not */
						if((rx_buffer[1]+rx_buffer[2])== MAX_SIZE_DATA)
						{
							Comm_state_g = RECIEVING_DATA;
						}
						else
						{
							comm_buffer_free();
						}

					}
					else
					{
						Comm_state_g = RECIEVING_HEADER;
					}

					rx_flag_new_data=0;
					break;
				}
		case RECIEVING_DATA:
				{

					if((rx_buffer[1]+rx_buffer[2])== MAX_SIZE_DATA)
					{
						/*check the rx buffer size can be carry all the coming data or not */
						if(rx_buffer_conuter == MAX_SIZE_DATA)
						{
							Comm_state_g = RECIEVING_COMPLETE;
						}
						else
						{
							Comm_state_g = RECIEVING_DATA;
						}

					}
					else
					{
						 comm_buffer_free();
					}

					rx_flag_new_data=0;
					break;
				}
		case RECIEVING_COMPLETE:
				{
					if((rx_buffer[1]+rx_buffer[2])== MAX_SIZE_DATA)
					{
						/*pointer on the rx buffer*/
						ptr_rx = rx_buffer;
						Comm_state_g = IDLE;
					}
					else
					{
						comm_buffer_free();
					}

					rx_flag_new_data=0;
					break;
				}


#endif


	}
	return ret_val;

}
