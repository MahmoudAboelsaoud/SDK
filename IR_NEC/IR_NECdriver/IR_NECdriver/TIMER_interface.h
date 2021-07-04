/**********************************************/
/* Auther : Mahmoud Aboelsaoud                */
/* Version: v2                                */
/* Data   : 31 may 2021                       */
/* Description   : Timers code                */
/**********************************************/

#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

#include "STD_TYPES.h"

typedef enum 
{
	TIMER_0  =0x53,
	TIMER_1  =0x4f,
	TIMER_2  =0x45,
}genum_inst_timer_t;

typedef enum 
{
	NO_CLOCK = 0x0,
	WITHOUT_PRESACLER = 0x1,
	PRESCALER_8 ,
	PRESCALER_64,
#ifdef TIMER2
	PRESCALER_128,
#endif
	PRESCALER_256,
	PRESCALER_1024,
	EXTERNAL_CLOCK = 0x6,
}genum_freq_timer_t;

typedef enum 
{
	NORMAL_MODE = 1,
	CTC_MODE,
	PWM_PHASE_CORRECT,
	FAST_PWM,
}genum_fun_timer_t;


typedef struct
{
	genum_inst_timer_t  ins_timer;
	genum_freq_timer_t  freq;
	genum_fun_timer_t   timer_fun;
}gcfg_hal_timer_t;


/* hal_init_timer : function init any timer you need (TIMER0, TIMER1, TIMER2) tack object of the 
gcfg_hal_timer_t structure and return signed number for error indection */
su8 hal_init_timer(gcfg_hal_timer_t * obj);

/* hal_start_timer : function start the initialized timer you need (TIMER0, TIMER1, TIMER2) tack object of the 
gcfg_hal_timer_t structure and return signed number for error indection */
su8 hal_start_timer(gcfg_hal_timer_t * obj);

/* hal_read_timer : function read the timer value (TIMER0, TIMER1, TIMER2) tack object of the 
gcfg_hal_timer_t structure and address to return the timer contain value in it and return signed number for error indection */
su8 hal_read_timer(gcfg_hal_timer_t * obj, u8 *timer_contain);
u8 hal_ReadTimerCurrentValue(gcfg_hal_timer_t * obj);

/* hal_is_timer_finish : function check if the timer finish (TIMER0, TIMER1, TIMER2) tack object of the 
gcfg_hal_timer_t structure and pointer to cary if finish TRUE or FALSE if not finish and return signed number for error indection */
su8 hal_is_timer_finish(gcfg_hal_timer_t * obj , bool_t * res);

/* hal_update_timer : function update the timer init value that you need in the noromal mode (TIMER0, TIMER1, TIMER2) tack object of the 
gcfg_hal_timer_t structure and the value and return signed number for error indection */
su8 hal_update_init_timer_value(gcfg_hal_timer_t * obj , u8 value);

/* hal_update_cmp_timer : function update the timer init value that you need in the CTC mode (TIMER0, TIMER1, TIMER2) tack object of the 
gcfg_hal_timer_t structure and the value and return signed number for error indection */
su8 hal_update_cmp_timer(gcfg_hal_timer_t * obj , u8 value);


/* hal_deinit_timer : function deinit any timer you need (TIMER0, TIMER1, TIMER2) tack object of the 
gcfg_hal_timer_t structure and return signed number for error indection */
su8 hal_deinit_timer(gcfg_hal_timer_t * obj);

bool_t hal_Init_Timer0_Cb_OV(void(*cb_fun_t0_ov)(void));
bool_t hal_Init_Timer1_Cb_OV(void(*cb_fun_t1_ov)(void));
bool_t hal_Init_Timer2_Cb_OV(void(*cb_fun_t2_ov)(void));

bool_t hal_Init_Timer0_Cb_CM(void(*cb_fun_t0_cm)(void));
bool_t hal_Init_Timer1_Cb_CM(void(*cb_fun_t1_cm)(void));
bool_t hal_Init_Timer2_Cb_CM(void(*cb_fun_t2_cm)(void));













#endif