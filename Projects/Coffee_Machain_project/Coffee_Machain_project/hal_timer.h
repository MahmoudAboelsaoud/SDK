/*
 * hal_timer.h
 *
 *  Created on: Jul 20, 2018
 *      Author: mahmoud.aboelsaoud
 */

#ifndef HAL_TIMER_H_
#define HAL_TIMER_H_

#include"DataTypes.h"

typedef enum {
	//a=0x53,
	TIMER_0=0x53,
	TIMER_1A=0x4f,
	TIMER_1B=0x4e,
	TIMER_2=0x45,
}genum_inst_timer_t;

typedef enum {
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

sint_8 hal_init_timer(gcfg_hal_timer_t * obj, uint_8* cb_fun);
sint_8 hal_start_timer(gcfg_hal_timer_t * obj);
sint_8 hal_read_timer(gcfg_hal_timer_t * obj, uint_8 *timer_contain);
sint_8 hal_is_timer_finish(gcfg_hal_timer_t * obj , bool_t * res);

sint_8 hal_update_timer(gcfg_hal_timer_t * obj , uint_8 value);

sint_8 hal_update_cmp_timer(gcfg_hal_timer_t * obj , uint_8 value);

sint_8 hal_deinit_timer(gcfg_hal_timer_t * obj);



#endif /* HAL_TIMER_H_ */
