/*
 * common_std_types.h
 *
 *  Created on: Feb 12, 2019
 *      Author: M.Aboelsaoud
 */

#ifndef COMMON_H_
#define COMMON_H_

typedef enum{
	E_FALSE =0,
	E_TRUE,
}tenum_bool;

#define NULL ((void *)0)
typedef tenum_bool bool_t;
typedef signed char ecore_s8;
typedef unsigned char ecore_u8;
typedef unsigned short int ecore_u16;
typedef unsigned long int ecore_u32;

#endif /* COMMON_H_ */
