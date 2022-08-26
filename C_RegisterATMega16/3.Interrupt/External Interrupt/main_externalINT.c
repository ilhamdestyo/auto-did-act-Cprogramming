//compile: avr-gcc -g -Wall -Os main_externalINT.c mytimer.c -o main.elf
#include "io.h"
#include "interrupt.h"
#include "mytimer.h"

#define bit0 	0
#define bit1 	1
#define bit2 	2
#define bit3 	3
#define bit4 	4
#define bit5 	5
#define bit6 	6
#define bit7 	7

float FCPU;

ISR(INT0_vect)
{
	PORTC=~PORTC;		/* toogle pada PORTC LED akan menyala ketika interrupt button di tekan*/
	delay_ms(50);  	/* Software debouncing control delay */
	
}
int main(void)
{
	FCPU = 8; //in MHz
	
	DDRC= 1<<bit7;		/* Make PORTC7 as output PORT*/
	DDRB &= (~1 << bit2); /* PORTD2 as input */
	PORTD= 1<<bit2;		/* Make pull up high */
	
	GICR = 1<<INT0;		/* Enable INT0*/
	MCUCR = 1<<ISC01 | 1<<ISC00;  /* Trigger INT0 on rising edge */
	
	sei();			/* Enable Global Interrupt */
	
	while(1);
}
