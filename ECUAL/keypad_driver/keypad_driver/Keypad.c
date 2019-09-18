/*
 * Keypad.c
 *
 *  Created on: Feb 13, 2019
 *      Author: M.Aboelsaoud
 */

#include"Keypad.h"

ecore_u8 KeyPad_getPressedKey(void)
{

	//bool_t ret_val =E_TRUE;

	ecore_u8 col,row;
	while(1)
	{

		for(col=0; col<N_COL; col++)
		{
			KEYPAT_DDRX_PORT |=(0b00010000 << col);

			KEYPAT_PORTX_PORT &=(~(0b00010000 << col));

			for(row=0; N_ROW>row; row++)
			{
				if(IS_BIT_SET(KEYPAT_PINX_PORT, row))
				{
					return KeyPad_4x4_adjustKeyNumber((row*N_COL)+col+1);

				}

			}

		}

	}

	//return ret_val;
}


ecore_u8 KeyPad_4x4_adjustKeyNumber(ecore_u8 button_number)
{
	//bool_t ret_val =E_TRUE;
	switch(button_number)
		{
			case 1: return 7;
					break;
			case 2: return 8;
					break;
			case 3: return 9;
					break;
			case 4: return '%'; // ASCII Code of %
					break;
			case 5: return 4;
					break;
			case 6: return 5;
					break;
			case 7: return 6;
					break;
			case 8: return '*'; /* ASCII Code of '*' */
					break;
			case 9: return 1;
					break;
			case 10: return 2;
					break;
			case 11: return 3;
					break;
			case 12: return '-'; /* ASCII Code of '-' */
					break;
			case 13: return 13;  /* ASCII of Enter */
					break;
			case 14: return 0;
					break;
			case 15: return '='; /* ASCII Code of '=' */
					break;
			case 16: return '+'; /* ASCII Code of '+' */
					break;
			default: return button_number;
		}

	//return ret_val;
}
