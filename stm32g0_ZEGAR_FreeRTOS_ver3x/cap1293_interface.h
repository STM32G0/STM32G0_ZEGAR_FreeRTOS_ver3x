/*****************************************
File  : cap1293_interface.h
Autor : strefapic.blogspot.com
MCU   : STM32G071KBT6
IDE   : SEGGER Embedded Studio
******************************************/

#include <stdint.h>
#include "cap1293.h"

#ifndef CAP1293_INTERFACE_H_
#define CAP1293_INTERFACE_H_


typedef  struct {
/*deklaracja wskaznikow na funkcje*/
void (*WriteRegister)(uint8_t registerAdress, uint8_t data);
uint8_t (*ReadRegister)(uint8_t registerAdress);
void (*Init)(void);

} cap1293_interface_t ;

extern const cap1293_interface_t cap1293 ;

#endif /*CAP1293_INTERFACE_H*/