#ifndef LCD_16x2_H_H_					/* Define library H file if not defined */
#define LCD_16x2_H_H_

#include "io.h"					/* Include AVR std. library file */
#include "mytimer.h"					/* Include Delay header file */

#define LCD_Data_Dir DDRD				/* Define LCD data port direction */
#define LCD_Command_Dir DDRC			/* Define LCD command port direction register */
#define LCD_Data_Port PORTD				/* Define LCD data port */
#define LCD_Command_Port PORTC			/* Define LCD data port */
#define EN PC2							/* Define Enable signal pin */
#define RW PC3							/* Define Read/Write signal pin */
#define RS PC4							/* Define Register Select (data reg./command reg.) signal pin */

void LCD_Command (char);				/* LCD command write function */
void LCD_Char (char);					/* LCD data write function */
void LCD_Init (void);					/* LCD Initialize function */
void LCD_String (char*);				/* Send string to LCD function */
void LCD_String_xy (char,char,char*);	/* Send row, position and string to LCD function */


#endif									/* LCD_16x2_H_FILE_H_ */
