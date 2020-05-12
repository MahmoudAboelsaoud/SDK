/*
 ============================================================================
 Name        : MicroWave_Project.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "MiceoWave.h"

int main(void)
{
	MW_Init_All();
	MW_Start();
	//SREG = (1<<7);
	while(1)
	{
	tum_dispatch();		 
	}

	return 0;
}
