/*
 * Keypad.h
 *
 *  Created on: Feb 13, 2019
 *      Author: M.Aboelsaoud
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_



#include "STD_TYPES.h"
#include "MGPIO_private.h"
#include "macros_commen.h"
#include "micro_config.h"

#define N_col 3
#define N_row 4

/* Keypad Port Configurations*/ 
#define KEYPAD_PORT_OUT  OUT_PORTC
#define KEYPAD_PORT_IN   IN_PINC
#define KEYPAD_PORT_DIR  DIR_DDRC



/*
 * Function responsible for getting the pressed keypad key
 */
u8 KeyPad_getPressedKey(void);

#if (N_col == 3)
/*
 * Function responsible for mapping the switch number in the keypad to 
 * its corresponding functional number in the proteus for 4x3 keypad 
 */
u8 KeyPad_4x3_adjustKeyNumber(u8 button_number);
#elif (N_col == 4)
/*
 * Function responsible for mapping the switch number in the keypad to 
 * its corresponding functional number in the proteus for 4x4 keypad  
 */
u8 KeyPad_4x4_adjustKeyNumber(u8 button_number);
#endif

#endif /* KEYPAD_H_ */
