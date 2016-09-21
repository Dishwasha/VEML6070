#include<VEML6070.h>

// Pin definitions
int intPin = 15;  // These can be changed, 2 and 3 are the Arduinos ext int pins
int myLed  = 13;                      
VEML6070* veml6070;
uint8_t ITime = 180;

void setup()
{
  veml6070 = new VEML6070(I2C_PINS_16_17, I2C_PULLUP_EXT, I2C_RATE_400);
  // Set up the interrupt pin, its set as active high, push-pull
  pinMode(myLed, OUTPUT);
  digitalWrite(myLed, HIGH);

  veml6070->init();
  
  digitalWrite(myLed, LOW);
}

void loop()
{  
  uint16_t steps = veml6070->getUVdata();
  Serial.print("UV raw counts = "); Serial.println(steps);
  Serial.print("UV radiant power = "); Serial.print((float)steps*5.0); Serial.println(" microWatts/cm*cm");

  uint8_t risk_level = veml6070->convert_to_risk_level(steps);
  if(risk_level == 0) Serial.println("UV risk level is low"); 
  if(risk_level == 1) Serial.println("UV risk level is moderate"); 
  if(risk_level == 2) Serial.println("UV risk level is high"); 
  if(risk_level == 3) Serial.println("UV risk level is very high"); 
  if(risk_level == 4) Serial.println("UV risk level is extreme"); 

  digitalWrite(myLed, !digitalRead(myLed));
  delay(ITime+20);
}
