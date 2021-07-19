/*
 * safe_App_MC2.c
 *
 * Created: 7/17/2021 4:04:58 AM
 *  Author: M.Aboelsaoud
 */ 

#include "Safe_interface.h"

int main(void)
{
	Safe_Init();
	
	
    while(1)
    {
		Safe_Start();	
    }
}