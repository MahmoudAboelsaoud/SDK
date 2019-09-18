/*
 * WaveGeneration_Square_NM_CTC_modes.c
 *
 * Created: 4/28/2019 9:20:44 PM
 *  Author: M.Aboelsaoud
 */ 
#include <avr/interrupt.h>
ISR(TIMER0_COMP_vect)
{
  const unsigned char wavetable[]={24,49,39,34};
  static unsigned char index =0;
OCR0=wavetable[index];
index++;

if (index>=4)
index++;

}
//#define TIMER0
//#define TIMER1
//#define T0 
//#define  WAVES

#define WAVE_CAPTURE

#define TCCR0  *(volatile unsigned char*)0x53
#define TCNT0  *(volatile unsigned char*)0x52
#define OCR0   *(volatile unsigned char*)0x5c
#define DDRB   *(volatile unsigned char*)0x37


#ifdef TIMER1
#define TCCR1A   *(volatile unsigned char*)0x4f
#define TCCR1B   *(volatile unsigned char*)0x4e
#define OCR1AL   *(volatile unsigned char*)0x4a
#define OCR1AH   *(volatile unsigned char*)0x4b
#define OCR1BL   *(volatile unsigned char*)0x48
#define OCR1BH *(volatile unsigned char*)0x49
#define DDRD   *(volatile unsigned char*)0x31
#endif
/*#include <avr/io.h>*/

int main(void)
{
	#ifdef TIMER0
	/*CTC mode*/
	DDRB  |=(1<<3);
	TCCR0 |=(1<<0)|(1<<3)|(1<<4)|(1<<7);
	OCR0=100;
	#endif
	
	#ifdef TIMER1
	/*Normal mode OC1A */
	DDRD |=(1<<4)|(1<<5);
	TCCR1A |=(1<<4);
	TCCR1B|=(1<<0);
	#endif
	
	#ifdef TIMER1
	/*CTC mode OC1B */
	DDRD |=(1<<4)|(1<<5);
	OCR1AH =0x00;
    OCR1AL =0x0f;
	TCCR1A |=(1<<6);
	TCCR1B|=(1<<0)|(1<<3);
	#endif
	
	#ifdef T0
	
	/*OC0 output , T0 input*/
	DDRB |=(1<<3);
	DDRB &=~(1<<0);
	OCR0 =3;
	TCNT0=0;
	/* CTC mode ,toggle oc0, external clock */
	TCCR0 |=(1<<4)|(1<<2)|(1<<1)|(1<<0)|(1<<3);
	
	#endif
	
	#ifdef WAVES
	/* genarate mulitable waves, CTC, no prescaler, toggle in compeare match*/
	DDRB |=(1<<3);
	OCR0=69;
	TCCR0=0x19;
	TIMSK=(1<<OCIE0);
	sei();
	#endif
	
	#ifdef WAVE_CAPTURE
	/*unsigned int t;
	DDRA=0xff;
	DDRB=0xff;
	PORTD=0xff;
	
	TCCR1A=0;      //normal mode 
	TCCR1B=0x41;    //rising edge , no scaler , no noise canceller
	TCCR1B=0x45; 
	TIFR=(1<<ICF1);
	while((TIFR&(1<<ICF1))==0);
	t=ICR1L;
	
	
	
	TIFR=(1<<ICF1);
	while((TIFR&(1<<ICF1))==0);
	t=ICR1L-t;
	PORTA=t;
	PORTB=t>>8;
	PORTB= ICR1L-t;
	TIFR=(1<<ICF1);
	*/
	DDRA=0xff;
	DDRB=0xff;
	PORTD=0xff;
	while(1){
		TCCR1A=0;
		TCCR1B=0x41;
	
		while((TIFR&(1<<ICF1))==0);
		TIFR=(1<<ICF1);
		PORTA=ICR1L;
		PORTB=ICR1H;
		
		
		
		
	}
	
	
	
	#endif
	
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}