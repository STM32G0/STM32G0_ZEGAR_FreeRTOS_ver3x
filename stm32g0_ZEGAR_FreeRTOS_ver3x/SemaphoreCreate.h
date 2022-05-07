/*****************************************
File  : SemaphoreCreate.h
Autor : strefapic.blogspot.com
MCU   : STM32G071KBT6
IDE   : SEGGER Embedded Studio
******************************************/

/* Semaphore */
extern SemaphoreHandle_t xSemaphoreClockTask ;
/* Mutex */
extern SemaphoreHandle_t xMutexI2CWriteGuard;
extern SemaphoreHandle_t xMutexI2CReadGuard;

void SemaphoreCreate(void);