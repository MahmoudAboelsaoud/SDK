/*
 * timer0.h
 *
 *  Created on: Apr 28, 2020
 *      Author: M.Aboelsaoud
 */

#ifndef TIMER0_H_
#define TIMER0_H_
#include"DataTypes.h"
#include <avr/interrupt.h>

/*************************Timer0 Registers*************************/
#define TCCR0 *(volatile uint_8 *)0x53
#define TCNT0 *(volatile uint_8 *)0x52
#define TIMSk *(volatile uint_8 *)0x59
#define OCR0  *(volatile uint_8 *)0x5c
/*************************TCCR0 BITS*******************************/
#define FOC0  7
#define WGM00 6
#define COM01 5
#define COM00 4
#define WGM01 3
#define CS02  2
#define CS01  1
#define CS00  0
/***************************Enable Timer0 INT*********************/
#define TOIE0 0
#define OCIE0 1


typedef enum
{
	CTC,
	NORMAL
}WAVE_FORM_GEN;

typedef enum
{
	TOIE0_ENABLE,
	TOIE0_DISABLE,
}TOVFIE0;

typedef enum
{
	OCIE0_ENABLE,
	OCIE0_DISABLE,
}OCMIE0;

typedef enum
{
	NO_CLK_SRC =0,
	NO_PRESCALING =1,
	PRESCALING_CLK8 =2,
	PRESCALING_CLK64 =3,
	PRESCALING_CLK256 =4,
	PRESCALING_CLK1024 =5,
	EXT_CLK_FALLING =6,
	EXT_CLK_RISING =7

}TMR_PRESCALAR;

typedef struct
{
	WAVE_FORM_GEN Timer0_Mode;
	TOVFIE0 Timer0_OVFI;
	OCMIE0 Timer0_OCIE;
	TMR_PRESCALAR Timer0_Prescalar;

}STIMER0_SETTINGS;

bool_t TMR0_INIT(STIMER0_SETTINGS * tmr0_configuration);
bool_t TMR0_ReadCounterValue(uint_8 *numberOfTicks);
bool_t TMR0_Set_Compare_Value(uint_8 val);
bool_t TMR0_Set_Counter_Value(uint_8 val);

bool_t TMR0_Set_TOV_Number(uint_8 val);
bool_t TMR0_Get_TOV_Number(uint_8 *val);

/** SW counter**/
bool_t TMR0_Get_Ticks_of_SWcounter(uint_32 *val);

/**  ISR **/
bool_t callback_TMR0_Overflow_Interrupt(void(*Ptr_to_OVI_function)(void));
bool_t callback_TMR0_Compare_Match_Interrupt(void(*Ptr_to_OCM_function)(void));


#endif /* TIMER0_H_ */
