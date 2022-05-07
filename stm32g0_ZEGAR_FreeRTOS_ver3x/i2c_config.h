/*****************************************
File  : i2c_config.h
Autor : strefapic.blogspot.com
MCU   : STM32G071KBT6
IDE   : SEGGER Embedded Studio
******************************************/

#ifndef I2C_CONFIG_H
#define  I2C_CONFIG_H
#include <stm32g071xx.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"


void I2C1_MANAGER_Initialize(void);
void I2C1_Write(uint8_t slaveAdress, uint8_t registerAdress, uint8_t data);
uint8_t I2C1_Read(uint8_t slaveAdress, uint8_t registerAdress);


#endif /*I2C_CONFIG_H*/