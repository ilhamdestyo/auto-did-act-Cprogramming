#ifndef SPI_H_
#define SPI_H_

#include "io.h"

#define SS 4
#define MOSI 5
#define MISO 6
#define CLK 7

#define SPI_DDR  DDRB
#define SPI_PORT PORTB

#define ENABLE()  (SPI_PORT &=~ (1<<SS))//enable for slave select
#define DISABLE() (SPI_PORT |=  (1<<SS))//disable for slave select

void SPI_INIT(char state);
unsigned int spi_transmit(unsigned int data);

#endif /* SPI_H_ */


