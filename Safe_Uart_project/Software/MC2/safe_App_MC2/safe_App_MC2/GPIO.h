/*
 * GPIO.h
 *
 *  Created on: Oct 9, 2018
 *      Author: Aboelsaoud ^_^
 */

#ifndef GPIO_H_
#define GPIO_H_
#include "STD_TYPES.h"

/*PortA registers*/
#define PORTA1 *(volatile unsigned char*)0x3B 
#define DDRA *(volatile unsigned char*)0x3A
#define PINA *(volatile unsigned char*)0x39

/*PortB registers*/
#define PORTB1 *(volatile unsigned char*)0x38
#define DDRB *(volatile unsigned char*)0x37
#define PINB *(volatile unsigned char*)0x36

/*PortC registers*/
#define PORTC1 *(volatile unsigned char*)0x35
#define DDRC *(volatile unsigned char*)0x34
#define PINC *(volatile unsigned char*)0x33

/*PortD registers*/
#define PORTD1 *(volatile unsigned char*)0x32
#define DDRD *(volatile unsigned char*)0x31
#define PIND *(volatile unsigned char*)0x30
/*PINS*/
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

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

/*
typedef enum
{
	DDRA,
	DDRB,
	DDRC,
	DDRD,
}enum_direction_t;
*/
/*
typedef enum
{
	//MIM_ENUM_NUM=-1,
	INPUT=0,
	OUTPUT=1,
	//MIX_ENUM_NUM
}enum_port_direction_t;
*/
/*
typedef struct
{
	enum_port_t port;
	enum_status_t status;
}str_pin_t;
*/

/*
bool_t port_init(str_pin_t* obg);
bool_t set_pin(str_pin_t* obg, uint_8 pin_num);
bool_t clear_pin(str_pin_t* obg, uint_8 pin_num);
bool_t togal_pin(str_pin_t* obg, uint_8 pin_num);

bool_t set_group_of_pins(str_pin_t* obg, uint_8*arr_ptr, uint_8 pins_count);
bool_t clear_group_of_pins(str_pin_t* obg, uint_8*arr_ptr, uint_8 pins_count);

bool_t pur_set(str_pin_t* obg);

*/

bool_t GPIO_PortInit(enum_port_t port, uint_8 pins, uint_8 init_value);
bool_t GPIO_PortDirection(enum_port_t port, uint_8 pins, uint_8 prot_dir);
bool_t GPIO_Pin_Set(uint_8 port, uint_8 pins);
bool_t GPIO_Pin_Clear(uint_8 port, uint_8 pins);
bool_t GPIO_Pin_Togal(uint_8 port, uint_8 pins);

#endif /* GPIO_H_ */
