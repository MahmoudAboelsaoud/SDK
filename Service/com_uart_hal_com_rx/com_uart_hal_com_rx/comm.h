/*
 * comm.h
 *
 *  Created on: Aug 3, 2018
 *      Author: Aboelsaoud ^_^
 */

#ifndef COMM_H_
#define COMM_H_


#include"commen.h"


#define MAX_SIZE_DATA 7
#define MAX_SIZE_HEADER 2


void comm_cb_tx();
void comm_cb_rx();
bool_t comm_init(void);
bool_t comm_send (ecore_u8 * data_ptr, ecore_u16 size);
bool_t comm_recieve ();
bool_t comm_dispatch ();



#endif /* COMM_H_ */
