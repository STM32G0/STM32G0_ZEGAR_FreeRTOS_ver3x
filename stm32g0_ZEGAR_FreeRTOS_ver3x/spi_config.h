/*****************************************
File  : spi_config.h
Autor : strefapic.blogspot.com
MCU   : STM32G071KBT6
IDE   : SEGGER Embedded Studio
******************************************/

void SPI1_MANAGER_Initialize(void);
void SPI2_MANAGER_Initialize(void);

void SPI1_Transmit_8bit(uint8_t data);
void SPI1_Transmit_Buffer(uint8_t *data, int size);
void SPI1_Transmit_2x8bit(uint8_t adress, uint8_t data);