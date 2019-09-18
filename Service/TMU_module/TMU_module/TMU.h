/*
 * TMN.h
 *
 *  Created on: Jul 15, 2018
 *      Author: Aboelsaoud ^_^
 */

#ifndef TMN_H_
#define TMN_H_

#include"commen.h"

#define NO_AVAILABLE_TIMERS 3

#define TCCR0_t   (*(volatile unsigned char*)0x53)
#define TCNT0_t   (*(volatile unsigned char*)0x52)
#define TIMSK_t   (*(volatile unsigned char*)0x59)
#define TIFR_t    (*(volatile unsigned char*)0x58)
#define SREG_t    (*(volatile unsigned char*)0x5f)


typedef enum
{
	INVALID_MIN_INDEX=0x52,
	TIMER0 =  0x53,
	TIMER1 =  0x4f,
	TIMER2 =  0x45,
	INVALID_MAX_INDEX,

}base_timer;

typedef enum
{
	ONE_SHOT,
	PERIODIC,

}type_timer;

typedef struct
{
	ecore_u8 time;
	void(*cb)();
	type_timer type;
	ecore_su8 curent_time;

}str_obj;


bool_t tmu_init(base_timer timer , ecore_u8 res);
bool_t start_timer(void(*cb)(), type_timer type, ecore_u8 time, str_obj * obg_adrs);
bool_t stop_timer(str_obj * obg_adrs);
bool_t tum_dispatch();



#endif /* TMN_H_ */
