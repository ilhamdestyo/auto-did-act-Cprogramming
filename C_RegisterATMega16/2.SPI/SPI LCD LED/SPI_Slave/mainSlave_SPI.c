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
	
	LCD_Init();
	SPI_Init_Slave();
	
	LCD_String_xy(1, 0, "Slave Device");
	LCD_String_xy(2, 0, "Receive Data:    ");
	while (1)
	{
		count = SPI_Receive();
		sprintf(buffer, "%d   ", count);
		LCD_String_xy(2, 13, buffer);
	}

}
