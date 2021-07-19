/***********************************************/
/* Auther     : Mahmoud Aboelsaoud             */
/* Date       : 30 Jun 2021                    */
/* Version    : V02                            */
/*Description : private file                   */
/***********************************************/
#ifndef MGPIO_PRIVATE_H
#define MGPIO_PRIVATE_H




/*PortA registers*/
#define OUT_PORTA *(volatile unsigned char*)0x3B 
#define DIR_DDRA  *(volatile unsigned char*)0x3A
#define IN_PINA1  *(volatile unsigned char*)0x39

/*PortB registers*/
#define OUT_PORTB *(volatile unsigned char*)0x38
#define DIR_DDRB  *(volatile unsigned char*)0x37
#define IN_PINB  *(volatile unsigned char*)0x36

/*PortC registers*/
#define OUT_PORTC *(volatile unsigned char*)0x35
#define DIR_DDRC  *(volatile unsigned char*)0x34
#define IN_PINC  *(volatile unsigned char*)0x33

/*PortD registers*/
#define OUT_PORTD *(volatile unsigned char*)0x32
#define DIR_DDRD  *(volatile unsigned char*)0x31
#define IN_PIND  *(volatile unsigned char*)0x30


/*PINS*/
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

/*Directions*/
#define OUTPUT 1
#define INPUT  0


/*User input*/
#define PORTA   2
#define PORTB   3
#define PORTC   4
#define PORTD   5






#endif