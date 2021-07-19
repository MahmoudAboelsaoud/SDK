*
 * common.h
 *
 *  Created on: Oct 9, 2018
 *      Author: Aboelsaoud ^_^
 */

#ifndef COMMON_H_
#define COMMON_H_

typedef enum
{
	E_FALSE =0,
    E_TRUE,
}enum_bool_t;

typedef unsigned char    uint_8;
typedef unsigned short   uint_16;
typedef unsigned long    uint_32;


typedef signed char sint_8;
typedef signed short sint_16;
typedef signed long snit_32;

typedef float sfloat_32;

typedef enum_bool_t bool_t;

#define NULL (void*)0


#endif /* COMMON_H_ */
