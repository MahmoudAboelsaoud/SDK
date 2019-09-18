/*
 * Keypad.h
 *
 *  Created on: Feb 13, 2019
 *      Author: M.Aboelsaoud
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_



#include"common_std_types.h"
#include"macros_commen.h"
#include"micro_config.h"


#define N_COL 4
#define N_ROW 4
#define KEYPAT_DDRX_PORT  *(volatile unsigned char*)0x34
#define KEYPAT_PINX_PORT  *(volatile unsigned char*)0x33
#define KEYPAT_PORTX_PORT *(volatile unsigned char*)0x35

/* the user use it to allow the the controller receiver any press */
ecore_u8 KeyPad_getPressedKey(void);
/* this function calc the button number and pass then to the KeyPad_getPressedKey*/
ecore_u8 KeyPad_4x4_adjustKeyNumber(ecore_u8 button_number);



#endif /* KEYPAD_H_ */
