/*
 * GPIO_AvrDriver.c
 *
 * Created: 6/30/2021 1:19:52 AM
 *  Author: M.Aboelsaoud
 */ 


//#include <avr/io.h>
#include "MGPIO_interface.h"
#include "MGPIO_private.h"
int main(void)
{
	
	
	
	 MGPIO_SetPortDirection(PORTA, PIN0, OUTPUT);
	 MGPIO_SetPortDirection(PORTB, PIN1, OUTPUT);
	 MGPIO_SetPortDirection(PORTC, PIN2, OUTPUT);
	 MGPIO_SetPortDirection(PORTD, PIN3, OUTPUT);
	 
	 MGPIO_SetPin(PORTA,PIN0);
	 MGPIO_SetPin(PORTB,PIN0);
	 MGPIO_SetPin(PORTC,PIN0);
	 MGPIO_SetPin(PORTD,PIN0);
	 MGPIO_SetPin(PORTA,PIN7);
	/* MGPIO_SetPortDirection(PORTA, PIN0, INPUT);
	 MGPIO_SetPortDirection(PORTB, PIN1, INPUT);
	 MGPIO_SetPortDirection(PORTC, PIN2, INPUT);
	 MGPIO_SetPortDirection(PORTD, PIN3, INPUT);*/
    while(1)
    {
        
		
		
		MGPIO_TogalPin(PORTA,PIN0);
		MGPIO_TogalPin(PORTA,PIN1);
		MGPIO_TogalPin(PORTA,PIN2);
		MGPIO_TogalPin(PORTA,PIN3);
		MGPIO_TogalPin(PORTA,PIN4);
		MGPIO_TogalPin(PORTA,PIN5);
		MGPIO_TogalPin(PORTA,PIN6);
		MGPIO_TogalPin(PORTA,PIN7);
		
    }
}