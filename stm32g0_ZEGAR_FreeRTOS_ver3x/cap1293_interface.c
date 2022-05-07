/*****************************************
File  : cap1293_interface.c
Autor : strefapic.blogspot.com
MCU   : STM32G071KBT6
IDE   : SEGGER Embedded Studio
******************************************/

#include "cap1293_interface.h"
#include "cap1293.h"


/*do wskaznikow przypisujemy funkcje*/
const cap1293_interface_t cap1293 = {

.WriteRegister = i2c_cap1293_wr,
.ReadRegister = i2c_cap1293_rd,
.Init = i2c_cap1293_ini, 

};