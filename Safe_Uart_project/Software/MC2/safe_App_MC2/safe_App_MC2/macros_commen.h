/*
 * macros_commen.h
 *
 *  Created on: Feb 12, 2019
 *      Author: M.Aboelsaoud
 */

#ifndef MACROS_COMMEN_H_
#define MACROS_COMMEN_H_

/*Set bit in any register*/
#define SET_BIT(REG, BIT) (REG |=(1<<BIT))

/*Clear bit in any register*/
#define CLEAR_BIT(REG, BIT) (REG &= ~(1<<BIT))

/*Toggle bit in any register*/
#define TOGGLE_BIT(REG, BIT) (REG ^=(1<<BIT))

/*Check if any bit in register is set return true if bit is set*/
#define IS_BIT_SET(REG, BIT)  (REG & (1<<BIT))

/*Check if any bit in register is cleared return true if bit is cleared*/
#define IS_BIT_CLEAR(REG, BIT)  (!(REG & (1<<BIT)))

#endif /* MACROS_COMMEN_H_ */
