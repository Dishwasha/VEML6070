#ifndef VEML6070_cpp
#define VEML6070_cpp
#include<VEML6070.h>

//===================================================================================================================
//====== Set of useful function to access UV data
//===================================================================================================================

VEML6070::VEML6070(i2c_pins pins, i2c_pullup pullup, i2c_rate rate)
{
 // Setup for Master mode, pins 16/17, external pullups, 400kHz for Teensy 3.1
  Wire.begin(I2C_MASTER, 0x00, pins, pullup, rate);
  delay(4000);
  Serial.begin(38400);
}

void VEML6070::init()
{
  I2Cscan();
  
  enableVEML6070(); // initalize sensor
 
  delay(150);
}

uint16_t VEML6070::getUVdata()
{
  uint8_t msb=0, lsb=0;

  Wire.requestFrom(VEML6070_ADDR_DATA_MSB, 1); //MSB
  delay(100);
  if(Wire.available())
    msb = Wire.read();

  Wire.requestFrom(VEML6070_ADDR_DATA_LSB, 1); //LSB
  delay(100);
  if(Wire.available())
    lsb = Wire.read();

  return ((uint16_t) msb<<8) | lsb;
}

void VEML6070::enableVEML6070()
{
  Wire.beginTransmission(VEML6070_ADDR_CMD);
  Wire.write((IT<<2) | VEML6070_CMD_WDM); // Bit 1 must be 1, bit 0 is 0 for run and 1 for shutdown
  Wire.endTransmission();
}

uint16_t VEML6070::convert_to_risk_level(uint16_t uvs_step)
{
uint16_t risk_level_mapping_table[4] = {2241, 4482, 5976, 8217};
uint16_t i;
for (i = 0; i < 4; i++)
{
if (uvs_step <= risk_level_mapping_table[i])
{
break;
}
}
return i;
}

// I2C scan function

void VEML6070::I2Cscan()
{
// scan for i2c devices
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknow error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
    
}

#endif