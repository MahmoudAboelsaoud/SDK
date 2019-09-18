/*
 * keypad_driver.c
 *
 * Created: 2/13/2019 2:26:40 PM
 *  Author: M.Aboelsaoud
 */ 


#include <avr/io.h>
#include "Keypad.h"
int main(void)
{
	ecore_u8 key;
	//DDRC=0xff;
	DDRB=0xff;
	PORTB=0;
     while(1)
     {
	     key = KeyPad_getPressedKey(); /* get the pressed button from keypad */
	     if((key >= 0) && (key <= 9))
	     {
		     PORTB = key;
	     }
     }
}