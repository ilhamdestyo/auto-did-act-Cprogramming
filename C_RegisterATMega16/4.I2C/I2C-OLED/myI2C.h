#include <stdio.h>

#ifndef __TWI_H__
#define __TWI_H__
  // define clock
  #if defined(__AVR_ATmega16__)
    #define FCPU 16000000
  #endif
  extern double FCPU;

  // define register for TWI communication
  // -------------------------------------------
  #if defined(__AVR_ATmega16__) || defined(__AVR_ATmega8__) || defined(__AVR_ATmega328P__)
    #define I2C_TWAR TWAR // TWI (Slave) Address Register
    #define I2C_TWBR TWBR // TWI Bit Rate Register
    #define I2C_TWDR TWDR // TWI Data Register
    #define I2C_TWCR TWCR // TWI Control Register
    #define I2C_TWSR TWSR // TWI Status Register
    #endif

  // TWI CLK frequency
  //  @param TWBR
  //  @param Prescaler
  //    TWPS1 TWPS0  - PRESCALER
  //      0     0    -     1
  //      0     1    -     4
  //      1     0    -    16
  //      1     1    -    64
  #define I2C_FREQ(BIT_RATE, PRESCALER) { I2C_TWBR = BIT_RATE; I2C_TWSR |= (I2C_TWSR & 0x03) | PRESCALER; }
  
  /* Enable TWI, generate START */
  // TWI start condition 
  // (1 <<  TWEN) - untuk I2C Enable
  // (1 << TWINT) - untuk I2C Interrupt Flag - must be cleared by set
  // (1 << TWSTA) - TWI Start
  #define I2C_START() { I2C_TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWSTA); }

  /* Enable TWI & clear interrupt flag */
  // TWI enable
  // (1 <<  TWEN) - TWI Enable
  // (1 << TWINT) - TWI Interrupt Flag - must be cleared by set
  #define I2C_ENABLE() { I2C_TWCR = (1 << TWEN) | (1 << TWINT); }

  // TWI stop condition
  // (1 <<  TWEN) - TWI Enable
  // (1 << TWINT) - TWI Interrupt Flag - must be cleared by set
  // (1 << TWSTO) - TWI Stop
  #define I2C_STOP() { I2C_TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWSTO); }

  // TWI test if TWINT Flag is set
  #define I2C_WAIT_TILL_TWINT_IS_SET() { while (!(I2C_TWCR & (1 << TWINT))); }

  // TWI status mask
  #define I2C_STATUS (I2C_TWSR & 0xF8)
 
  // success return value
  #ifndef SUCCESS
    #define SUCCESS             0
  #endif
  // success return value
  #ifndef ERROR
    #define ERROR               1
  #endif 
  // ++++++++++++++++++++++++++++++++++++++++++
  //
  //        M A S T E R   M O D E
  //
  // ++++++++++++++++++++++++++++++++++++++++++  
  // Master Mode - Transmitter / Receiver
  #define I2C_START_ACK         0x08  // A START condition has been transmitted
  #define I2C_REP_START_ACK     0x10  // A repeated START condition has been transmitted
  #define I2C_FLAG_ARB_LOST     0x38  // Arbitration lost in SLA+W or NOT ACK bit
  // Master Transmitter Mode
  #define I2C_MT_SLAW_ACK       0x18  // SLA+W has been transmitted; ACK has been received
  #define I2C_MT_SLAW_NACK      0x20  // SLA+W has been transmitted; NOT ACK has been received
  #define I2C_MT_DATA_ACK       0x28  // Data byte has been transmitted; ACK has been received
  #define I2C_MT_DATA_NACK      0x30  // Data byte has been transmitted; NOT ACK has been received  
  // Master Receiver Mode
  #define I2C_MR_SLAR_ACK       0x40  // SLA+R has been transmitted; ACK has been received
  #define I2C_MR_SLAR_NACK      0x48  // SLA+R has been transmitted; NOT ACK has been received
  #define I2C_MR_DATA_ACK       0x50  // Data byte has been received; ACK has been received
  #define I2C_MR_DATA_NACK      0x58  // Data byte has been received; NOT ACK has been received
  
  // ++++++++++++++++++++++++++++++++++++++++++
  //
  //         S L A V E   M O D E
  //
  // ++++++++++++++++++++++++++++++++++++++++++
  // Slave Receiver Mode
  #define I2C_SR_SLAW_ACK       0x60  // Own Slave address has been received; ACK returned
  #define I2C_SR_ALMOA_ACK      0x68  // Arbitration Lost in SLA+R/W as Master; Own Slave address has been received; ACK returned
  #define I2C_SR_GCALL_ACK      0x70  // General call address has been received; ACK returned
  #define I2C_SR_ALMGA_ACK      0x78  // Arbitration lost in SLA+R/W as Master; General call address has been received; ACK returned  
  #define I2C_SR_OA_DATA_ACK    0x80  // Previously addressed with own SLA+W; data has been received; ACK returned
  #define I2C_SR_OA_DATA_NACK   0x88  // Previously addressed with own SLA+W; data has been received; NOT ACK returned
  #define I2C_SR_GC_DATA_ACK    0x90  // Previously addressed with general call; data has been received; ACK returned
  #define I2C_SR_GC_DATA_NACK   0x98  // Previously addressed with general call; data has been received; NOT ACK returned
  #define I2C_SR_STOP_RSTART    0xA0  // A STOP condition or repeated START condition has been received while still addressed as Slave
  // Slave Transmitter Mode
  #define I2C_ST_OA_ACK         0xA8  // Own SLA+R has been received; ACK has been returned
  #define I2C_ST_ALMOA_ACK      0xB0  // Arbitration lost in SLA+R/W as Master; own SLA+R has been received; ACK has been received
  #define I2C_ST_DATA_ACK       0xB8  // Data byte in TWDR has been transmitted; ACK has been received
  #define I2C_ST_DATA_NACK      0xC0  // Data byte in TWDR has been transmitted; NOT ACK has been received
  #define I2C_ST_DATA_LOST_ACK  0xC8  // Last data byte in TWDR has been transmitted (TWEA = '0'); ACK has been received

  void I2C_Init(void);
  char I2C_MT_Start(void);
  char I2C_MT_Send_SLAW(char);
  char I2C_MT_Send_Data(char);
  char I2C_MR_Send_SLAR(char);
  void I2C_Stop(void);
  
#endif
