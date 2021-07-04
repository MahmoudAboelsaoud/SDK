/**********************************************/
/* Auther : Mahmoud Aboelsaoud                */
/* Version: v2                                */
/* Data   : 28 may 2021                       */
/* Description   : external interupt code     */
/**********************************************/

#ifndef EXTI_PRIVATE_H
#define   EXTI_PRIVATE_H


#define GICR    *(volatile unsigned char*)0x5b
#define GIFR    *(volatile unsigned char*)0x5a
#define MCUCR   *(volatile unsigned char*)0x55
#define MCUCSR  *(volatile unsigned char*)0x54
#define SREG    *(volatile unsigned char*)0x5f









#endif