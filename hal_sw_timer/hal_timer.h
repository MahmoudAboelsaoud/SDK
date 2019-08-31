/*
 * hal_timer.h
 *
 *  Created on: Jul 20, 2018
 *      Author: hossam.adel
 */

#ifndef HAL_TIMER_H_
#define HAL_TIMER_H_

#include "common.h"
#include "hal_timer_config.h"

#define TCCR1A   (*(volatile unsigned char*)0x4F)
#define TCCR1B   (*(volatile unsigned char*)0x4E)
#define TCNT1H   (*(volatile unsigned char*)0x4D)
#define TCNT1L   (*(volatile unsigned char*)0x4C)


#define TCCR0   (*(volatile unsigned char*)0x53)
#define TCNTO   (*(volatile unsigned char*)0x52)
#define TIMSK   (*(volatile unsigned char*)0x59)
#define TIFR    (*(volatile unsigned char*)0x58)
#define SREG    (*(volatile unsigned char*)0x5f)

typedef enum {
	TIMER_0 =0x53,
	TIMER_1=0x4f,
	/* TIMER_1A=0X4F
	 * TIMER_1B=0X4E
	 */
   TIMER_2 =0x45,
}genum_inst_timer_t;

typedef enum {
	MIN_ENUM_NUMBER=0,
	WITHOUT_PRESACLER=0x01,
	PRESCALER_8=0x02,
	PRESCALER_64=0x03,
#ifdef TIMER2
	PRESCALER_128=0x05,
#endif
	PRESCALER_256=0x04,
	PRESCALER_1024=0x08,
	EXTERNAL_CLOCK_ON_T1=0x06,
	EXTERNAL_CLOCK_ON_T2=0x07,
	MIN_ENUM_NUMBER,
}genum_freq_timer_t;


typedef enum {
	CTC_MODE,
	NORMAL_MODE,
	PWM_PHASE_CORRECT,
	FAST_PWM,
}genum_fun_timer_t;


typedef struct {
	genum_inst_timer_t ins_timer;
	genum_freq_timer_t freq;
	genum_fun_timer_t timer_fun;
	/*INT handler*/
}gcfg_hal_timer_t;

#ifdef RESOLUTION_IS_USED
typedef enum{
	ENUM_MIN_INDEX=0,
	ONE_MILLIE_SEC,
	ONE_MICRO_SEC,
	ENUM_MIX_INDEX,
}genum_res_t;
#endif


ecore_s8 hal_init_timer(gcfg_hal_timer_t * obj, ecore_u8* cb_fun);

#ifdef RESOLUTION_IS_USED
ecore_s8 hal_init_timer_with_resolution(gcfg_hal_timer_t * obg, genum_res_t obj);
#endif

ecore_s8 hal_start_timer(gcfg_hal_timer_t * obj);

ecore_s8 hal_read_timer(gcfg_hal_timer_t * obj, ecore_u16 *timer_contain);

ecore_s8 hal_is_timer_finish(gcfg_hal_timer_t * obj , bool_t * res);

ecore_s8 hal_update_timer(gcfg_hal_timer_t * obj , ecore_u8 value);

ecore_s8 hal_update_cmp_timer(gcfg_hal_timer_t * obj , ecore_u8 value);

ecore_s8 hal_deinit_timer(gcfg_hal_timer_t * obj);


#endif /* HAL_TIMER_H_ */
