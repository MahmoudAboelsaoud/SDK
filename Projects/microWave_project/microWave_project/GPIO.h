/*
 * GPIO.h
 *
 *  Created on: Oct 9, 2018
 *      Author: Aboelsaoud ^_^
 */

#ifndef GPIO_H_
#define GPIO_H_

#include"DataTypes.h"
#include"AVR_registers.h"



/*Directions*/
#define OUTPUT 1
#define INPUT 0


typedef enum
{  
	PORTA,
	PORTB,
	PORTC,
	PORTD,
}enum_port_t;


bool_t GPIO_PortInit(enum_port_t port, uint_8 pins, uint_8 init_value);
bool_t GPIO_PortDirection(enum_port_t port, uint_8 pins, uint_8 prot_dir);
bool_t GPIO_Pin_Set(enum_port_t port, uint_8 pins);
bool_t GPIO_Pin_Clear(enum_port_t port, uint_8 pins);
bool_t GPIO_Pin_Togal(enum_port_t port, uint_8 pins);

#endif /* GPIO_H_ */
