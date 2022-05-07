/*****************************************
File  : QueueCreate.c
Autor : strefapic.blogspot.com
MCU   : STM32G071KBT6
IDE   : SEGGER Embedded Studio
******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stm32g071xx.h>
#include <stdbool.h>
//#define NDEBUG // activate if not use Assert control, before #include <assert>
#include <assert.h>
#include "system_config.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "QueueCreate.h"
#include "ds18b20.h"



QueueHandle_t xQueueClockTask = NULL;
QueueHandle_t xQueueTemperatureTaskWire = NULL;


void QueueCreate(void){

/* Attempt to create a queue. */
  xQueueClockTask = xQueueCreate(2, sizeof(time_t));
  assert(xQueueClockTask != NULL); // assert create queue control

  xQueueTemperatureTaskWire = xQueueCreate(8, sizeof(temperatureDevice_t));
  assert(xQueueTemperatureTaskWire != NULL); // assert create queue control
  
}