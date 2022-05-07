/*****************************************
File  : i2c_config.c
Autor : strefapic.blogspot.com
MCU   : STM32G071KBT6
IDE   : SEGGER Embedded Studio
******************************************/

#include <stm32g071xx.h>
#include "i2c_config.h"


#include <stm32g071xx.h>
#include <assert.h>
#include "i2c_config.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "SemaphoreCreate.h"
//#define debug

void I2C1_MANAGER_Initialize(void) {

  I2C1->CR1 &= ~I2C_CR1_PE; // I2C2 OFF
  asm("nop");
  asm("nop");
  asm("nop");
  I2C1->CR1 |= I2C_CR1_ANFOFF; // Analog filter ON
  I2C1->TIMINGR = 0x00303D5B;  // get from STM32Cube, FCY - 16MHz
  I2C1->CR1 |= I2C_CR1_TCIE;   // Transfer Complete interrupt enable TCIE = 1
  I2C1->CR1 |= I2C_CR1_TXIE;   // Transmit (TXIS) interrupt enabled TXIE = 1
  I2C1->CR1 |= I2C_CR1_RXIE;   // Receive (RXNE) interrupt enabled RXIE = 1
  I2C1->CR1 |= I2C_CR1_STOPIE; // STOP (STOPF) interrupt enabled STOPIE = 1
  I2C1->CR1 |= I2C_CR1_PE;     // I2C2 ON
  asm("nop");
  asm("nop");
  asm("nop");
}

/*For MCP79410 and CAP1293*/
uint8_t I2C1_Read(uint8_t slaveAdress, uint8_t registerAdress) {

  uint8_t data;
  /* ochrona I2C1 za pomoc¹ Mutex */
  if (xSemaphoreTake(xMutexI2CReadGuard, 5 / portTICK_PERIOD_MS) == pdTRUE) { 
    while (I2C1->ISR & I2C_ISR_BUSY)
      ; // wait for I2C not busy

    I2C1->CR2 &= ~I2C_CR2_NBYTES;         // clear NBYTES
    I2C1->CR2 |= 1 << I2C_CR2_NBYTES_Pos; // set NBYTES = 1
    I2C1->CR2 &= ~I2C_CR2_AUTOEND;        // set AUTOEND = 0

    I2C1->CR2 &= ~I2C_CR2_SADD;                                 // clear SADD
    I2C1->CR2 |= ((uint32_t)(slaveAdress) << I2C_CR2_SADD_Pos); // set SADD = slaveAdress
    I2C1->TXDR = (uint32_t)registerAdress;                      // write to buf TXDR , registerAdress
    I2C1->CR2 &= ~I2C_CR2_RD_WRN;                               // Master requests a write transfer RD_WRN = 0
    I2C1->CR2 |= I2C_CR2_START;                                 // set START = 1

    while (!(I2C1->ISR & I2C_ISR_TC))
      ; // wait for transfer complete TC = 1

    /*RESTART*/
    I2C1->CR2 |= I2C_CR2_AUTOEND; // set AUTOEND = 1
    I2C1->CR2 |= I2C_CR2_RD_WRN;  // Master requests a read transfer RD_WRN = 1
    I2C1->CR2 |= I2C_CR2_START;   // set START = 1
    /*slaveAdress wpisany wczesniej w SADD jest sprzetowo ustawiany bit R/W = 1 i wysylany jest automatycznie po komendzie START*/
    while (!(I2C1->ISR & I2C_ISR_RXNE))
      ;                // wait for data to be received RXNE = 1
    data = I2C1->RXDR; // read receive bufer
    while (!(I2C1->ISR & I2C_ISR_STOPF))
      ;                          // wait for STOP complete STOPF = 1
    I2C1->ICR |= I2C_ICR_STOPCF; // clear flag for STOP event

#ifdef debug
    printf("data %d\n", data);
#endif
    xSemaphoreGive(xMutexI2CReadGuard); // oddaj token mutex
    return data;
  }
}

/*For MCP79410 and CAP1293 */
void I2C1_Write(uint8_t slaveAdress, uint8_t registerAdress, uint8_t data) {
  /* ochrona I2C1 za pomoc¹ Mutex */
  if (xSemaphoreTake(xMutexI2CWriteGuard, 5 / portTICK_PERIOD_MS) == pdTRUE) { 

    while (I2C1->ISR & I2C_ISR_BUSY)
      ; // wait for I2C not busy

    I2C1->CR2 &= ~I2C_CR2_NBYTES;         // clear NBYTES
    I2C1->CR2 |= 2 << I2C_CR2_NBYTES_Pos; // set NBYTES = 2

    I2C1->CR2 |= I2C_CR2_AUTOEND; // set AUTOEND = 1

    I2C1->CR2 &= ~I2C_CR2_SADD;                                 // clear SADD
    I2C1->CR2 |= ((uint32_t)(slaveAdress) << I2C_CR2_SADD_Pos); // set SADD = slaveAdress
    I2C1->TXDR = (uint32_t)registerAdress;                      // write to buf TXDR , registerAdress *****
    I2C1->CR2 &= ~I2C_CR2_RD_WRN;                               // Master requests a write transfer RD_WRN = 0
    I2C1->CR2 |= I2C_CR2_START;                                 // set START = 1

    while (!(I2C1->ISR & I2C_ISR_TXIS))
      ; // wait for data to be transmitted TXIS = 1

    I2C1->TXDR = (uint32_t)data; // write to buf TXDR , registerAdress

    while (!(I2C1->ISR & I2C_ISR_STOPF))
      ; // wait for STOP complete STOPF = 1

    I2C1->ICR |= I2C_ICR_STOPCF; // clear flag for STOP event

    xSemaphoreGive(xMutexI2CWriteGuard); // oddaj token mutex
  }
}