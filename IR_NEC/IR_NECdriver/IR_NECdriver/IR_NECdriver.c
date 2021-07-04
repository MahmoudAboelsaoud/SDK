/*
 * IR_NECdriver.c
 *
 * Created: 7/1/2021 2:38:08 AM
 *  Author: M.Aboelsaoud
 */ 

#include "MGPIO_private.h"
#include "MHAL_IRinterface.h"

int main()
{

	HAL_boolIRSensorInit(PORTD, PIN2);
	
	
	
    while(1)
    {
		
        //TODO:: Please write your application code 
    }
	return 0;
}