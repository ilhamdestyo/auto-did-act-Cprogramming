/*SPI Function*/
#include "spi_hal.h"				/* Include SPI header file */

//SPI Init function master
void SPI_Init_Master()					/* SPI Initialize function */
{
	DDRB |= (1<<MOSI)|(1<<SCK)|(1<<SS);		/* Make MOSI, SCK, 0th pin direction as output pins */
	DDRB &= ~(1<<MISO);						/* Make MISO pin as input pin */
	PORTB |= (1<<SS);						/* Disable slave initially by making high on SS pin */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);	/* Enable SPI, Enable in master mode, with Fosc/16 SCK frequency */
	SPSR &= ~(1<<SPI2X);					/* Disable speed doubler */
}

//SPI Init function slave
void SPI_Init_Slave()					/* SPI Initialize function */
{
	DDRB &= ~((1<<MOSI)|(1<<SCK)|(1<<SS));		/* Make MOSI, SCK, SS pin direction as input pins */
	DDRB |= (1<<MISO);							/* Make MISO pin as output pin */
	SPCR = (1<<SPE);							/* Enable SPI in slave mode */
}


//SPI_Write function
//Input argument: It has an input argument of data to be transmitted.
void SPI_Write(char data)		/* SPI write data function */
{
	char flush_buffer;
	SPDR = data;			/* Write data to SPI data register */
	while(!(SPSR & (1<<SPIF)));	/* Wait till transmission complete */
	flush_buffer = SPDR;		/* Flush received data */
/* Note: SPIF flag is cleared by first reading SPSR (with SPIF set) and then accessing SPDR hence flush buffer used here to access SPDR after SPSR read */
}

//SPI_Read function
//Return value: It returns the received char data type.
char SPI_Read()				/* SPI read data function */
{
	SPDR = 0xFF;
	while(!(SPSR & (1<<SPIF)));	/* Wait till reception complete */
	return(SPDR);			/* Return received data */
}

//SPI_Transmitt function slave
char SPI_Transmit(char data)					/* SPI transmit data function */
{
	SPDR = data;								/* Write data to SPI data register */
	while(!(SPSR & (1<<SPIF)));					/* Wait till transmission complete */
	return(SPDR);								/* return received data */
}
//SPI_Receive function slave
//Return value: it returns received char data type.
char SPI_Receive()			/* SPI Receive data function */
{
	while(!(SPSR & (1<<SPIF)));	/* Wait till reception complete */
	return(SPDR);			/* Return received data */
}
