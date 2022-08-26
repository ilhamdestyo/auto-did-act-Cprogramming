//LIB LCD

#define myLCD PORTA
extern float FCPU;
#define rs PB0
#define en PB2

#include <util/delay.h>

//--- Latch Function ---//

void myLCD_latch()
{
	myLCD |= (1<<en);
	_delay_ms(1); 
	myLCD &= ~(1<<en);		//--- high to low to latch data into lcd
}

//--- Lcd Command ---//

void lcd_cmd(char x)
{
	myLCD &= ~(1<<rs);		//--- Register Select is Command Register
	myLCD &= 0x0F;			//--- Masking lower bit
	myLCD |= (x & 0xF0);		//--- Masking Higher bit and send to display
	myLCD_latch();			//--- latch function
	
	myLCD &= 0x0F;			//--- Masking lower bit
	myLCD |= ((x & 0x0F)<<4);	//--- Masking lower bit and send to display
	myLCD_latch();			//--- latch function 
}

//--- Lcd Data ---//

void lcd_dwr(char x)
{
	myLCD |= (1<<rs);			//--- Register Select is Data Register
	myLCD &= 0x0F;			//--- Masking lower bit
	myLCD |= (x & 0xF0);		//--- Masking Higher bit and send to display
	myLCD_latch();			//--- latch function
	
	myLCD &= 0x0F;			//--- Masking lower bit
	myLCD |= ((x & 0x0F)<<4); //--- Masking lower bit and send to display
	myLCD_latch();			//--- latch function
}

//--- Lcd String send ---//

void lcd_msg(char *c)
{
	while (*c != 0)			//--- Check for not equal zero
		lcd_dwr(*c++);		//--- Send String to Lcd
}

//--- Lcd init ---//

void lcd_init()
{
	lcd_cmd(0x03);			//--- Lcd initializing 
	lcd_cmd(0x02);			//--- Lcd initializing
	lcd_cmd(0x28);			//--- Lcd 4 bit mode cmd
	lcd_cmd(0x0E);			//--- Blinkng Cursor
	lcd_cmd(0x80);			//--- Starting address
	lcd_msg("LCD TEST SUCCESS"); //--- Test msg
	_delay_ms(1000);		//--- 1 sec delay
	lcd_cmd(0x01);			//--- Clear Lcd
	lcd_cmd(0x06);			//--- Auto incrementing
	lcd_cmd(0x80);			//--- Starting address of LCD
}
