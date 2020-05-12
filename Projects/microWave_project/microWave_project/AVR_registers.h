/*
 * AVR_registers.h
 *
 *  Created on: Apr 10, 2020
 *      Author: M.Aboelsaoud
 */

#ifndef AVR_REGISTERS_H_
#define AVR_REGISTERS_H_

/*PINS*/
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7


/*PortA registers*/
#define PORTA1 *(volatile unsigned char*)0x3B
#define DDRA *(volatile unsigned char*)0x3A
#define PINA *(volatile unsigned char*)0x39

/*PortB registers*/
#define PORTB1 *(volatile unsigned char*)0x38
#define DDRB *(volatile unsigned char*)0x37
#define PINB *(volatile unsigned char*)0x36

/*PortC registers*/
#define PORTC1 *(volatile unsigned char*)0x35
#define DDRC *(volatile unsigned char*)0x34
#define PINC *(volatile unsigned char*)0x33

/*PortD registers*/
#define PORTD1 *(volatile unsigned char*)0x32
#define DDRD *(volatile unsigned char*)0x31
#define PIND *(volatile unsigned char*)0x30




#define GICR    *(volatile unsigned char*)0x5b
#define GIFR    *(volatile unsigned char*)0x5a
#define MCUCR   *(volatile unsigned char*)0x55
#define MCUCSR  *(volatile unsigned char*)0x54
#define SREG    *(volatile unsigned char*)0x5f

#define  DIR_PORTD   (*(volatile unsigned char*)0x31)
#define  INPUT_PORTD (*(volatile unsigned char*)0x30)
#define  OUTPUT_PORTD (*(volatile unsigned char*)0x32)

#define  DIR_PORTB   (*(volatile unsigned char*)0x37)
#define  INPUT_PORTB (*(volatile unsigned char*)0x36)
#define  OUTPUT_PORTB (*(volatile unsigned char*)0x38)


#define  DIR_PORTA   (*(volatile unsigned char*)0x3a)
#define  INPUT_PORTA (*(volatile unsigned char*)0x39)
#define  OUTPUT_PORTA (*(volatile unsigned char*)0x3b)






#endif /* AVR_REGISTERS_H_ */
