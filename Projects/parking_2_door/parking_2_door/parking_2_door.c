/*
 * parking_2_door.c
 *
 * Created: 7/24/2019 4:50:32 PM
 *  Author: M.Aboelsaoud
 */ 


/*#include <avr/io.h>*/
#include <avr/interrupt.h>

#define GICR    *(volatile unsigned char*)0x5b
#define GIFR    *(volatile unsigned char*)0x5a
#define MCUCR   *(volatile unsigned char*)0x55
#define MCUCSR  *(volatile unsigned char*)0x54
#define SREG    *(volatile unsigned char*)0x5f


#define  DIR_PORTA   (*(volatile unsigned char*)0x3a)
#define  INPUT_PORTA (*(volatile unsigned char*)0x39)
#define  OUTPUT_PORTA (*(volatile unsigned char*)0x3b)

#define  DIR_PORTB   (*(volatile unsigned char*)0x37)
#define  INPUT_PORTB (*(volatile unsigned char*)0x36)
#define  OUTPUT_PORTB (*(volatile unsigned char*)0x38)

#define  DIR_PORTD   (*(volatile unsigned char*)0x31)
#define  INPUT_PORTD (*(volatile unsigned char*)0x30)
#define  OUTPUT_PORTD (*(volatile unsigned char*)0x32)

#define SET_PIN(reg ,pin) (reg |=(1<<pin))
#define CLEAR_PIN(reg ,pin) (reg &= ~(1<<pin))
#define TOGGAL_PIN(reg ,pin) (reg ^=(1<<pin))

int car_counter = 0;
int sensor_door_1 = 0;
int sensor_door_2 = 0;

ISR(INT0_vect)
{
	/*first door at get in the garage*/
	sensor_door_1 = 1;
}

ISR(INT1_vect)
{
	/*second door at get in the garage*/
	sensor_door_2 = 1;
}

void external_interrupt_config()
{
	MCUCR |=(1<<0)|(1<<1)|(1<<2)|(1<<3);
	GICR  |=(1<<6)|(1<<7);
	SREG  |=(1<<7);
}


int main(void)
{
	/*input*/
	CLEAR_PIN(DIR_PORTD,2);
	CLEAR_PIN(DIR_PORTD,3);
	/*output*/
	SET_PIN(DIR_PORTB,0);
	SET_PIN(DIR_PORTB,1);
	
	/* 7 seg port*/
	DIR_PORTA=0xff;
	
	/*port d init*/
	
	CLEAR_PIN(OUTPUT_PORTB,0);
	CLEAR_PIN(OUTPUT_PORTB,1);
	
	OUTPUT_PORTA=car_counter;
	
	external_interrupt_config();
	
    while(1)
    {
       if (sensor_door_1 == 1)
       {
		   if (sensor_door_2 == 1)
		   {
			   car_counter++;
			   TOGGAL_PIN(OUTPUT_PORTB,0);
			   OUTPUT_PORTA=car_counter;
			   sensor_door_2=0;
			   sensor_door_1=0;
		   }
       }
	   
	   if(sensor_door_2 == 1)
 	     {
			   if(sensor_door_1 == 1)
			   {
				   car_counter--;
				   TOGGAL_PIN(OUTPUT_PORTB,1);
				   OUTPUT_PORTA=car_counter;
				   sensor_door_1=0;
				   sensor_door_2=0;
				   //break;
			   }
			   
		   }
	}
	
	
	 sensor_door_2=0;
	 sensor_door_1=0;
}