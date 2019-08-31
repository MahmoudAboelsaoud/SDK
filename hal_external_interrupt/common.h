/*
 * common.h
 *
 *  Created on: Jul 6, 2019
 *      Author: M.Aboelsaoud
 */

#ifndef COMMON_H_
#define COMMON_H_

#define NULL (void*)0

typedef enum
{
	E_FALSE=0,
	E_TRUE,
}enum_bool_t;

typedef enum_bool_t bool_t;

typedef signed char unit_s8;
typedef signed short int unit_s16;
typedef signed long int unit_s32;

typedef unsigned char unit_8;
typedef unsigned short int unit_16;
typedef unsigned long int unit_32;

typedef float unit_f32;
typedef double unit_f64;


#define GETBIT(REG, BITNO)      ((REG>>BITNO)&1)
#define CLRBIT(REG, BITNO)      (REG &=~(BITNO<<1))
#define SETBIT(REG, BITNO)      (REG |=(BITNO<<1))
#define TOGGELBIT(REG, BITNO)   (REG ^=(BITNO<<1))




#endif /* COMMON_H_ */
