/*
 * safe_App.c
 *
 * Created: 7/17/2021 2:48:50 AM
 *  Author: M.Aboelsaoud
 */ 

#include "STD_TYPES.h"
#include "Safe_interface.h"

int main(void)
{
	Safe_Init();

	 while(1)
    {
		Safe_Start();
	  
    }
}