/*
 * seven_seg.c
 *
 *  Created on: Jul 7, 2018
 *      Author: hossam.adel
 */
#include "commen.h"
#include "sevenseg.h"

typedef struct
{
	enum_port_base_t enum_base_port;                   
	enum_seven_seg_type_t enum_type;                     
}str_seven_seg_info_t;

static str_seven_seg_info_t ga_seven_handlers[MAX_NUMBER_OF_HANDLERS];
static  ecore_u8 count_deinit=0;                 

static const  ecore_u8 pattern[]= {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
static  ecore_u8 arr_deinit_num [] ={0};

 ecore_u8 handler_counter = 0;
 ecore_u8 element_deinit = 0;

bool_t seven_seg_init(enum_port_base_t port_base, enum_seven_seg_type_t seven_seg_type, ecore_u8 * handler )
{
	bool_t b_ret_val = E_TRUE;

	if((handler != NULL))
	{

		if(count_deinit !=0)
		{
			for(ecore_u8 i=0 ; i < count_deinit ; i++ ,count_deinit --)
			{
				*(volatile ecore_u8*)(port_base + 1) = 0xff;
				ga_seven_handlers[arr_deinit_num[i]].enum_base_port = port_base;
 				ga_seven_handlers[arr_deinit_num[i]].enum_type = seven_seg_type;
			}
		}

	   else if(handler_counter < MAX_NUMBER_OF_HANDLERS)
		{
			*(volatile ecore_u8*)(port_base + 1) = 0xff;
			ga_seven_handlers[handler_counter].enum_base_port = port_base;
			ga_seven_handlers[handler_counter].enum_type = seven_seg_type;
			*handler = handler_counter;
			handler_counter++;
		}
		else
		{
			b_ret_val = E_FALSE;
		}
	}
	else
	{
		b_ret_val = E_FALSE;
	}

	return b_ret_val;
}

bool_t seven_seg_display(ecore_u8 handler , ecore_u8 dis_no)
{
	bool_t b_ret_val = E_TRUE;
	if((handler_counter < MAX_NUMBER_OF_HANDLERS) && (dis_no < 10))
	{
		if(ga_seven_handlers[handler].enum_base_port != 0)
		{
			if(ga_seven_handlers[handler].enum_type == COMMON_ANOD)
			{
				*(volatile ecore_u8*)(ga_seven_handlers[handler].enum_base_port + 2) = pattern[dis_no];
			}
			else if(ga_seven_handlers[handler].enum_type == COMMON_CATHOD)
			{
				*(volatile ecore_u8*)(ga_seven_handlers[handler].enum_base_port + 2) = ~pattern[dis_no];
			}
			else
			{
				/*invalid parameter*/
				b_ret_val  = E_FALSE;
			}
		}
		else
		{
			/*module not init*/
			b_ret_val = E_FALSE;
		}
	}
	else
	{
		b_ret_val = E_FALSE;
	}
	return b_ret_val;
}


bool_t seven_seg_reset(ecore_u8 handler)
{
	bool_t ret_val = E_TRUE;

	if((handler_counter < MAX_NUMBER_OF_HANDLERS))
	{
		if(ga_seven_handlers[handler].enum_base_port != 0)
		{
			if(ga_seven_handlers[handler].enum_type==COMMON_ANOD)
			{
				*(volatile unsigned char*)(ga_seven_handlers[handler].enum_base_port+2)=pattern[0];

			}
			else if(ga_seven_handlers[handler].enum_type==COMMON_CATHOD)
			{
				*(volatile unsigned char*)(ga_seven_handlers[handler].enum_base_port+2)= ~ pattern[0];
			}
			else
			{
				ret_val = E_FALSE;
			}

		}
		else
		{
			ret_val = E_FALSE;
		}
	}
	else
	{
		ret_val = E_FALSE;
	}

    return ret_val;
}

bool_t seven_seg_deinit(ecore_u8 handler , ecore_u8 element_deinit)
{
	bool_t ret_val = E_TRUE;

	if((element_deinit < MAX_NUMBER_OF_HANDLERS) && (handler < MAX_NUMBER_OF_HANDLERS))
	{

		*(volatile unsigned char*)(ga_seven_handlers[element_deinit].enum_base_port)=0;
		*(volatile unsigned char*)(ga_seven_handlers[element_deinit].enum_type)=0;
		 arr_deinit_num[count_deinit]=element_deinit;
		 count_deinit++;

	}
	else
	{
		ret_val = E_FALSE;
	}
  return ret_val;
}

