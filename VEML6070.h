#ifndef VEML6070_h
#define VEML6070_h

/* VEML6070_t3 Basic Example Code
 by: Kris Winer
 date: May 23, 2015
 license: Beerware - Use this code however you'd like. If you 
 find it useful you can buy me a beer some time.
 
 Demonstrate basic VEML6070 functionality including parameterizing the register addresses, initializing the sensor, 
 getting properly scaled UV intensity and index data out. Sketch runs on the 3.3 V Teensy 3.1.
 
 VEML6070 is an advanced ultraviolet (UV) light sensor with I2C protocol interface
 and designed by the CMOS process. It is easily operated via a simple I2C command. The active 
 acknowledge (ACK) feature with threshold windows setting allows the UV sensor to send out a UVI alert message. 
 Under a strong solar UVI condition, the smart ACK signal can be easily implemented by the software programming.
 VEML6070 incorporates a photodiode, amplifiers, and analog / digital circuits into a single chip. VEML6070’s adoption of FiltronTM
 UV technology provides the best spectral sensitivity to cover UV spectrum sensing. 
 It has an excellent temperature compensation and a robust refresh rate setting that does not use an external RC low pass filter. 
 VEML6070 has linear sensitivity to solar UV light and is easily adjusted by an external resistor. Software shutdown 
 mode is provided, which reduces power consumption to be less than 1 µA. VEML6070’s operating voltage ranges from 
 2.7 V to 5.5 V.

 SDA and SCL  have external pull-up resistors (to 3.3V).
 2K2 resistors are on the VEML6070 breakout board.
 
 Hardware setup:
 VEML6070 Breakout ------ Teensy 3.1
 VDD ---------------------- 3.3V
 SDA ----------------------- pin 17 or 18
 SCL ----------------------- pin 16 or 19
 GND ---------------------- GND
  */
//#include "Wire.h"   
#include <i2c_t3.h>
#include <SPI.h>

// See also VEML6070 data sheet:http://www.vishay.com/docs/84277/veml6070.pdf
//

////////////////////////////
// VEML6070 Registers/addresses //
////////////////////////////
#define  VEML6070_ADDR_ARA	      0x19 >> 1 // shift by one to get correct register addresses
#define  VEML6070_ADDR_CMD		    0x70 >> 1
#define  VEML6070_ADDR_DATA_LSB		0x71 >> 1
#define  VEML6070_ADDR_DATA_MSB		0x73 >> 1

enum IT {  // set of allowable sample rates
  IT_0_5 = 0,
  IT_1,
  IT_2,
  IT_4
};

// VEML6070 command register bits
#define VEML6070_CMD_DISABLE             0x01
#define VEML6070_CMD_WDM                 0x02

#ifndef SerialDebug
#define SerialDebug true  // set to true to get Serial output for debugging
#endif

//Integration Time with 270 kOhm set resistor
#define IT_1_2 0x00 //1/2T  90 ms
#define IT_1   0x01 //1T   180 ms
#define IT_2   0x02 //2T   360 ms
#define IT_4   0x03 //4T   720 ms

class VEML6070
{
	public:
	VEML6070(i2c_pins pins, i2c_pullup pullup, i2c_rate rate);
	void init();
	uint16_t getUVdata();
	void enableVEML6070();
	uint16_t convert_to_risk_level(uint16_t uvs_step);
	void I2Cscan();
	private:
	// Specify VEML6070 Integration time
	uint8_t IT = IT_1;
	uint16_t count = 0;
};
#endif
