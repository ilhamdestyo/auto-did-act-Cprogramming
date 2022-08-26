#include "fungsi_atmega16.h"
#include "io.h"

#define LTHRES 500
#define RTHRES 500
 
// initialize adc
void adc_init()
{
    // AREF = AVcc
    ADMUX = (1<<REFS0);
 
    // ADC Enable and prescaler of 128
    // 16000000/128 = 125000
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}
 
// read adc value
uint16_t adc_read(uint8_t ch)
{
    // select the corresponding channel 0~7
    // ANDing with '7' will always keep the value
    // of 'ch' between 0 and 7
    ch &= 0b00000111;  // AND operation with 7
    ADMUX = (ADMUX & 0xF8)|ch;     // clears the bottom 3 bits before ORing
 
    // start single conversion
    // write '1' to ADSC
    ADCSRA |= (1<<ADSC);
 
    // wait for conversion to complete
    // ADSC becomes '0' again
    // till then, run loop continuously
    while(ADCSRA & (1<<ADSC));
 
    return (ADC);
}
 
int main()
{
    uint16_t adc_result0, adc_result1;
    char int_buffer[10];
    DDRB = 0xFF;           // to connect led to PC0
 
    // initialize adc and lcd
    adc_init();
	delay_ms(50);
 
    while(1)
    {
        adc_result0 = adc_read(0);      // read adc value at PA0
        adc_result1 = adc_read(1);      // read adc value at PA1
 
        // condition for led to glow
        if (adc_result0 < LTHRES && adc_result1 < RTHRES)
            PORTB = 0xFF;
        else
            PORTB = 0x00;
 
        // now display on lcd
        itoa(adc_result0, int_buffer, 10);
 
        itoa(adc_result1, int_buffer, 10);
		delay_ms(50);
    }
}
// include function file
#include "my_common.c"

// Compiler : avr-gcc -o ledADC.elf ledADC.c
