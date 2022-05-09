/*****************************************
File  : cap1293.c
Autor : strefapic.blogspot.com
MCU   : STM32G071KBT6
IDE   : SEGGER Embedded Studio
******************************************/

#include <stm32g071xx.h>
#include "system_config.h"
#include "cap1293.h"

//..............................................................................
// The below function writes a data byte in the I2C CAP1293
//..............................................................................

void i2c_cap1293_wr(uint8_t registerAdress, uint8_t data) { // writes a data byte to the I2C CAP1293

  uint8_t slaveAdress = CAP1293_ADDR;
  I2C1_Write(slaveAdress, registerAdress, data);
}
//..............................................................................
// The below function reads a data byte from the I2C CAP1293
//..............................................................................

uint8_t i2c_cap1293_rd(uint8_t registerAdress) { // read a data byte from the I2C CAP1293

  uint8_t slaveAdress = CAP1293_ADDR;
  return I2C1_Read(slaveAdress, registerAdress);
}

//..............................................................................
// The below function initializes the I2C CAP1293
//..............................................................................

void i2c_cap1293_ini(void) { // initialization of the I2C RTCC:

  i2c_cap1293_wr(CAP1293_INTENABLE, 0b00000111); //Enable interrupt on CS1,CS2,CS3
  i2c_cap1293_wr(CAP1293_CONFIG2, 0b01000101); //Przerwanie jest generowane po wykryciu nacinicia i z czstotliwoci powtarzania, ale nie po wykryciu zwolnienia
  i2c_cap1293_wr(CAP1293_SENSITIVITY, 0b00101111); //Sensitive 32x
  i2c_cap1293_wr(CAP1293_RPTRATEENABLE, 0b00000011); //Repeat CS3-OFF , CS2-ON, CS1-ON
  i2c_cap1293_wr(CAP1293_MAIN, (i2c_cap1293_rd(CAP1293_MAIN) & ~CAP1293_MAIN_INT)); // clear main interrupt
}