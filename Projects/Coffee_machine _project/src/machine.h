/*
 * machine.h
 *
 *  Created on: May 12, 2020
 *      Author: M.Aboelsaoud
 */

#ifndef MACHINE_H_
#define MACHINE_H_

#include"GPIO.h"
#include"timer0.h"
#include"Keypad.h"
#include"DataTypes.h"
#include"lcd_driver.h"


bool_t Init_all_drivers();

bool_t Start_machine_working();

bool_t Sotp_machine_working();


#endif /* MACHINE_H_ */
