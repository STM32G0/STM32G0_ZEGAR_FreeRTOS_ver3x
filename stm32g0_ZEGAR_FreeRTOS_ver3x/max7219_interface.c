/*****************************************
File  : max7219_interface.c
Autor : strefapic.blogspot.com
MCU   : STM32G071KBT6
IDE   : SEGGER Embedded Studio
******************************************/

#include "max7219_interface.h"
#include "max7219.h"

/*do wskaznikow przypisujemy funkcje*/
const max7219_interface_t max7219 = {
.InitAllDevice = max7219_init,
.ClearAllDevice = max7219_clear,
.SendAllDevice = max7219_send,
.SendToDevice = max7219_SendToDevice,
.Display_MIN = max7219_display_Minutes,
.Display_HOUR = max7219_display_Hour,
.ClearDisplay_MIN = max7219_clear_display_Minutes,
.ClearDisplay_HOUR = max7219_clear_display_Hour,
.Display_TemperatureAllDevice = max7219_display_Temperature,
.Set_Intensity = max7219_intensity,
};