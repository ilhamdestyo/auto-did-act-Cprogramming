// include libraries
#include "io.h"
#include "myI2C.h"

void I2C_Init(void)
{
  // Rumus fclk:
  // fclk = (FCPU)/(16+2*TWBR*4^Prescaler)
  // --------------------------------------------- 
  // Rumus kalkulasi TWBR:
  // TWBR = {(FCPU/fclk) - 16 } / (2*4^Prescaler)
  // +++++++++++++++++++++++++++++++++++++++++++++
  // @param1 value of TWBR, 
  //    fclk = 400 kHz; TWBR = 3
  //    fclk = 100 kHz; TWBR = 20
  // @param2 value of Prescaler = 1
  I2C_FREQ(2,1);
}

//I2C master start
char I2C_MT_Start(void)
{
  // null status flag
  I2C_TWSR &= ~0xA8;
  // START
  // ----------------------------------------------
  // request for bus
  I2C_START();
  // wait till flag set
  I2C_WAIT_TILL_TWINT_IS_SET();
  // test if start or repeated start acknowledged
  if ((I2C_STATUS != I2C_START_ACK) && (I2C_STATUS != I2C_REP_START_ACK)) {
    // return status
    return I2C_STATUS;
  }
  // success
  return SUCCESS;
}

//Cek untuk SLA+W transmitted
char I2C_MT_Send_SLAW(char address)
{
  // SLA+W
  // ----------------------------------------------
  I2C_TWDR = (address << 1);
  // enable
  I2C_ENABLE();
  // wait till flag set
  I2C_WAIT_TILL_TWINT_IS_SET();

  // find
  if (I2C_STATUS != I2C_MT_SLAW_ACK) {
    // return status
    return I2C_STATUS;
  }
  // return found device address
  return SUCCESS;
}

char I2C_MT_Send_Data(char data)
{
  // DATA
  // ----------------------------------------------
  I2C_TWDR = data;
  // enable
  I2C_ENABLE();
  // wait till flag set
  I2C_WAIT_TILL_TWINT_IS_SET();

  // find
  if (I2C_STATUS != I2C_MT_DATA_ACK) {
    // return status
    return I2C_STATUS;
  }
  // return found device address
  return SUCCESS;
}


char I2C_MR_Send_SLAR(char address)
{
  // SLA+R
  // ----------------------------------------------
  I2C_TWDR = (address << 1) | 0x01;
  // enable
  I2C_ENABLE();
  // wait till flag set
  I2C_WAIT_TILL_TWINT_IS_SET();

  // find
  if (I2C_STATUS != I2C_MR_SLAR_ACK) {
    // return status
    return I2C_STATUS;
  }
  // return found device address
  return SUCCESS;
}


void I2C_Stop(void)
{
  // End I2C
  // -------------------------------------------------
  // send stop sequence
  I2C_STOP();
  // wait for TWINT flag is set
//  I2C_WAIT_TILL_TWINT_IS_SET();
}
