/*****************************************
File  : pin_config.h
Autor : strefapic.blogspot.com
MCU   : STM32G071KBT6
IDE   : SEGGER Embedded Studio
******************************************/

#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

void PIN_MANAGER_Initialize(void);
/* definitions for led on PC15 */
#define LED2_SetHigh()           (GPIOC->BSRR |= GPIO_BSRR_BS15) 
#define LED2_SetLow()            (GPIOC->BSRR |= GPIO_BSRR_BR15) 
#define LED2_Toggle()            ((GPIOC->ODR & GPIO_ODR_OD15)  ? (GPIOC->BSRR |= GPIO_BSRR_BR15) : (GPIOC->BSRR |= GPIO_BSRR_BS15))

/* definitions for led on PC14 */
#define LED1_SetHigh()           (GPIOC->BSRR |= GPIO_BSRR_BS14) 
#define LED1_SetLow()            (GPIOC->BSRR |= GPIO_BSRR_BR14) 
#define LED1_Toggle()            ((GPIOC->ODR & GPIO_ODR_OD14)  ? (GPIOC->BSRR |= GPIO_BSRR_BR14) : (GPIOC->BSRR |= GPIO_BSRR_BS14))

/* definitions for CS (MAX7219) on PA3 */
#define CS_SetHigh()            (GPIOA->BSRR |= GPIO_BSRR_BS3) 
#define CS_SetLow()             (GPIOA->BSRR |= GPIO_BSRR_BR3) 

#define BUZZER_ON()             (GPIOB->BSRR |= GPIO_BSRR_BS3)
#define BUZZER_OFF()            (GPIOB->BSRR |= GPIO_BSRR_BR3)
#define BUZZER_Toggle()         ((GPIOB->ODR & GPIO_ODR_OD3)  ? (GPIOB->BSRR |= GPIO_BSRR_BR3) : (GPIOB->BSRR |= GPIO_BSRR_BS3))



#endif /*PIN_CONFIG_H*/