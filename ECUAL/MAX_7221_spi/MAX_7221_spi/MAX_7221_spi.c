/*
 * MAX_7221_spi.c
 *
 * Created: 7/5/2019 5:29:21 PM
 *  Author: M.Aboelsaoud
 */ 


#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>


#define MISO  6
#define MOSI  5
#define SS    4
#define SCK   7



void spi_init_master(void)
{
	DDRB |=(1<<MOSI)|(1<<SCK)|(1<<SS);
	DDRB &=~(1<<MISO);
	SPCR=(1<<SPE)|(1<<MSTR)|(1<<SPR0);

}

void spi_excute_tx(unsigned char cmd ,unsigned char num)
{
	PORTB &=~(1<<SS);
	SPDR=cmd;
	while(!(SPSR &(1<<SPIF)));
	
	SPDR=num;
	while(!(SPSR &(1<<SPIF)));
	PORTB |=(1<<SS);

}
int main(void)
{
	spi_init_master();
	
	spi_excute_tx(0x09,0xff);
    spi_excute_tx(0x0B,0x07);
	spi_excute_tx(0x0A,0x0f);
	spi_excute_tx(0x0C,0x01);
	//spi_excute_tx(0x0f,5);
	spi_excute_tx(1,5);
	spi_excute_tx(2,6);
	spi_excute_tx(3,7);
	spi_excute_tx(4,8);
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}