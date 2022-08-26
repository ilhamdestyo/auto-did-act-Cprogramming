#include <stdio.h>
#include "io.h"
#include "mylcd.h"


float FCPU = 8;
#define BAUDRATE 9600

void usart_init(void);
void usart_transmitt(char a);
char usart_receive(void);
void usart_msg(char *c); // for usart transmitt data send (string)

char tx_data;

int main(void){
	DDRA = 0xFF;
	DDRB = 0B00000111;
	lcd_init();
	
	usart_init();
	usart_msg("Inisialisasi USART"); //send data string
	usart_transmitt(0x0D);
	while(1){
		usart_msg("Input is:");
		tx_data = usart_receive(); //receive data dari RXD pin
		usart_transmitt(0x0D);
			lcd_cmd(0xC0);						//--- LCD Address
			lcd_dwr(tx_data);					//--- Send the received data to LCD
		usart_msg(">>");
		usart_transmitt(tx_data);
		usart_transmitt(0x0D);
		
	}
}

//fungsi usart
void usart_init(){
	UBRRH = 0x00;  //UBRR value untuk baud rate
	UBRRL = 0x33;  //set baud rate 9600 sesuai data sheet
	UCSRB = (1<<TXEN)|(1<<RXEN); //enable transmitt dan receive
	UCSRC = (1<<URSEL) | (3<<UCSZ0); // 8 bit data dan UCSRC select
}

void usart_transmitt(char a){
	UDR = a;  //pindahkan data a ke UDR data register
	while(!(UCSRA & (1<<UDRE))); //check whether UDR
}

char usart_receive(){
	while(!(UCSRA & (1<<RXC))); //check whether Receive
	return(UDR); //return data dari UDR
}

void usart_msg(char *c){
	while (*c !=0) //cek message jika tidak sama dengan 0
		usart_transmitt(*c++); //incremet pointer dari data usart transmitt
}
