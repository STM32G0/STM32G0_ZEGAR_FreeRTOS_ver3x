/*****************************************
File  : delay.h
Autor : strefapic.blogspot.com
MCU   : STM32G071KBT6
IDE   : SEGGER Embedded Studio
******************************************/

#include <stm32g071xx.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void delay_us(uint16_t us);
void delay_ms(uint16_t ms);
