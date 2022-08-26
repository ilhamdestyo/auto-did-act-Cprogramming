/**
 * Compile:
 * avr-gcc -w -mmcu=atmega16 -o exeMaster_SPI mainMaster_SPI.c lcd16x2_hal.c mytimer.c spi_hal.c
 * copy to hex:
 * avr-objcopy -j .text -j .data -O ihex exeMaster_SPI exeMaster_SPI.hex 
 */

#include <stdio.h>			/* Include Std. i/p o/p file */
#include <string.h>			/* Include String header file */

#include "io.h"			/* Include AVR std. library file */
#include "mytimer.h"			/* Include Delay header file */
#include "lcd16x2_hal.h"		/* Include LCD header file */
#include "spi_hal.h"		/* Include SPI master header file */


float FCPU=1;

int main(void)
{
	uint8_t count;
	char buffer[5];
	DDRB = 0x0F;
	
	LCD_Init();
	SPI_Init_Master();
	
	LCD_String_xy(1, 0, "Master Device");
	LCD_String_xy(2, 0, "Sending Data:    ");
	SS_Enable;
	count = 0;
	while (1)			/* Send Continuous count */
	{
		SPI_Write(count);
		sprintf(buffer, "%d   ", count);
		LCD_String_xy(2, 13, buffer);
		count++;
		if(count %2 ==0) PORTB = 0b00001111;
		else PORTB = 0b00001010;
		delay_ms(500);
	}
		
}
