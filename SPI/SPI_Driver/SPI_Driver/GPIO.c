/*
 * GPIO.c
 *
 *  Created on: Oct 9, 2018
 *      Author: Aboelsaoud ^_^
 */

#include "common.h"
#include "GPIO.h"

bool_t GPIO_PortInit( enum_port_t port, uint_8 pins, uint_8 init_value)
{
	bool_t ret_val = E_FALSE;
  if( ((port==PORTD)||(port ==PORTB)||(port ==PORTC)||(port ==PORTA)) && ((init_value==0)||((init_value==1))) )
	{
		if(init_value==0)
		{
			if(port==PORTA)
			{
				PORTA1 &=~(1<<pins);
			}
			else if(port==PORTB)
			{
				PORTB1 &=~(1<<pins);
			}
			else if(port==PORTC)
			{
				PORTC1 &=~(1<<pins);
			}
			else
			{
				PORTD1 &=~(1<<pins);
			}
		}
		else if(init_value==1)
		  {
			if(port==PORTB)
			{
				PORTB1|=(1<<pins);
			}
		    else if(port==PORTA)
			{
				PORTA1|=(1<<pins);
			}
			else if(port==PORTC)
			{
				PORTC1|=(1<<pins);
			}
			else
			{
				PORTD1|=(1<<pins);
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

bool_t GPIO_PortDirection(enum_port_t port, uint_8 pins, uint_8 port_dir)
{
	bool_t ret_val = E_FALSE;
	
   if( 1 /*((port==PORTD)||(port ==PORTB)||(port ==PORTC)||(port ==PORTA)) && ((port_dir==INPUT)||((port_dir==OUTPUT)))*/)
	{
		if (port_dir==INPUT)
		{
			if(port==PORTA1)
			{
				DDRA &=~(1<<pins);
			}
			else if(port==PORTB1)
			{
				DDRB &=~(1<<pins);
			}
			else if(port==PORTC1)
			{
				DDRC &=~(1<<pins);
			}
			else 
			{
				DDRD &=~(1<<pins);
			}
		}
		else if(port_dir==OUTPUT)
		{
			if(port==PORTB1)
			{
				DDRB|=(1<<pins);
			}
		    else if(port==PORTA1)
			{
				DDRA|=(1<<pins);
			}
		    else if(port==PORTC1)
			{
				DDRC|=(1<<pins);
			}
			else			{
				DDRD|=(1<<pins);
			}
		}
		else
		{
			ret_val=E_FALSE;
		}
		
		
	}
	else
	{
		ret_val=E_FALSE;
	}
	return ret_val;
}

bool_t GPIO_Pin_Set(enum_port_t port, uint_8 pins)
{
	bool_t ret_val = E_FALSE;
	if(((port==PORTD)||(port ==PORTB)||(port ==PORTC)||(port ==PORTA)) && ((pins>=0)||((pins<=7))))
	{
		if(port==PORTB)
		{
			PORTB1|=(1<<pins);
		}
		else if(port==PORTA)
		{
			PORTA1|=(1<<pins);
		}
		else if(port==PORTC)
		{
			PORTC1|=(1<<pins);
		}
		else			{
			PORTD1|=(1<<pins);
		}
	}
	else
	{
		ret_val=E_FALSE;
	}
	return ret_val;
}


bool_t GPIO_Pin_Clear(enum_port_t port, uint_8 pins)
{
	bool_t ret_val = E_FALSE;
	if(((port==PORTD)||(port ==PORTB)||(port ==PORTC)||(port ==PORTA)) && ((pins>=0)||((pins<=7))))
	{
		if(port==PORTB)
		{
			PORTB1&=~(1<<pins);
		}
		else if(port==PORTA)
		{
			PORTA1&=~(1<<pins);
		}
		else if(port==PORTC)
		{
			PORTC1&=~(1<<pins);
		}
		else			{
			PORTD1&=~(1<<pins);
		}
	}
	else
	{
		ret_val=E_FALSE;
	}
	return ret_val;
}

bool_t GPIO_Pin_Togal(enum_port_t port, uint_8 pins)
{
	bool_t ret_val = E_FALSE;
	if(((port==PORTD)||(port ==PORTB)||(port ==PORTC)||(port ==PORTA)) && ((pins>=0)||((pins<=7))))
	{
		if(port==PORTB)
		{
			PORTB1^=(1<<pins);
		}
		else if(port==PORTA)
		{
			PORTA1^=(1<<pins);
		}
		else if(port==PORTC)
		{
			PORTC1^=(1<<pins);
		}
		else			{
			PORTD1^=(1<<pins);
		}
	}
	else
	{
		ret_val=E_FALSE;
	}
	return ret_val;
}



/*
bool_t port_init(str_pin_t* obg)
{
	bool_t ret_val =E_TRUE;
	if(obg!=NULL)
	{
		if(obg->status==INPUT)
		{
			// DDRx
			*(volatile unsigned char*)(obg->port-1)=0x00;
		}
		else
		{
			// DDRx
			*(volatile unsigned char*)(obg->port-1)=0xff;
		}
	}
	else
	{
		ret_val=E_FALSE;
	}

	return ret_val;
}




bool_t set_pin(str_pin_t* obg, uint_8 pin_num)
{
	bool_t ret_val =E_TRUE;
	if(obg!=NULL)
		{
		              //DDR
			*(volatile unsigned char*)(obg->port-1) |=(1<< pin_num);
			*(volatile unsigned char*)obg->port     |= (1<< pin_num);

		}
		else
		{
			ret_val=E_FALSE;
		}

	return ret_val;
}


bool_t clear_pin(str_pin_t* obg, uint_8 pin_num)
{
	bool_t ret_val =E_TRUE;
	if(obg!=NULL)
		{
		                 //DDR
		   *(volatile unsigned char*)(obg->port-1) |= (1<< pin_num);
		   *(volatile unsigned char*)obg->port   &= ~(1<< pin_num);

		}
		else
		{
			ret_val=E_FALSE;
		}

	return ret_val;
}


bool_t togal_pin(str_pin_t* obg, uint_8 pin_num)
{
	bool_t ret_val =E_TRUE;
	if(obg!=NULL)
		{
		                 //DDR
       		 *(volatile unsigned char*)(obg->port-1) |= (1<< pin_num);
		     *(volatile unsigned char*)obg->port   ^= (1<< pin_num);
		}
		else
		{
			ret_val=E_FALSE;
		}

	return ret_val;
}


bool_t set_group_of_pins(str_pin_t* obg, uint_8*arr_ptr, uint_8 pins_count)
{
	bool_t ret_val =E_TRUE;
	if(obg!=NULL)
		{
		uint_8 i;
				for(i=0; i < pins_count; i++)
				{
					//DDR
					*(volatile unsigned char*)(obg->port-1) |=(1<< *(arr_ptr+i));
					*(volatile unsigned char*)obg->port   |= (1<< *(arr_ptr+i));
				}

		}
		else
		{
			ret_val=E_FALSE;
		}

	return ret_val;
}



bool_t clear_group_of_pins(str_pin_t* obg, uint_8*arr_ptr, uint_8 pins_count)
{
	bool_t ret_val =E_TRUE;
	if(obg!=NULL)
		{
		uint_8 i;
			for(i=0; i < pins_count; i++)
    			{
				             //DDR
					*(volatile unsigned char*)(obg->port-1) |=(1<< *(arr_ptr+i));
					*(volatile unsigned char*)obg->port     &= ~(1<< *(arr_ptr+i));
				}

		}
		else
		{
			ret_val=E_FALSE;
		}

	return ret_val;
}


bool_t pur_set(str_pin_t* obg)
{
	bool_t ret_val =E_TRUE;
	if(obg!=NULL)
	{
		//DDR
		*(volatile unsigned char*)(obg->port-1)=0x00;
		//port
		*(volatile unsigned char*)(obg->port)=0xff;
		//SFIOR
		*(volatile unsigned char*)0x50 |=(1<<2);

	}
	else
	{
		ret_val=E_FALSE;
	}

	return ret_val;
}




*/