/*****************************************
File  : QueueCreate.h
Autor : strefapic.blogspot.com
MCU   : STM32G071KBT6
IDE   : SEGGER Embedded Studio
******************************************/

extern QueueHandle_t xQueueClockTask;
extern QueueHandle_t xQueueTemperatureTaskWire;

typedef struct {
  uint8_t HOUR;
  uint8_t MIN;
  uint8_t SEC;
} time_t;

void QueueCreate(void);