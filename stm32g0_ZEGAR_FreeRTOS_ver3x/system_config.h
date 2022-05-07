/*****************************************
File  : system_config.h
Autor : strefapic.blogspot.com
MCU   : STM32G071KBT6
IDE   : SEGGER Embedded Studio
******************************************/

#ifndef SYSTEM_CONFIG_H
#define  SYSTEM_CONFIG_H

#include "clock_config.h"
#include "pin_config.h"
#include "system_config.h"
#include "i2c_config.h"
#include "spi_config.h"
#include "interrupt_config.h"
#include "timer_config.h"
#include "adc_config.h"

void SYSTEM_MANAGER_Initialize(void);

#endif /*SYSTEM_CONFIG_H*/