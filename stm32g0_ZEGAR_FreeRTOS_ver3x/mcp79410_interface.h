/*****************************************
File  : mcp79410_interface.h
Autor : strefapic.blogspot.com
MCU   : STM32G071KBT6
IDE   : SEGGER Embedded Studio
******************************************/

#include <stdint.h>
#include "mcp79410.h"


#ifndef MCP79410_INTERFACE_H_
#define MCP79410_INTERFACE_H_


typedef  struct {
/*deklaracja wskaznikow na funkcje*/
void (*WriteRegisterRTCC)(uint8_t registerAdress, uint8_t data) ;
void (*WriteRegisterEEPROM)(uint8_t registerAdress, uint8_t data);
uint8_t (*ReadRegisterRTCC)(uint8_t registerAdress);
void (*InitRTCC)(void);
uint8_t (*getTime_YEAR)(void);
uint8_t (*getTime_MONTH)(void);
uint8_t (*getTime_DAY)(void);
uint8_t (*getTime_HOUR)(void);
uint8_t (*getTime_MIN)(void);
uint8_t (*getTime_SEC)(void);
void (*setTime_MIN)(uint8_t minute);
void (*setTime_HOUR)(uint8_t hour);

} mcp79410_interface_t ;

extern const mcp79410_interface_t mcp79410 ;

#endif /*MCP79410_INTERFACE_H*/