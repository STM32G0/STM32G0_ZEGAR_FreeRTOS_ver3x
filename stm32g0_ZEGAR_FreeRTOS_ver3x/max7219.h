/*****************************************
File  : max7219.h
Autor : strefapic.blogspot.com
MCU   : STM32G071KBT6
IDE   : SEGGER Embedded Studio
******************************************/

#ifndef MAX7219_H_
#define MAX7219_H_

#include "ds18b20.h"


#define MAX7219_USE_DIGIT	8  // okreslenie liczby wywietlaczy 7seg. sterowanych przy pomocy ukladu od 1 do 8 szt
#define MAX7219_DEVICES         2  // bo mam 2 x MAX7219
#define MAX7219_SHUTDOWN_MODE		0
#define MAX7219_NORMAL_OPPERATION	1

// -------------------------------------------------------------
//            adresy rejestrw ukladu MAX7219
// -------------------------------------------------------------
#define MAX7219_NOOP			0x00	// rejestr uywany przy kaskadowym poczeniu ukadw MAX7219 ze wspln lini CS
#define MAX7219_DIGIT0			0x01	// DIGIT 0..7 - rejestry danych kolejnych wyswietlaczy 7seg LED
#define MAX7219_DIGIT1			0x02
#define MAX7219_DIGIT2			0x03
#define MAX7219_DIGIT3			0x04
#define MAX7219_DIGIT4			0x05
#define MAX7219_DIGIT5			0x06
#define MAX7219_DIGIT6			0x07
#define MAX7219_DIGIT7			0x08
#define MAX7219_DECODE_MODE		0x09 	// bity 0..7 opisuj sposb dekodowania danych z rejestrw DIGIT0..7 (0 - standard dla 7-seg, 1 - BCD)
#define MAX7219_INTENSITY		0x0A	// regulacja intensywnoci swiecenia wyswietlaczy 1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31
#define MAX7219_SCAN_LIMIT		0x0B	// okrelenie liczby sterowanych ukladem wyswietlaczy (bity 0..2) - 0x00 - tylko 1 wys., 0x07 - wszystkie 8 wysw.
#define MAX7219_SHUTDOWN		0x0C	// tryb pracy wyswietlacza (0 - shutdown, 1 - normal)
#define MAX7219_DISPLAY_TEST            0x0F	// test wyswietlacza (zalaczenie wszystkich segmentw)

#define day 14   // wartosc intesywnosci swiecenia LED w dzien (stare 11)
#define night 7 // wartosc intesywnosci swiecenia LED w ciemnosci (stare 5)
// -------------------------------------------------------------
// ustawienie sposobu dekodowania danych na wyswietlaczu
//
// 0 na bicie reprezentujacym wywietlacz - zwykle kodowanie jak dla 7seg.
// 1 na bicie reprezentujacym wywietlacz - kodowanie BCD
//
// -------------------------------------------------------------
//#define MAX7219_USE_BCD_DECODE	0b11110111  // maska do ustawienia ktre bity sa dekodowane w BCD a ktre w segmentach - np.na pozycji 4-bitu chcemy wyswietla znak minus temperatury
//#define MAX7219_USE_BCD_DECODE_2	0b11110011  // maska - ustawiamy dekodowanie w segmentach na 3 i 4 bicie, np. jesli temp.mniejsza od 10 to chcemy znak minus wyswietla na 3-ciej pozycji
#define MAX7219_USE_BCD_DECODE          0b11111111  // maska do ustawienia ktre bity sa dekodowane w BCD a ktre w segmentach, na razie ustawiamy wszystkie  w BCD

#define kropka 	(1<<7) // ustawienie 7 bitu - wlaczenie znaku "kropka".
#define minus 1        // wyswietlenie znaku minus , na poyzcji wyswietlacza minus, dekodowanie znakw jako kod 7 segmentowy nie BCD jak w pozostalych

enum{Device0=0 , Device1}; // mamy dwa ukady MAX7219 w kaskadzie
extern uint8_t kropka_int_flag ; //uzyte w przerwaniu EXTI4_15_IRQHandler i w funkcji max7219_display_Hour() jako Heart Beat zegarka

void max7219_init(void);
void max7219_clear(void);
void max7219_send(uint8_t adress, uint8_t data) ;
void max7219_SendToDevice(uint8_t DeviceNumber, uint8_t Adress, uint8_t Data);
/* funkcje do wspolpracy z zegarkiem MCP79410) */
void max7219_display_Minutes(uint8_t minutes);
void max7219_display_Hour(uint8_t hour);
void max7219_clear_display_Minutes(void);
void max7219_clear_display_Hour(void);
void max7219_display_Temperature(temperatureDevice_t TemperatureDevice);
void max7219_intensity(uint8_t DeviceNumber, uint8_t intensity);

#endif /* MAX7219_H_ */
