/*****************************************
File  : spi_config.c
Autor : strefapic.blogspot.com
MCU   : STM32G071KBT6
IDE   : SEGGER Embedded Studio
******************************************/

#include <stm32g071xx.h>
#include "spi_config.h"


void SPI1_MANAGER_Initialize(void){
/*SPI1 disable*/
SPI1->CR1 &= ~SPI_CR1_SPE ; 
asm("nop");
asm("nop");
asm("nop");
/* set prescaler FCY=16MHz / prescaler(4) = 4 MHz (0b001) */
SPI1->CR1 |= SPI_CR1_BR_0 ;
/* SET mode 0 (CPOL = 0 / CPHA = 0) to SPI1 */
SPI1->CR1 &= ~SPI_CR1_CPOL ;
SPI1->CR1 &= ~SPI_CR1_CPHA ;
/* Set Master */
SPI1->CR1 |= SPI_CR1_MSTR ; //set Master mode
/* Set NSS */
SPI1->CR1 |= SPI_CR1_SSM ; // software slave management
SPI1->CR1 |= SPI_CR1_SSI ; // set High on the input NSS (NSS - software mode)
/* Data size 8-bit DS = 0b0111*/
SPI1->CR2 |= (SPI_CR2_DS_0 | SPI_CR2_DS_1 | SPI_CR2_DS_2) ;
SPI1->CR2 |= SPI_CR2_FRXTH; // event is generated if the FIFO level is greater than or equal to 1/4 (8-bit)
/*enable SPI*/
SPI1->CR1 |= SPI_CR1_SPE ; //SPI1 enable
asm("nop");
asm("nop");
asm("nop");

}

void SPI2_MANAGER_Initialize(void){
/*write initialization code if you are using SPI2*/
}

/*only send, not used receive data*/
void SPI1_Transmit_8bit(uint8_t data){

while(!(SPI1->SR & SPI_SR_TXE)); //wait if TX buffor empty
*(volatile uint8_t *)&(SPI1->DR) = data;  //(you need also to force the compiler to use the correct size (in this case 8bits) 

/*During discontinuous communications, there is a 2 APB clock period delay between the
write operation to the SPI_DR register and BSY bit setting. As a consequence it is
mandatory to wait first until TXE is set and then until BSY is cleared after writing the last
data.
*/
	while (!(SPI1->SR & SPI_SR_TXE));  // wait for TXE bit to set -> This will indicate that the buffer is empty
	while (SPI1->SR & SPI_SR_BSY);  // wait for BSY bit to Reset -> This will indicate that SPI is not busy in communication	

/*Clear the Overrun flag by reading DR and SR*/
	uint8_t temp = SPI1->DR;
	temp = SPI1->SR;
        
}



/*only send, not used receive data*/
/*for MAX7219*/
void SPI1_Transmit_Buffer(uint8_t *data, int size){
	
	int i=0;
	while (i<size)
	{
	   while (!(SPI1->SR & SPI_SR_TXE));  // wait for TXE bit to set -> This will indicate that the buffer is empty
	   *(volatile uint8_t *)&(SPI1->DR) = data[i];  // load the data into the Data Register
	   i++;
	}	
	
/*During discontinuous communications, there is a 2 APB clock period delay between the
write operation to the SPI_DR register and BSY bit setting. As a consequence it is
mandatory to wait first until TXE is set and then until BSY is cleared after writing the last
data.
*/
	while (!(SPI1->SR & SPI_SR_TXE));  // wait for TXE bit to set -> This will indicate that the buffer is empty
	while (SPI1->SR & SPI_SR_BSY);  // wait for BSY bit to Reset -> This will indicate that SPI is not busy in communication	
	
	//  Clear the Overrun flag by reading DR and SR
	uint8_t temp = SPI1->DR;
	temp = SPI1->SR;
	
}




/*only send, not used receive data*/
/*for MAX7219*/
void SPI1_Transmit_2x8bit(uint8_t adress, uint8_t data){

while(!(SPI1->SR & SPI_SR_TXE)); //wait if TX buffor empty
SPI1->DR = ((data << 8) | adress);  // send 16-bit

/*During discontinuous communications, there is a 2 APB clock period delay between the
write operation to the SPI_DR register and BSY bit setting. As a consequence it is
mandatory to wait first until TXE is set and then until BSY is cleared after writing the last
data.
*/
	while (!(SPI1->SR & SPI_SR_TXE));  // wait for TXE bit to set -> This will indicate that the buffer is empty
	while (SPI1->SR & SPI_SR_BSY);     // wait for BSY bit to Reset -> This will indicate that SPI is not busy in communication	

/*Clear the Overrun flag by reading DR and SR*/
	uint8_t temp = SPI1->DR;
	temp = SPI1->SR;
        
}