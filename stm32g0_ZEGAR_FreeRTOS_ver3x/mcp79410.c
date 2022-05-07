/*****************************************
File  : mcp79410.c
Autor : strefapic.blogspot.com
MCU   : STM32G071KBT6
IDE   : SEGGER Embedded Studio
******************************************/
 #include <stdint.h>
 #include "mcp79410.h"
 #include "i2c_config.h"

//extern uint8_t err_flg  ;   // the error flag will be used in this file 
// konwersja liczby DEC na BCD
uint8_t dec2bcd(uint8_t dec) {
    return ((dec / 10)<<4) | (dec % 10);
}

// konwersja liczby BCD na DEC
uint8_t bcd2dec(uint8_t bcd) {
    return ((((bcd) >> 4) & 0x0F) * 10) + ((bcd) & 0x0F);
    }
//..............................................................................
// The below function writes a data byte in the I2C RTCC
//..............................................................................

void i2c_rtcc_wr(uint8_t registerAdress, uint8_t data){ // writes a data byte to the I2C RTCC   
uint8_t slaveAdress = ADDR_RTCC_WRITE;
I2C1_Write(slaveAdress, registerAdress, data);
}
//..............................................................................
// The below function writes a data byte in the I2C RTCC
//..............................................................................

void i2c_eeprom_wr(uint8_t registerAdress, uint8_t data){ // writes a data byte to the I2C EEPROM   
uint8_t slaveAdress = ADDR_EEPROM_WRITE ;
I2C1_Write(slaveAdress, registerAdress, data);
}
//..............................................................................
// The below function reads a data byte from the I2C RTCC
//..............................................................................

uint8_t i2c_rtcc_rd(uint8_t registerAdress){ // read a data byte from the I2C RTCC   
uint8_t slaveAdress = ADDR_RTCC_WRITE;
return I2C1_Read(slaveAdress, registerAdress);
}
//..............................................................................
// The below function initializes the I2C RTCC
//..............................................................................

void i2c_rtcc_ini(void){             // initialization of the I2C RTCC: 
uint8_t day = 0, sec = 0;
i2c_rtcc_wr(ADDR_CTRL,0xC0);         // square wave on MFP, no alarms, MFP = 1Hz
/*enable VBAT*/
day = i2c_rtcc_rd(ADDR_DAY);
i2c_rtcc_wr(ADDR_DAY,day | VBATEN);  // enable the battery back-up
/*Set Time*/
/* nie uzywamy YEAR, MNTH , DATE i nie ustawiamy tego !!! */
//i2c_rtcc_wr(ADDR_YEAR,0x22);         // initialize YEAR  register : (20)22           
//i2c_rtcc_wr(ADDR_MNTH,0x02);         // initialize MONTH register : luty 
//i2c_rtcc_wr(ADDR_DATE,0x16);         // initialize DATE  register : date =  
/* ustawiamy HOUR , MIN i zerujemy sekundy */
//i2c_rtcc_wr(ADDR_HOUR,dec2bcd(13));    // initialize HOUR  register : hour = 13  
//i2c_rtcc_wr(ADDR_MIN,dec2bcd(34));     // initialize MIN   register : min  = 34  
sec = i2c_rtcc_rd(ADDR_DAY);             //read SEC register
i2c_rtcc_wr(ADDR_SEC,sec|START_32KHZ);   // start the 32khz oscillator SEC = 00 + ST bit = 1
}   

//..............................................................................
// The below function set time
//..............................................................................

void set_MIN(uint8_t minute){
i2c_rtcc_wr(ADDR_MIN,dec2bcd(minute)); 
}

void set_HOUR(uint8_t hour){
i2c_rtcc_wr(ADDR_HOUR,dec2bcd(hour)); 
}

/*****************************************************************************
                    Get time MCP79410 in BCD code
 *****************************************************************************/
uint8_t get_YEAR(void) {
uint8_t yr = 0;   
yr  = i2c_rtcc_rd(ADDR_YEAR)  ;  /*read YEAR*/        
return yr;           
}
    
uint8_t get_MONTH(void) { 
uint8_t mon = 0;  
mon = i2c_rtcc_rd(ADDR_MNTH)  ;  /*read MONTH*/ 
return mon;
}

uint8_t get_DAY(void) {   
uint8_t day = 0;
day = i2c_rtcc_rd(ADDR_DATE)  ;  /*read DATE*/ 
return day;
}

uint8_t get_HOUR(void) {
uint8_t hr = 0;       
hr  = i2c_rtcc_rd(ADDR_HOUR)  ;  /*read HOUR*/
return  hr ;
}

uint8_t get_MIN(void) {   
uint8_t min = 0;   
min = i2c_rtcc_rd(ADDR_MIN)   ;  /*read MIN*/
return min;
} 

uint8_t get_SEC(void) { 
uint8_t sec = 0;   
sec = i2c_rtcc_rd(ADDR_SEC)   ;  /*read SEC*/
return sec;
}

