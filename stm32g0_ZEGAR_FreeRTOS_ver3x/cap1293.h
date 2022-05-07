/*****************************************
File  : cap1293.h
Autor : strefapic.blogspot.com
MCU   : STM32G071KBT6
IDE   : SEGGER Embedded Studio
******************************************/


#ifndef CAP1293_H
#define	CAP1293_H

uint8_t i2c_cap1293_rd(uint8_t registerAdress); 
void i2c_cap1293_wr(uint8_t registerAdress, uint8_t data);
void i2c_cap1293_ini(void);

#define CAP1293_ADDR_write              0x50 		//default address for all CAP1293 chips  - '0101 0000' write, '0101 0001' read
#define CAP1293_ADDR_read               0x51 		//default address for all CAP1293 chips  - '0101 0000' write, '0101 0001' read
#define CAP1293_ADDR                    0x50 		//default address for all CAP1293 chips  - '0101 0000' write, '0101 0001' read

/* Register set in hexadecimal order */
#define CAP1293_MAIN                    0x00      	//Main Control
#define CAP1293_GENSTAT                 0x02		//General Status
#define CAP1293_SENSTATUS               0x03		//Sensor Input Status (where touches on the inputs are stored)
#define CAP1293_NOISEFLAG               0x0A		//Noise Flag Status
#define CAP1293_SENSINPUTDELTACOUNT1    0X10		//Sensor Input 1 Delta Count
#define CAP1293_SENSINPUTDELTACOUNT2    0X11		//Sensor Input 2 Delta Count
#define CAP1293_SENSINPUTDELTACOUNT3    0X12		//Sensor Input 3 Delta Count

#define CAP1293_SENSITIVITY             0x1F		//Sensitivity Control
#define CAP1293_CONFIG1                 0x20		//Configuration 1 (General) (Configuration 2 is 0x44)	
#define CAP1293_SENSINPUTENABLE         0x21		//Sensor Input Enable
#define CAP1293_SENSINPUTCONFIG1        0x22		//Sensor Input Configuration 1
#define CAP1293_SENSINPUTCONFIG2        0x23		//Sensor Input Configuration 2
#define CAP1293_AVGSAMPCONFIG           0x24		//Averaging and Sampling Configuration
#define CAP1293_CALIBRATE               0x26		//Calibration Activate and Status
#define CAP1293_INTENABLE               0x27		//Interrupt Enable
#define CAP1293_RPTRATEENABLE           0x28		//Repeat Rate Enable
#define CAP1293_SGENABLE                0x29		//Signal Guard Enable
#define CAP1293_MTCONFIG                0x2A		//Multiple Touch Configuration
#define CAP1293_MTPATTERNCONFIG         0x2B		//Multiple Touch Pattern Configuration
#define CAP1293_MTPATTERN               0x2D		//Multiple Touch Pattern
#define CAP1293_BASECOUNTOUTOFLIMIT     0x2E		//Base Count Out of Limit
#define CAP1293_RECALCONFIG             0x2F		//Recalibration Configuration
#define CAP1293_SENSINPUTTHRES1         0x30		//Sensor Input 1 Threshold
#define CAP1293_SENSINPUTTHRES2         0x31		//Sensor Input 2 Threshold
#define CAP1293_SENSINPUTTHRES3         0x32		//Sensor Input 3 Threshold

#define CAP1293_SENSINPUTNOISTHRES      0x38		//Sensor Input Noise Threshold
//Standby configuration registers
#define CAP1293_STANDBYCHNL             0x40		//Standby Channel
#define CAP1293_STANDBYCFG              0x41		//Standby Configuration
#define CAP1293_STANDBYSENS             0x42		//Standby Sensitivity
#define CAP1293_STANDBYTHRES            0x43		//Standby Threshold
#define CAP1293_CONFIG2                 0x44		//Configuration 2 (Configuration 1 is 0x20)
//Base count registers
#define CAP1293_SENSINPUTBASECOUNT1     0x50		//Sensor Input 1 Base Count
#define CAP1293_SENSINPUTBASECOUNT2     0x51		//Sensor Input 2 Base Count
#define CAP1293_SENSINPUTBASECOUNT3     0x52		//Sensor Input 3 Base Count

//Power button registers
#define CAP1293_PWRBT                   0x60		//Power Button
#define CAP1293_PWRBTCONFIG             0x61		//Power Button Configuration
//Calibration sensitivity configuration registers
#define CAP1293_CALIBSENSCONFIG         0x80		//Calibration Sensitivity Configuration

//Calibration registers
#define CAP1293_SENSINPUTCALIB1         0xB1		//Sensor Input 1 Calibration
#define CAP1293_SENSINPUTCALIB2         0xB2		//Sensor Input 2 Calibration
#define CAP1293_SENSINPUTCALIB3         0xB3		//Sensor Input 3 Calibration

#define CAP1293_SENSINPUTCALIBLSB1      0xB9		//Sensor Input Calibration LSB 1

//ID registers
#define CAP1293_PRODID                  0xFD		//Product ID (default 0x69)
#define CAP1293_MANUID                  0xFE		//Manufacturer ID (default 0x5D)
#define CAP1293_REV                     0xFF		//Revision

//..bits to set
#define CAP1293_MAIN_INT                0x01  		//Interrupt bit (default 0)
#define CAP1293_MAIN_COMBO              0x02		//Combo mode bit  (default 0)
#define CAP1293_MAIN_CGAIN0             0x04		//Combo mode gain setting bit 1 (default 0)
#define CAP1293_MAIN_CGAIN1             0x08		//Combo mode gain setting bit 2 (default 0)
#define CAP1293_MAIN_DSLEEP             0x10		//Deep sleep mode bit (default 0)
#define CAP1293_MAIN_STBY               0x20		//Standby mode bit
#define CAP1293_MAIN_GAIN0              0x40		//Active mode gain setting bit 1 (default 0)
#define CAP1293_MAIN_GAIN1              0x80		//Active mode gain setting bit 2 (default 0)
#define CAP1293_GENSTAT_ACALFAIL        0x20		//Calibration failure bit
#define CAP1293_CONFIG1_TIMEOUT         0x80		//Timeout config bit (default 0)
#define CAP1293_CONFIG1_DISDIGNOISE     0x20		//Disable digital noise threshold (default 1 (disabled))
#define CAP1293_CONFIG1_DISANANOISE     0x10		//Disable analog noise threshold (default 0 (enabled))
#define CAP1293_CONFIG1_MAXDUREN        0x08		//Enable Max duration recalibration
#define CAP1293_CONFIG2_BCOUTRECAL      0x40		//Base count out-of-limit recalibration bit (default 1)	I THINK I SHOULD TURN THIS OFF FOR MOST USERS (BARE CONTACTS CAUSE OOL)
#define CAP1293_CONFIG2_BLKPWRCONT      0x20		//Disable power control while sensing (default 0)
#define CAP1293_CS1_DOWN                0x01
#define CAP1293_CS2_UP                  0x02
#define CAP1293_CS3_SELECT              0x04



#endif