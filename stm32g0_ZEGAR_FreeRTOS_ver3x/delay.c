/*****************************************
File  : delay.c
Autor : strefapic.blogspot.com
MCU   : STM32G071KBT6
IDE   : SEGGER Embedded Studio
******************************************/

#include <stm32g071xx.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "delay.h"

void delay_us(uint16_t us){
  TIM6->CNT = 0;
 while (TIM6->CNT < us);
}

void delay_ms(uint16_t ms)
{
	int i;
	for (i=0; i < ms; i++){
		delay_us(1000);
	}
}