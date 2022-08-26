#ifndef SPI_MASTER_H_FILE_H_
#define SPI_MASTER_H_FILE_H_

#include "io.h"						/* Include AVR std. library file */

#define MOSI 5								/* Define SPI bus pins */
#define MISO 6
#define SCK 7
#define SS 4
#define SS_Enable PORTB &= ~(1<<SS)			/* Define Slave enable */
#define SS_Disable PORTB |= (1<<SS)			/* Define Slave disable */

/*SPI Function*/
//SPI Init function master
void SPI_Init_Master();					/* SPI Initialize function */
//SPI Init function slave
void SPI_Init_Slave();					/* SPI Initialize function */
//SPI_Write function
//Input argument: It has an input argument of data to be transmitted.
void SPI_Write(char);		/* SPI write data function */
//SPI_Read function
//Return value: It returns the received char data type.
char SPI_Read();				/* SPI read data function */
//SPI_Receive function
//Return value: it returns received char data type.
char SPI_Receive();			/* SPI Receive data function */
char SPI_Transmit(char);						/* SPI transmit data function */

#endif /* SPI_HAL*/

