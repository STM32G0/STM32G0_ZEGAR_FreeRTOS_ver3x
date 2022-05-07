/*****************************************
File  : adc_config.c
Autor : strefapic.blogspot.com
MCU   : STM32G071KBT6
IDE   : SEGGER Embedded Studio
******************************************/

#include <stm32g071xx.h>
#include "adc_config.h"

void ADC_MANAGER_Initialize(void){

ADC1->CHSELR |= ADC_CHSELR_CHSEL7 ; // select ADC IN7 od the PA7 pin
ADC1->CFGR1 |= ADC_CFGR1_RES_0 ; // ADC data resolution set on 10 bit - 0b01
ADC1->CFGR1 |= ADC_CFGR1_CONT ; // set Continuous conversion mode
ADC1->CR |= ADC_CR_ADEN ; // enable ADC
ADC1->CR |= ADC_CR_ADSTART ; // start ADC
};