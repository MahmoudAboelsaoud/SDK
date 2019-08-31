/*
 * hal_timer_config.h
 *
 *  Created on: Feb 18, 2019
 *      Author: M.Aboelsaoud
 */

#ifndef SRC_HAL_HAL_TIMER_CONFIG_H_
#define SRC_HAL_HAL_TIMER_CONFIG_H_

 #include "hal_timer.h"
 
#define RESOLUTION_IS_USED

#define TIMER2
#define TIMER1
#define TIMER0


/*call back fun from the application */
//ecore_u8 * hal_ptr_cb =count;

/*gcfg_hal_timer_t timer_confg =
	{
		.ins_timer = TIMER_0,
		.freq = WITHOUT_PRESACLER,
		.timer_fun = NORMAL_MODE,
	};*/

#ifdef RESOLUTION_IS_USED

gcfg_hal_timer_t timer_confg_one_micro =
	{
		.ins_timer =  TIMER_0,
		.freq = WITHOUT_PRESACLER,
		.timer_fun = NORMAL_MODE,
	};

gcfg_hal_timer_t timer_confg_one_mille =
	{
		.ins_timer =  TIMER_1,
		.freq = WITHOUT_PRESACLER,
		.timer_fun = NORMAL_MODE,
	};

#endif

#endif /* SRC_HAL_HAL_TIMER_CONFIG_H_ */
