/***********************************************/
/* Auther     : Mahmoud Aboelsaoud             */
/* Date       : 17 Jun 2021                    */
/* Version    : V01                            */
/*Description : code file                      */
/***********************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MUART_interface.h"


#include "Keypad.h"
#include "MGPIO_interface.h"
#include "MGPIO_private.h"

#include "Safe_private.h"
#include "Safe_interface.h"
#include "Safe_config.h"

u8 PressedKey = 0;
u8 arr[]={5,6,7,8};


static void stop_transmit(void)
{
	MUART_voidDeinitTransmition(&obj);
}

void Safe_Init(void)
{
	MGPIO_SetPortDirection(PORTB,PIN5,INPUT);
	MUART_boolInit(&obj) ;
}


void Safe_Start(void)
{
	for(u8 i =0;i<4;i++)
	{
		PressedKey = KeyPad_getPressedKey();
		MUART_voidTransmitChar(PressedKey);
		_delay_ms(500);
		if(GET_BIT(IN_PINB,PIN5)==1)
		{
			i=0;
		}
	}
	//stop_transmit();
}
