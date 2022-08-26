//register for atmega16
#include <stdio.h>

//converts the I/O address to the memory address
#define __OFFSET 0x20 //memory mapped address - i/o address, eg. PORTA $1B ($3B), then 3B-1B = 20
#define _MMIO_BYTE(mem_addr) (*(volatile uint8_t *)(mem_addr))
#define ACCES_REGISTER_ADDRESS(io_addr) _MMIO_BYTE((io_addr) + __OFFSET)


//define PORTA and it's pin adress
#define PORTA   ACCES_REGISTER_ADDRESS(0x1B)
#define DDRA    ACCES_REGISTER_ADDRESS(0x1A)
#define PINA    ACCES_REGISTER_ADDRESS(0x19)
/* Timer 0 */
#define TCNT0   ACCES_REGISTER_ADDRESS(0x32)
#define TCCR0   ACCES_REGISTER_ADDRESS(0x33)
#define TIFR    ACCES_REGISTER_ADDRESS(0x38)

#define bit0    0
#define bit1    1
#define bit2    2
#define bit3    3
#define bit4    4
#define bit5    5
#define bit6    6
#define bit7    7

double FCPU;

void T0delay();
void delayms();
//========Main Program=============
int main(void){
	FCPU = 1; //in MHz
	DDRA = (1 << (bit0)); //give initial value 1 to DDRA bit0, configure as output
	DDRA |= (1 << (bit7)); //give value 1 to DDRA bit7, without destructing previous value of DDRA, configure as output
	
    for(;;) //do infinite loop
    {
        PORTA ^= (1 << (bit0)); //give value 1 to bit0, toggles the state of that pin every 5 ms (if previous value is 1, then next value is 0 and so on)
        delayms(5);
    }
	
	return 0;
}
//========End of Main Program=============

//========Functions=======================
void Timer0delay() //Timer0, for 1MHz clock, time = i/fcpu = 1 microsecond
{
	TCNT0 = 0;  		// Load TCNT0 with initial value = 0;
	TCCR0 = 0x01;  		// start Timer0, 00000001==> FOC0 = 0, WGM00 = 0 (Normal), COM01 = 0, COM00 = 0, WGM01 = 0 (Normal), CS02 = 0, CS01 = 0, CS00 = 1 (no pre-scalar)
	
	while(TIFR==0x01);  // TIFR = 00000001 ==> if TOV0 = 1 (Timer0 has overflow/going from 0xFF to 0x00), do nothing. (or,Wait for TOV0 to roll over)
	TCCR0 = 0; //stop Timer0 temporarily
	TIFR = 0x01;  // Clear TOV0 flag
}

void delayms(uint16_t deltime){
	uint16_t i = 0;
	
	double cputime_1micro;
	uint16_t cputimeMili;

	cputime_1micro = (float)(FCPU); //in microsecond
	cputimeMili = (uint16_t)(1000*cputime_1micro);
	
	while(i<deltime*cputimeMili){
		i++;
		Timer0delay();
	}
}

//compile : avr-gcc -o tes.elf tes.c
