//compile: avr-gcc -g -Wall -Os main_internalINT.c mytimer.c -o main.elf
#include "mytimer.h"
#include "io.h"
#include "interrupt.h"

#define myLCD PORTB
#define rs PD0 //pin RS terhubung pada PD0 sehingga value = PD0
#define rw PD1 //pin RW terhubung pada PD1 sehingga value = PD1
#define en PD2 //Enable di pin PD2

void adc_init(void);
unsigned int adc_read(void);
void adc_conversion(uint16_t);
void lcd_init(void);
void lcdcmd(unsigned char);
void lcddata(unsigned char);

float FCPU = 1;
uint16_t adc_out;



int main(){
	unsigned char data[12]= "ADC OUTPUT:";
	
	int i=0;
	DDRD=0x07;
	DDRB=0xFF;
	DDRC=0xFF;
	lcd_init();
	
	while(data[i]!='0'){
		lcddata(data[i]);
		delay_ms(5);
		i++;
	}
	
	adc_init();
	
	/* Configure timer0*/
	TCCR0=(1<<CS02) | (1<<CS00); 
	TIMSK=(1<<TOIE0);
	sei();
	
	while(1);
}

ISR(ADC_vect){
adc_conversion((ADC));
}

ISR(TIMER0_OVF_vect){
}

// ADC configuration
void adc_init(){
	ADMUX=(1<<REFS0); //Vref=AVcc
	// ADSC=1 ADC Enable
	// ADPS[2:0]=111, prescaler=128
	// ADIE=1, ADC interrupt Enable
	//ADATE=1, ADC Auto Triggering Enable
	ADCSRA=(1<<ADEN)|(7<<ADPS0)|(1<<ADSC)|(1<<ADIE)|(1<<ADATE);
	
	//ADTS[2:0]= 100 , Timer0 overflow select as trigger source
	SFIOR=(4<<ADTS0);
}


/* this function is written to convert interger value to their corresponding ASCII value*/
void adc_conversion(uint16_t adc_out){
	unsigned int adc_out1;
	int i=0;
	char position=0xC3;
	
	for(i=0;i<=3;i++){
		adc_out1=adc_out%10;
		adc_out=adc_out/10;
		lcdcmd(position);
		lcddata(48+adc_out1);
		position--;
	}
}

// fuction for LCD initialization
void lcd_init(){
	lcdcmd(0x38);
	lcdcmd(0x0C);
	lcdcmd(0x01);
	lcdcmd(0x06);
	lcdcmd(0x80);
}

void lcdcmd(unsigned char cmdout){
	myLCD=cmdout;
	PORTD=(0<<rs)|(0<<rw)|(1<<en);
	delay_ms(10);
	PORTD=(0<<rs)|(0<<rw)|(0<<en);
}


void lcddata(unsigned char dataout){
	myLCD=dataout;
	PORTD=(1<<rs)|(0<<rw)|(1<<en);
	delay_ms(10);
	PORTD=(1<<rs)|(0<<rw)|(0<<en);
}
