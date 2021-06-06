/*******************************************************/
/* Author   : MAhmoud Aboelsaoud                       */
/* Date     : 25 spt 2020                              */
/* Version  : v01                                      */
/*******************************************************/

#ifndef STD_TYPES_H
#define STD_TYPES_H

#define NULL (void*)0  
typedef char                su8  ;
typedef short int           su16 ;
typedef long int            su32 ;
typedef unsigned char       u8   ;
typedef unsigned short int  u16  ;
typedef unsigned long int   u32  ;

typedef enum
{
	E_FALSE = 0,
	E_TRUE
}enum_bool_t;

typedef enum_bool_t bool_t;


#endif
