
/*
 * RS: Register Select, Data/Instruction select, driven
 * high for data, and low for instruction.
 *
 */


#define F_CPU (8000000UL)
#include "Std_Types.h"
#include "Macros.h"
#include "DIO_interface.h"
#include "LCD_config.h"
#include "LCD_interface.h"
#include <util/delay.h>



void LCD_vidInit(void) {
#ifdef LCD_CONFIG_4BIT
	DIO_vidSetPinDirection(LCD_DATA_PORT,LCD_D4,DIO_OUTPUT);
	DIO_vidSetPinDirection(LCD_DATA_PORT,LCD_D5,DIO_OUTPUT);
	DIO_vidSetPinDirection(LCD_DATA_PORT,LCD_D6,DIO_OUTPUT);
	DIO_vidSetPinDirection(LCD_DATA_PORT,LCD_D7,DIO_OUTPUT);
#else
	DIO_vidSetPinDirection(LCD_DATA_PORT,LCD_D0,DIO_OUTPUT);
	DIO_vidSetPinDirection(LCD_DATA_PORT,LCD_D1,DIO_OUTPUT);
	DIO_vidSetPinDirection(LCD_DATA_PORT,LCD_D2,DIO_OUTPUT);
	DIO_vidSetPinDirection(LCD_DATA_PORT,LCD_D3,DIO_OUTPUT);
	DIO_vidSetPinDirection(LCD_DATA_PORT,LCD_D4,DIO_OUTPUT);
	DIO_vidSetPinDirection(LCD_DATA_PORT,LCD_D5,DIO_OUTPUT);
	DIO_vidSetPinDirection(LCD_DATA_PORT,LCD_D6,DIO_OUTPUT);
	DIO_vidSetPinDirection(LCD_DATA_PORT,LCD_D7,DIO_OUTPUT);
#endif

	DIO_vidSetPinDirection(LCD_CTRL_PORT,LCD_E,DIO_OUTPUT);
	DIO_vidSetPinDirection(LCD_CTRL_PORT,LCD_RS,DIO_OUTPUT);
	DIO_vidSetPinDirection(LCD_CTRL_PORT,LCD_RW,DIO_OUTPUT);
	_delay_ms(20);
#ifdef LCD_CONFIG_4BIT
	LCD_vidSendCommand(0x02);
	LCD_vidSendCommand(0x28);
	LCD_vidSendCommand(LCD_CLEAR_SCREEN); /*Clear screen*/
	LCD_vidSendCommand(LCD_RETURN_HOME); /*Move to home*/
	LCD_vidSendCommand(LCD_SET_ENTRY_MODE|LCD_MOVE_CURSOR_RIGHT); /*Set entry mode*/
	LCD_vidSendCommand(LCD_DISPLAY_ON); /*Display On/Off control*/
	_delay_ms(2);
#else
	LCD_vidSendCommand(LCD_FUNCTION_SET|LCD_8BIT|LCD_4LINES); /*Function Set*/
	LCD_vidSendCommand(LCD_CLEAR_SCREEN); /*Clear screen*/
	LCD_vidSendCommand(LCD_RETURN_HOME); /*Move to home*/
	LCD_vidSendCommand(LCD_SET_ENTRY_MODE|LCD_MOVE_CURSOR_RIGHT); /*Set entry mode*/
	LCD_vidSendCommand(LCD_FUNCTION_SET|LCD_8BIT|LCD_4LINES);
	LCD_vidSendCommand(LCD_DISPLAY_ON); /*Display On/Off control*/
#endif
}

void LCD_vidSendCommand(u8 commandCpy) {
#ifdef LCD_CONFIG_4BIT
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D4,GET_BIT(commandCpy,4));
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D5,GET_BIT(commandCpy,5));
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D6,GET_BIT(commandCpy,6));
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D7,GET_BIT(commandCpy,7));

	/*RS=0*/
	DIO_vidSetPinValue(LCD_CTRL_PORT,LCD_RS,STD_LOW);
	
	/*Sending enable signal*/
	DIO_vidSetPinValue(LCD_CTRL_PORT,LCD_E,STD_HIGH);
	_delay_us(1);
	DIO_vidSetPinValue(LCD_CTRL_PORT,LCD_E,STD_LOW);
	_delay_us(200);
	
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D4,GET_BIT(commandCpy,0));
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D5,GET_BIT(commandCpy,1));
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D6,GET_BIT(commandCpy,2));
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D7,GET_BIT(commandCpy,3));

	DIO_vidSetPinValue(LCD_CTRL_PORT,LCD_E,STD_HIGH);
	_delay_us(1);
	DIO_vidSetPinValue(LCD_CTRL_PORT,LCD_E,STD_LOW);
	_delay_ms(2);

#else
	DIO_vidSetPinValue(LCD_CTRL_PORT,LCD_RS,STD_LOW);
	DIO_vidSetPinValue(LCD_CTRL_PORT,LCD_RW,STD_LOW);

	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D0,GET_BIT(commandCpy,0));
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D1,GET_BIT(commandCpy,1));
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D2,GET_BIT(commandCpy,2));
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D3,GET_BIT(commandCpy,3));
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D4,GET_BIT(commandCpy,4));
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D5,GET_BIT(commandCpy,5));
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D6,GET_BIT(commandCpy,6));
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D7,GET_BIT(commandCpy,7));

	DIO_vidSetPinValue(LCD_CTRL_PORT,LCD_E,STD_HIGH);
	_delay_ms(2);
	DIO_vidSetPinValue(LCD_CTRL_PORT,LCD_E,STD_LOW);
	_delay_ms(2);
	DIO_vidSetPinValue(LCD_CTRL_PORT,LCD_E,STD_HIGH);
	_delay_ms(2);
#endif
}

void LCD_vidWriteCharacter(u8 charCpy) {
#ifdef LCD_CONFIG_4BIT
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D4,GET_BIT(charCpy,4));
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D5,GET_BIT(charCpy,5));
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D6,GET_BIT(charCpy,6));
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D7,GET_BIT(charCpy,7));

	/*RS=1*/
	DIO_vidSetPinValue(LCD_CTRL_PORT,LCD_RS,STD_HIGH);
	
	/*Sending enable signal*/
	DIO_vidSetPinValue(LCD_CTRL_PORT,LCD_E,STD_HIGH);
	_delay_us(1);
	DIO_vidSetPinValue(LCD_CTRL_PORT,LCD_E,STD_LOW);
	_delay_us(200);
	
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D4,GET_BIT(charCpy,0));
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D5,GET_BIT(charCpy,1));
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D6,GET_BIT(charCpy,2));
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D7,GET_BIT(charCpy,3));

	DIO_vidSetPinValue(LCD_CTRL_PORT,LCD_E,STD_HIGH);
	_delay_us(1);
	DIO_vidSetPinValue(LCD_CTRL_PORT,LCD_E,STD_LOW);
	_delay_ms(2);

#else
	DIO_vidSetPinValue(LCD_CTRL_PORT,LCD_RS,STD_HIGH);
	DIO_vidSetPinValue(LCD_CTRL_PORT,LCD_RW,STD_LOW);

	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D0,GET_BIT(charCpy,0));
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D1,GET_BIT(charCpy,1));
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D2,GET_BIT(charCpy,2));
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D3,GET_BIT(charCpy,3));
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D4,GET_BIT(charCpy,4));
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D5,GET_BIT(charCpy,5));
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D6,GET_BIT(charCpy,6));
	DIO_vidSetPinValue(LCD_DATA_PORT,LCD_D7,GET_BIT(charCpy,7));

	DIO_vidSetPinValue(LCD_CTRL_PORT,LCD_E,STD_HIGH);
	_delay_ms(2);
	DIO_vidSetPinValue(LCD_CTRL_PORT,LCD_E,STD_LOW);
	_delay_ms(2);
	DIO_vidSetPinValue(LCD_CTRL_PORT,LCD_E,STD_HIGH);
#endif
}

void LCD_vidWriteString(s8 * s8String) {	
	do {
		LCD_vidWriteCharacter(*s8String);
		(s8String++);
	}while(*s8String != '\0');
}

void LCD_vidWriteSizedString(s8 * s8String,u8 u8sizeCpy) {	
	u8 i = 0;
	do {
		LCD_vidWriteCharacter(*s8String);
		(s8String++);
		i++;
	}while(u8sizeCpy > i);
}

void LCD_vidBlinkString(s8 * s8stringCpy,u8 u8timesCpy) {
	u8 i = 0;
	s8 * s8string;
	s8string = s8stringCpy;
	do {
		_delay_ms(500);	
		while(*s8string != '\0') {
			LCD_vidWriteCharacter(*s8string);
			(s8string++);
		}
		_delay_ms(500);
		i++;
		LCD_vidSendCommand(LCD_CLEAR_SCREEN);
		s8string = s8stringCpy;
	}
	while (u8timesCpy > i);
}

void LCD_vidWriteNumber(u16 u16NumberCpy) {
	if(u16NumberCpy < 10) {
		LCD_vidWriteCharacter('0');
		LCD_vidWriteCharacter(u16NumberCpy+'0');
	}
	else {
		if (u16NumberCpy < 100) {
			LCD_vidWriteCharacter(u16NumberCpy/10+'0');
			LCD_vidWriteCharacter(u16NumberCpy%10+'0');
		}
		else if (u16NumberCpy < 1000) {
			LCD_vidWriteCharacter((u16NumberCpy/100)+'0');
			LCD_vidWriteCharacter((u16NumberCpy%100)/10+'0');
			LCD_vidWriteCharacter((u16NumberCpy%100)%10+'0');
		}
		else if (u16NumberCpy < 10000)
		{
			LCD_vidWriteCharacter((u16NumberCpy/1000)+'0');
			LCD_vidWriteCharacter((u16NumberCpy%1000)/100+'0');
			LCD_vidWriteCharacter((u16NumberCpy%100)/10+'0');
			LCD_vidWriteCharacter((u16NumberCpy%100)%10+'0');
		}
	}
}

/*Write a number with a fixed number of digits, zeros from the left to complete
 *the fixed size.
 * */
void LCD_vidWriteSizedNumber(u16 u16NumberCpy, u8 u8Size)
{
	u8 u8i;
	if(u16NumberCpy < 10) {
		for (u8i = 0; u8i < u8Size-1; u8i++)
		{		
			LCD_vidWriteCharacter('0');
		}
		LCD_vidWriteCharacter(u16NumberCpy+'0');
	}
	else {
		if (u16NumberCpy < 100) {
			for (u8i = 0; u8i < u8Size-2; u8i++)
			{		
				LCD_vidWriteCharacter('0');
			}

			LCD_vidWriteCharacter(u16NumberCpy/10+'0');
			LCD_vidWriteCharacter(u16NumberCpy%10+'0');
		}
		else if (u16NumberCpy < 1000) {
			for (u8i = 0; u8i < u8Size-3; u8i++)
			{		
				LCD_vidWriteCharacter('0');
			}
			LCD_vidWriteCharacter((u16NumberCpy/100)+'0');
			LCD_vidWriteCharacter((u16NumberCpy%100)/10+'0');
			LCD_vidWriteCharacter((u16NumberCpy%100)%10+'0');
		}
		else if (u16NumberCpy < 10000)
		{
			for (u8i = 0; u8i < u8Size-4; u8i++)
			{		
				LCD_vidWriteCharacter('0');
			}
			LCD_vidWriteCharacter((u16NumberCpy/1000)+'0');
			LCD_vidWriteCharacter((u16NumberCpy%1000)/100+'0');
			LCD_vidWriteCharacter((u16NumberCpy%100)/10+'0');
			LCD_vidWriteCharacter((u16NumberCpy%100)%10+'0');
		}
	}

}

void LCD_vidGoToXY(u8 u8xCpy, u8 u8yCpy) {
#define LCD_SET_CURSOR_LOCATION 0x80
	u8 u8address = u8xCpy;
	switch(u8yCpy) {
		case 0:
			u8address = u8xCpy;
			break;
		case 1:
			u8address = u8xCpy+0xC0;
			break;
		case 2:
			u8address = u8xCpy+0x94;
			break;
		case 3:
			u8address = u8xCpy+0xD4;
			break;
	}
	LCD_vidSendCommand(u8address | 0x80);
}

#define SET_CURSOR_LOCATION
void LCD_vidCreateCustomChar(u8 * u8CharPtrCpy, u8 u8LocationCpy) {
	u8 i = 0;
	LCD_vidSendCommand(0x40+(u8LocationCpy*8)); /*Setting to CGRAM address8*/
	while (i != 8) {
		LCD_vidWriteCharacter(*u8CharPtrCpy++);
		i++;
	}
	LCD_vidWriteCharacter(0x00+u8LocationCpy);
}

void LCD_vidWriteCustomChar(u8 u8LocationCpy) {
	LCD_vidWriteCharacter(0x00+u8LocationCpy);
}

/*This function has been reedited to allow writing a character
 *on a specific row and a specific column.
 * */
void LCD_vidWriteInPlace(u8 u8xCpy,u8 u8yCpy, u8 u8CharCpy) {
	LCD_vidGoToXY(u8xCpy,u8yCpy);
	LCD_vidWriteCharacter(u8CharCpy);
}

void LCD_vidClearSpace(u8 u8xPosStart, u8 u8xPosEnd ,u8 u8yPos)
{
	u8 u8i = 0;
	LCD_vidGoToXY(u8xPosStart,u8yPos);
	for (u8i = 0; u8i < u8xPosEnd; u8i++)
	{
		LCD_vidWriteCharacter(' ');	
	}
	LCD_vidGoToXY(u8xPosStart,u8yPos);
}

void LCD_vidClearLine(u8 u8LineNumber)
{
	LCD_vidGoToXY(LCD_XPOS0,u8LineNumber);
	u8 u8xPos;
	for (u8xPos = 0; u8xPos < 20; u8xPos++)
	{
		LCD_vidWriteCharacter(' ');
	}
}
