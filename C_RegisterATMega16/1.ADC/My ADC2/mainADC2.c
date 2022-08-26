/**
 * compile:
 * avr-gcc -w -mmcu=atmega16 -o exeADC2 mainADC2.c
 * copy to file.hex 
 * avr-objcopy -O ihex -R eeprom exeADC2 exeADC2.hex
 * flash to microcontroller:
 * sudo avrdude -F -V -c usbasp -p ATmega16 -P usb -U flash:w:exeADC2.hex
 */
// include function file
#include <stdio.h>
#include "io.h"

//define my variable
double FCPU;
int valVar;
//unsigned char segmen [10]={0x3F, 0x6, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x7, 0x7F, 0x6F};
unsigned char segmen [10]={0b00111111, 0b00000110, 0b01011011, 0b01001111,
0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111}; //array

int adc(char ch);
void display(void);
void delay_ms (double __ms);
void Timer0delay();


int main()
{
	//FCPU=1;
	DDRC= 0xFF; //Port C sebagai output
	DDRB= 0xF0; //PortB 0-3 sebagai Input, PortB 4-7 sebagai Output
	ADMUX= 0xE0; //0b11100000, VRef internal =2.56V, format data rata kiri read hanya ADCH register, ADC0 sebagai Channel
	ADCSRA= 0x84; //ADC start conversion, prescale clock = F_CPU/16
	valVar=0;
	while(1){
		valVar= adc(1);
		display();
	}
}

int adc(char ch){
	ADMUX=ch; //0b00000001 ADC Multiple selection register
	delay_ms(1);
	/*
	 * ADC control dan status register,
	 * dimana |= adalah operasi bitwise yaitu "or equals"
	 * enable ADC
	 * Fr/16
	 */
	 ADCSRA|=0x40;
	 while ((ADCSRA & 0x10)==0);
	 ADCSRA|=0x10;
	 return ADCW;
}

void display (void){
	char a;
	for (a=0;a<250;a++){
		PORTC=segmen[valVar%10]; //formula ambil data satuan
		PORTB=0B01111111; //SELECTOR/SCAN DIGIT satuan
		delay_ms(1);
		PORTB=0B11111111; //SELECTOR/SCAN OFF
		
		PORTC=segmen[valVar/10%10]; //formula ambil data puluhan
		PORTB=0B10111111; //SELECTOR/SCAN DIGIT puluhan
		delay_ms(1);
		PORTB=0B11111111; //SELECTOR/SCAN OFF
		
		PORTC=segmen[valVar/100%10]; //formula ambil data data ratusan
		PORTB=0B11011111; //SELECTOR/SCAN DIGIT ratusan
		delay_ms(1);
		PORTB=0B11111111; //SELECTOR/SCAN OFF

		PORTC=segmen[valVar/1000%10]; //formula ambil data ribuan
		PORTB=0B11101111; //SELECTOR/SCAN DIGIT ribuan
		delay_ms(1);
		PORTB=0B11111111; //SELECTOR/SCAN OFF
	}
}

void delay_ms (double delaytime){
	uint16_t i = 0;
	
	double cputime_1micro;
	uint16_t cputimeMili;

	cputime_1micro = (float)(FCPU); //in microsecond
	cputimeMili = (uint16_t)(1000*cputime_1micro);
	
	while(i<delaytime* cputimeMili){
		i++;
		Timer0delay();
	}
}


void Timer0delay() //Timer0, for 1MHz clock, time = i/fcpu = 1 microsecond
{
	TCNT0 = 0;  		// Load TCNT0 with initial value = 0;
	TCCR0 = 0x01;  		// start Timer0, 00000001==> FOC0 = 0, WGM00 = 0 (Normal), COM01 = 0, COM00 = 0, WGM01 = 0 (Normal), CS02 = 0, CS01 = 0, CS00 = 1 (no pre-scalar)
	
	while(TIFR==0x01);  // TIFR = 00000001 ==> if TOV0 = 1 (Timer0 has overflow/going from 0xFF to 0x00), do nothing. (or,Wait for TOV0 to roll over)
	TCCR0 = 0; //stop Timer0 temporarily
	TIFR = 0x01;  // Clear TOV0 flag
}
