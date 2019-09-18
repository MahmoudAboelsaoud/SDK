/*
 * WaveGeneration_PWM.c
 *
 * Created: 5/11/2019 2:33:51 AM
 *  Author: M.Aboelsaoud
 */ 

#define PWM_FAST
//#define PWM_PHASE_CORRECT
#define TIMER1

#define DDRB   *(volatile unsigned char*)0x37
#define DDRD   *(volatile unsigned char*)0x31

#define TCCR0  *(volatile unsigned char*)0x53
#define TCNT0  *(volatile unsigned char*)0x52
#define OCR0   *(volatile unsigned char*)0x5c



#ifdef TIMER1
#define TCCR1A   *(volatile unsigned char*)0x4f
#define TCCR1B   *(volatile unsigned char*)0x4e
#define OCR1AL   *(volatile unsigned char*)0x4a
#define OCR1AH   *(volatile unsigned char*)0x4b
#define OCR1BL   *(volatile unsigned char*)0x48
#define OCR1BH   *(volatile unsigned char*)0x49

#endif

int main(void)
{
	#ifdef PWM_FAST
	
	//OC0 output
	DDRB|=(1<<3);
	OCR0=99;
	//fast pwm , inverted pwm , no prescaler
	TCCR0|=(1<<0)|(1<<3)|(1<<4)|(1<<5)|(1<<6);
	
	
	//timer1, fast pwm, mode 6, non_inverting, f=1953Hz, DT=60% 
	DDRD|=(1<<5);  //OC1A
	OCR1AH =306>>8;
	OCR1AL =306;
	TCCR1A |=(1<<7)|(1<<1); 
	TCCR1B |=(1<<3)|(1<<1); 
	
	
	DDRD|=(1<<4);
	OCR1BH =204>>8;
	OCR1BL =204;
	TCCR1A =0xb2;//|=(1<<7)|(1<<6)|(1<<1);
	TCCR1B =0x0a;//|=(1<<3)|(1<<1);
	
	
	
	
	
	#endif
	
	#ifdef PWM_PHASE_CORRECT
	/*OC0 output*/
	DDRB|=(1<<3);
	OCR0=0;
	/*phase correct pwm , inverted pwm ,prescaler 256*/
	TCCR0|=(1<<2)|(1<<4)|(1<<5)|(1<<6);
	
	#endif
	
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}