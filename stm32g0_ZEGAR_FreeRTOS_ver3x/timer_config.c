/*****************************************
File  : timer_config.c
Autor : strefapic.blogspot.com
MCU   : STM32G071KBT6
IDE   : SEGGER Embedded Studio
******************************************/

#include <stm32g071xx.h>
#include "timer_config.h"

#define MCU_CLK 16000000    /* 16 MHz */
#define DELAY_TIM_FREQUENCY 1000000 /* = 1MHZ -> timer runs in microseconds */

/*TIM6 to Delay functionality*/
void TIMER6_MANAGER_Initialize(void){

/* Timer6 init */
TIM6->PSC = (MCU_CLK / DELAY_TIM_FREQUENCY) - 1;  // 16MHz/16 = 1 MHz ~~ 1 uS per tick counter
TIM6->ARR = 0x0FFF; 
TIM6->CR1 |= TIM_CR1_CEN; // Enable the Counter
while (!(TIM6->SR & TIM_SR_UIF));  // UIF: Update interrupt flag..  This bit is set by hardware when the registers are updated
}


