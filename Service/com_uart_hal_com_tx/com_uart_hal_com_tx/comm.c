/*
 * comm.c
 *
 *  Created on: Aug 3, 2018
 *      Author: Aboelsaoud ^_^
 */
#include"hal_uart.h"
#include "comm.h"


static ecore_u16 tx_counter =0;

gstr_uart_t obj=
{
	.speed=BAUD_RATE_9600,
};

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
	
}



bool_t comm_init(void)
{
	bool_t ret_val=E_TRUE;

	hal_init_uart(&obj,comm_cb_tx);
		
   return ret_val;
}




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


bool_t comm_dispatch ()
{
	bool_t ret_val=E_TRUE;
if(gstr_comm.lock_flag == 1)
{
		switch (Comm_state_g)
		{

	
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
		}
	return ret_val;
}
