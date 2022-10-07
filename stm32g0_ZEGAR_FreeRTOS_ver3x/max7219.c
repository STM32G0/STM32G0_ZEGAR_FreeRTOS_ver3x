/*****************************************
File  : max7219.c
Autor : strefapic.blogspot.com
MCU   : STM32G071KBT6
IDE   : SEGGER Embedded Studio
******************************************/

#include <stm32g071xx.h>
#include <string.h>
#include "system_config.h"
#include "max7219.h"
#include "max7219_interface.h"
#include "ds18b20.h"


uint8_t Max7219SpiBuffer[MAX7219_DEVICES * 2];
uint8_t kropka_int_flag = 0 ;	

// wyslanie 2 bajtw do ukladu MAX7219
// 1 bajt (adress) - adres rejestru do ktrego bd wpisane dane
// 2 bajt (data) - dane do zapisania
void max7219_send(uint8_t adress, uint8_t data) {
  CS_SetLow(); // ustawienie stanu niskiego na linii CS
  SPI1_Transmit_2x8bit(adress, data);
  CS_SetHigh(); // ustawienie stanu wysokiego na linii CS (zatrzanicie danych w ukladzie zboczem narastajacym)
}

void max7219_SendToDevice(uint8_t DeviceNumber, uint8_t Adress, uint8_t Data) {
  uint8_t Offset = DeviceNumber * 2;
/* Device 0 - send NOP (0,0) and next send (adresRegister , data) */
/* Device 1 - send (adresRegister , data) and next send NOP (0,0) */

  memset(Max7219SpiBuffer, 0x00, (MAX7219_DEVICES * 2)); // set NOP
  Max7219SpiBuffer[(MAX7219_DEVICES * 2) - Offset - 2] = Adress;
  Max7219SpiBuffer[(MAX7219_DEVICES * 2) - Offset - 1] = Data;
  CS_SetLow(); // ustawienie stanu niskiego na linii CS
  SPI1_Transmit_Buffer(Max7219SpiBuffer, (MAX7219_DEVICES * 2));
  CS_SetHigh(); // ustawienie stanu wysokiego na linii CS (zatrzanicie danych w ukladzie zboczem narastajacym)
}

// inicjalizacja ukladu MAX7219
void max7219_init(void) {
  /* Device 0*/
  max7219_SendToDevice(Device0, MAX7219_SCAN_LIMIT, (MAX7219_USE_DIGIT - 4)); // liczba obslugiwanych wyswietlaczy
  max7219_SendToDevice(Device0, MAX7219_INTENSITY, 11);                       // maksymalna jasnosc od zera 0 - 15
  max7219_SendToDevice(Device0, MAX7219_DECODE_MODE, MAX7219_USE_BCD_DECODE); // ustawienie trybu wyswietlania dla poszczeglnych wyswietlaczy - BCD
  max7219_SendToDevice(Device0, MAX7219_SHUTDOWN, MAX7219_NORMAL_OPPERATION); // wlaczenie ukladu (normal operation)
  max7219_SendToDevice(Device0, MAX7219_DISPLAY_TEST, 0);                     // Test OFF
  /* Device 1*/
  max7219_SendToDevice(Device1, MAX7219_SCAN_LIMIT, (MAX7219_USE_DIGIT - 2)); // liczba obslugiwanych wyswietlaczy
  max7219_SendToDevice(Device1, MAX7219_INTENSITY, 11);                       // maksymalna jasnosc od zera 0 - 15
  max7219_SendToDevice(Device1, MAX7219_DECODE_MODE, MAX7219_USE_BCD_DECODE); // ustawienie trybu wyswietlania dla poszczeglnych wyswietlaczy - BCD
  max7219_SendToDevice(Device1, MAX7219_SHUTDOWN, MAX7219_NORMAL_OPPERATION); // wlaczenie ukladu (normal operation)
  max7219_SendToDevice(Device1, MAX7219_DISPLAY_TEST, 0);                     // Test OFF
}

// czyszczenie zawartosci wszystkich wyswietlaczy LED

void max7219_clear(void) {
  uint8_t i, j;
  for (i = 0; i < (MAX7219_DEVICES); i++) {
    for (j = 0; j < 8; j++) {
      if ((MAX7219_USE_BCD_DECODE & (1 << j))) {
        max7219_SendToDevice(i, j, 0xF);
      } else {
        max7219_SendToDevice(i, j, 0);
      }
    }
  }
}

/* funkcja do ustawienia intensywnosci swiecenia */
/* dozwolone wartosci : 1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31 */
void max7219_intensity(uint8_t DeviceNumber, uint8_t intensity){

max7219_SendToDevice(DeviceNumber, MAX7219_INTENSITY, intensity);  
}

/* funkcje do współpracy z MCP79410 i wyswietlania czasu*/
void max7219_display_Minutes(uint8_t minutes){
/* display minutes*/
          max7219.SendToDevice(Device0, MAX7219_DIGIT0,  minutes & 0x0F);        // wyswietl cyfre jednosci
          max7219.SendToDevice(Device0, MAX7219_DIGIT1, (minutes >> 4) & 0x0F); // wyswietl cyfre dziesiatki
}

void max7219_display_Hour(uint8_t hour){
/* display hour*/
          max7219.SendToDevice(Device0, MAX7219_DIGIT2,  (hour & 0x0F) | kropka_int_flag);        // wyswietl cyfre jednosci plus kropka
          max7219.SendToDevice(Device0, MAX7219_DIGIT3, (hour >> 4) & 0x0F); // wyswietl cyfre dziesiatki
}

void max7219_clear_display_Minutes(void){
/* display minutes*/
          max7219.SendToDevice(Device0, MAX7219_DIGIT0, 0x0F);   // zgas cyfre jednosci 
          max7219.SendToDevice(Device0, MAX7219_DIGIT1, 0x0F);   // zgaś cyfre dziesiatki
}

void max7219_clear_display_Hour(void){
/* display hour*/
          max7219.SendToDevice(Device0, MAX7219_DIGIT2, 0x0F); // zgas cyfre jednosci
          max7219.SendToDevice(Device0, MAX7219_DIGIT3, 0x0F); // zgaś cyfre dziesiatki
}

/* funkcja do współpracy z DS18B20 i wyswietlania temperatury*/

void max7219_display_Temperature(temperatureDevice_t TemperatureDevice){
  /* Display Temperature All Device*/

  /* Wire1 and Wire2 */
  uint16_t cyfra_dziesiatki; //  variable to extract the digit for displaying the temperature at the decimal position
  uint16_t cyfra_jednosci;   //  variable to extract the digit for the temperature display at the unity position

  if (TemperatureDevice.DStemp_Calkowita >= 10 && TemperatureDevice.DStemp_Calkowita < 100) { //  digit in the tens position to display ? if yes then display , if no then display nothing

    /* decimal and unity digit for temperature displayed before decimal point */
    cyfra_dziesiatki = (uint16_t)(TemperatureDevice.DStemp_Calkowita / 10) % 10; // calculation of the decimal digit
    cyfra_jednosci = ((uint16_t)(TemperatureDevice.DStemp_Calkowita)) % 10;      // calculation of the unity digit
    if (TemperatureDevice.deviceID == Wire1) {
      max7219.SendToDevice(Device1, MAX7219_DIGIT5, cyfra_dziesiatki);
      max7219.SendToDevice(Device1, MAX7219_DIGIT4, cyfra_jednosci | kropka); // display a number and a dot
    }
    if (TemperatureDevice.deviceID == Wire2) {
      max7219.SendToDevice(Device1, MAX7219_DIGIT2, cyfra_dziesiatki);
      max7219.SendToDevice(Device1, MAX7219_DIGIT1, cyfra_jednosci | kropka); // display a number and a dot
    }
  }

  if (TemperatureDevice.DStemp_Calkowita < 10) //  number in the units position to display ? if yes - then display , if no - display nothing
  {
    cyfra_jednosci = ((uint16_t)TemperatureDevice.DStemp_Calkowita) % 10; // wyliczenie cyfry jednosci
    /* Wire1 */
    if (TemperatureDevice.deviceID == Wire1) {
      max7219.SendToDevice(Device1, MAX7219_DIGIT4, cyfra_jednosci | kropka); // display the digit for the unity value and a dot
      max7219.SendToDevice(Device1, MAX7219_DIGIT3, 0xF);                     // Turn off the display in the decimal position
    }
    /* Wire2 */
    if (TemperatureDevice.deviceID == Wire2) {
      max7219.SendToDevice(Device1, MAX7219_DIGIT1, cyfra_jednosci | kropka); // display the digit for the unity value and a dot
      max7219.SendToDevice(Device1, MAX7219_DIGIT2, 0xF);                     // Turn off the display in the decimal position
    }
  }

  /* Temperature display after decimal point (one digit) */
  /* Wire1 */
  if (TemperatureDevice.deviceID == Wire1) {
    max7219.SendToDevice(Device1, MAX7219_DIGIT3, TemperatureDevice.DStemp_Ulamek);
  }
  /* Wire2 */
  if (TemperatureDevice.deviceID == Wire2) {
    max7219.SendToDevice(Device1, MAX7219_DIGIT0, TemperatureDevice.DStemp_Ulamek);
  }

   /* Temperature sign signaling */
  /* Wire1 */
  if (TemperatureDevice.deviceID == Wire1) {
  if(TemperatureDevice.DStemp_Znak){ //sign temperature minus ?
     	  LED2_SetHigh(); // LED for Wire1 ON
       } else
     	  LED2_SetLow(); // LED for Wire1 OFF
  }

  /* Wire2 */
    if (TemperatureDevice.deviceID == Wire2) {
    if(TemperatureDevice.DStemp_Znak){ //sign temperature minus ?
       	  LED1_SetHigh(); // LED for Wire2 ON
         } else
       	  LED1_SetLow(); // LED for Wire2 OFF
    }
}