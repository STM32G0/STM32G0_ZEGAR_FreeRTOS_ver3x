/*****************************************
File  : clock_config.c
Autor : strefapic.blogspot.com
MCU   : STM32G071KBT6
IDE   : SEGGER Embedded Studio
******************************************/

#include <stm32g071xx.h>
#include "pin_config.h"

void PIN_MANAGER_Initialize(void){
/************ MCP79410 and CAP1293 *******************/
/********** PA9 and PB9 set for I2C2 *****************/
/*set Alternate fuction mode (0b10)*/
/*for PA9*/
GPIOA->MODER |= GPIO_MODER_MODE9_1 ; 
GPIOA->MODER &= ~(GPIO_MODER_MODE9_0); 
/*for PB9*/
GPIOB->MODER |= GPIO_MODER_MODE9_1 ; 
GPIOB->MODER &= ~(GPIO_MODER_MODE9_0); 
/*set Open Drain*/
GPIOA->OTYPER |= GPIO_OTYPER_OT9 ;
GPIOB->OTYPER |= GPIO_OTYPER_OT9 ;
/*set Pull-Up (0b01)*/
/*for PA9*/
GPIOA->PUPDR |= GPIO_PUPDR_PUPD9_0 ;
GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD9_1);
/*for PB9*/
GPIOB->PUPDR |= GPIO_PUPDR_PUPD9_0 ;
GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD9_1);
/*set low speed (0b01)*/
/*for PA9*/
GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED9_0 ;
GPIOA->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED9_1);
/*for PB9*/
GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED9_0 ;
GPIOB->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED9_1);
/*set for I2C (0b0110)*/
/*for PA9*/
GPIOA->AFR[1] &= ~(GPIO_AFRH_AFSEL9) ; // clear
/*for PB9*/
GPIOB->AFR[1] &= ~(GPIO_AFRH_AFSEL9) ; // clear
/*for PA9*/
GPIOA->AFR[1] |= (GPIO_AFRH_AFSEL9_1 | GPIO_AFRH_AFSEL9_2) ; //set
/*for PB9*/
GPIOB->AFR[1] |= (GPIO_AFRH_AFSEL9_1 | GPIO_AFRH_AFSEL9_2) ; //set

/********** PC15 set Out for LED2 **********************/
GPIOC->MODER &= ~GPIO_MODER_MODE15_1; //MODE15 -> 0b01
/********** PC14 set Out for LED1 **********************/
GPIOC->MODER &= ~GPIO_MODER_MODE14_1; //MODE14 -> 0b01


/********** PA3 set Out for CS MAX7219 **********************/
GPIOA->MODER &= ~GPIO_MODER_MODE3_1; //MODE3 -> 0b01

/********* MCP79410 for pin MFP *********/
/********** PB5 set for EXTI ************/
/*set Input (0b00)*/
GPIOB->MODER &= ~(GPIO_MODER_MODE5_0 | GPIO_MODER_MODE5_1); 
/*set low speed (0b01)*/
GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED5_0 ;
GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED5_1 ;
/*set Pull-Up (0b01)*/
GPIOB->PUPDR |= GPIO_PUPDR_PUPD5_0 ;
GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD5_1;
/*set EXTI for PB5*/
EXTI->EXTICR[1] |= EXTI_EXTICR2_EXTI5_0 ; // Port PB - 0x01
/*set EXTI Falling triger for PB5*/
EXTI->FTSR1 |= EXTI_FTSR1_FT5 ;
/*set EXTI Interrupt no-masked for PB5*/
EXTI->IMR1 |= EXTI_IMR1_IM5 ;

/************************* MAX7219 *****************************/
/************ PA1 (SCK) and PA2 (MOSI) set for SPI1 ************/
/*set Alternate fuction mode (0b10)*/
/*Pin PA1*/
GPIOA->MODER &= ~GPIO_MODER_MODE1_0;
/*Pin PA2*/
GPIOA->MODER &= ~GPIO_MODER_MODE2_0;
/*set low speed (0b01)*/
GPIOA->OSPEEDR |= (GPIO_OSPEEDR_OSPEED1_0 | GPIO_OSPEEDR_OSPEED2_0) ;
/*GPIO alternate function low register (GPIOA_AFRL for AFSEL1 and AFSEL2 set default 0b0000)*/

/********** PA3 set Out for CS MAX7219 **********************/
GPIOA->MODER &= ~GPIO_MODER_MODE3_1; //MODE3 -> 0b01

/********* CAP1293 for pin ALERT *********/
/********** PB4 set for EXTI ************/
/*set Input (0b00)*/
GPIOB->MODER &= ~(GPIO_MODER_MODE4_0 | GPIO_MODER_MODE4_1); 
/*set low speed (0b01)*/
GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED4_0 ;
GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED4_1 ;
/*set Pull-Up (0b01)*/
GPIOB->PUPDR |= GPIO_PUPDR_PUPD4_0 ;
GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD4_1;
/*set EXTI for PB4*/
EXTI->EXTICR[1] |= EXTI_EXTICR2_EXTI4_0 ; // Port PB - 0x01
/*set EXTI Falling triger for PB4*/
EXTI->FTSR1 |= EXTI_FTSR1_FT4 ;
/*set EXTI Interrupt no-masked for PB4*/
EXTI->IMR1 |= EXTI_IMR1_IM4 ;

/********** PA5 set Out for DS18B20 WIRE2 **********************/
GPIOA->MODER |=  GPIO_MODER_MODE5_0; //MODE5 -> 0b01
GPIOA->MODER &= ~GPIO_MODER_MODE5_1; //MODE5 -> 0b01

/* PA5 set High */
GPIOA->BSRR |= GPIO_BSRR_BS5;

/********** PA0 set Out for DS18B20 WIRE1 **********************/
GPIOA->MODER |=  GPIO_MODER_MODE0_0; //MODE0 -> 0b01
GPIOA->MODER &= ~GPIO_MODER_MODE0_1; //MODE0 -> 0b01

/* PA0 set High */
GPIOA->BSRR |= GPIO_BSRR_BS0;

/********* PA7 config for OptoResistor *********/
GPIOA->MODER |=  ((GPIO_MODER_MODE7_0) | (GPIO_MODER_MODE7_1)); //MODE7 -> 0b11

}

