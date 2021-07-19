/***********************************************/
/* Auther     : Mahmoud Aboelsaoud             */
/* Date       : 21 Jun 2021                    */
/* Version    : V01                            */
/*Description : Configuration file             */
/***********************************************/
#ifndef MSPI_CONFIG_H
#define MSPI_CONFIG_H


/* please Config the SLAVE_SELECT_PIN in piar format */
#define  SLAVE_SELECT_PIN    DDRA,0

#define  MISO     DDRB,6
#define  MOSI     DDRB,5
#define  SS       DDRB,4
#define  CLK      DDRB,7

#include <avr/interrupt.h>
#define F_CPU 1000000UL

#endif 
