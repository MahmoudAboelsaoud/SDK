/**********************************************/
/* Auther : Mahmoud Aboelsaoud                */
/* Version: v2                                */
/* Data   : 31 may 2021                       */
/* Description   : Timers code                */
/**********************************************/

#ifndef TIMER_PRIVATE_H
#define TIMER_PRIVATE_H



#define E_OK 1
#define E_NOK 0



#define BASE_HAL_TIMER_ERROR -50


#define  INVALID_ARG    (BASE_HAL_TIMER_ERROR -1)
#define  INVALID_TIMER  (BASE_HAL_TIMER_ERROR -2)
#define  MODE_ERROR     (BASE_HAL_TIMER_ERROR -3)




#define   TIMSK  *(volatile unsigned char*)0x59 /*Timers Interrupt Enables */
#define   TIFR   *(volatile unsigned char*)0x58 /*Timers Flags*/

#define   TCNT0  *(volatile unsigned char*)0x52
#define   TCCR0  *(volatile unsigned char*)0x53
#define   OCR0   *(volatile unsigned char*)0x5C


#define   TCNT2  *(volatile unsigned char*)0x44
#define   TCCR2  *(volatile unsigned char*)0x45
#define   OCR2   *(volatile unsigned char*)0x43






















#endif