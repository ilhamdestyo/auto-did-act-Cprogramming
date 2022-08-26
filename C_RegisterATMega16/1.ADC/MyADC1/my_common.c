
//========Functions=======================
void Timer0delay() //Timer0, for 1MHz clock, time = i/fcpu = 1 microsecond
{
	TCNT0 = 0;  		// Load TCNT0 with initial value = 0;
	TCCR0 = 0x01;  		// start Timer0, 00000001==> FOC0 = 0, WGM00 = 0 (Normal), COM01 = 0, COM00 = 0, WGM01 = 0 (Normal), CS02 = 0, CS01 = 0, CS00 = 1 (no pre-scalar)
	
	while(TIFR==0x01);  // TIFR = 00000001 ==> if TOV0 = 1 (Timer0 has overflow/going from 0xFF to 0x00), do nothing. (or,Wait for TOV0 to roll over)
	TCCR0 = 0; //stop Timer0 temporarily
	TIFR = 0x01;  // Clear TOV0 flag
}

void delay_ms(uint16_t deltime){
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

// Initialization of ADC
void ADC_Init(void){
 ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));    //16Mhz/128 = 125Khz the ADC reference clock
 ADMUX |= (1<<REFS0);                //Voltage reference from Avcc (5v), AVcc with external capacitor at AREF or Selecting internal reference voltage
 ADCSRA |= (1<<ADEN);                //Turn on ADC
 ADCSRA |= (1<<ADSC);                //Do an initial conversion because this one is the slowest and to ensure that everything is up and running
}
