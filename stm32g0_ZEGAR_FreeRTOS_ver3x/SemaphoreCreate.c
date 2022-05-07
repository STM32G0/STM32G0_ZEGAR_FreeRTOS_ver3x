/*****************************************
File  : SemaphoreCreate.c
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

/* Semaphore */
SemaphoreHandle_t xSemaphoreClockTask = NULL ;
/* Mutex */
SemaphoreHandle_t xMutexI2CWriteGuard = NULL;
SemaphoreHandle_t xMutexI2CReadGuard = NULL;

void SemaphoreCreate(void){

 /* Attempt to create a Semaphore. */
  xSemaphoreClockTask = xSemaphoreCreateBinary();
  assert(xSemaphoreClockTask != NULL); // assert create semaphore control
  xSemaphoreGive(xSemaphoreClockTask); // load the semaphore with a token
/* Attempt to create a Mutex. */
  xMutexI2CWriteGuard = xSemaphoreCreateMutex();
  assert(xMutexI2CWriteGuard != NULL); // assert create mutex control
  /* Attempt to create a Mutex. */
  xMutexI2CReadGuard = xSemaphoreCreateMutex();
  assert(xMutexI2CReadGuard != NULL); // assert create mutex control
}