#include "spi.h"

void SPI_INIT(char state) {
	switch (state) {
	case 'M':
		SPI_DDR |= (1 << MOSI) | (1 << CLK) | (1 << SS);
		SPI_DDR &= ~(1 << MISO);
		SPCR = (1 << MSTR) | (1 << SPE);
		break;
	case 'S':
		SPI_DDR &= ~(1 << MOSI) | (1 << CLK) | (1 << SS);
		SPI_DDR |= (1 << MISO);
		SPCR = (1 << SPE);
		break;
	default:
		break;
	}
}
unsigned int spi_transmit(unsigned int data) {
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}

