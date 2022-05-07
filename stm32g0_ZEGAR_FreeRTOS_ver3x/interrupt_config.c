/*****************************************
File  : interrupt_config.c
Autor : strefapic.blogspot.com
MCU   : STM32G071KBT6
IDE   : SEGGER Embedded Studio
******************************************/

#include <stm32g071xx.h>
#include "interrupt_config.h"

void INTERRUPT_MANAGER_Initialize(void){
/* EXTI interrupt init*/
 NVIC_SetPriority(EXTI4_15_IRQn, 2);
 NVIC_EnableIRQ(EXTI4_15_IRQn);
 
}