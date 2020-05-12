/*
 * MiceoWave.h
 *
 *  Created on: Apr 9, 2020
 *      Author: M.Aboelsaoud
 */

#ifndef MICEOWAVE_H_
#define MICEOWAVE_H_

#include"DataTypes.h"

#include"Keypad.h"
#include"lcd_driver.h"
#include"GPIO.h"
#include"external_interrupt.h"
#include"TMU.h"


bool_t MW_Init_All(void);
bool_t MW_Start(void);
bool_t MW_Stop(void);
bool_t MW__ON_Spot_Stop(void);


#endif /* MICEOWAVE_H_ */
