/*************************************************** 
  This is a library for the HTU21DF Humidity & Temp Sensor

  Designed specifically to work with the HTU21DF sensor from Adafruit
  ----> https://www.adafruit.com/products/1899

  These displays use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

/*************************************************** 
  Adapted by Michael Siegel @pomplesiegel on 9/15/2015 for 
  use on Particle (Spark) Core and Photon
****************************************************/

#include "Adafruit_HTU21DF.h"

//empty constructor
Adafruit_HTU21DF::Adafruit_HTU21DF() 
{
}

//sends initialization signal to HTU21D-F IC
//Returns back true if it receives the expected response from the IC
//Wire.begin() must be called before this
bool Adafruit_HTU21DF::reset() 
{  
  //Send reset signal to IC
  Wire.beginTransmission(HTU21DF_I2CADDR);
  Wire.write(HTU21DF_RESET);
  Wire.endTransmission();
  
  //Delay to allow reset to digest
  delay(15);

  //Read from IC's register to see current state
  Wire.beginTransmission(HTU21DF_I2CADDR);
  Wire.write(HTU21DF_READREG);
  Wire.endTransmission();
  Wire.requestFrom(HTU21DF_I2CADDR, 1);

  //Store the IC's register state
  uint8_t returnValue = Wire.read(); 

  if(returnValue != 0x2)
  {
    // after reset should be 0x2
    Serial.println("HTU21DF: reset() return wrong: " + String(returnValue, HEX) );
    return false;
  }
  return true; //otherwise, we're ok
}

//Reads temperature from the IC
float Adafruit_HTU21DF::readTemperature() 
{
  //Begin transmission to IC
  Wire.beginTransmission(HTU21DF_I2CADDR);
  Wire.write(HTU21DF_READTEMP);
  Wire.endTransmission();
  
  // delay(50); // possible delay
  
  Wire.requestFrom(HTU21DF_I2CADDR, 3);

  //clear our counter
  numCommAttempts = 1;

  //to see if we're waiting.
  while ( !Wire.available() && numCommAttempts < 5 ) 
  {
    delay(10);
    Serial.println("Temp still not available...");
    numCommAttempts++; //increment counter
  }

  uint16_t t = Wire.read();
  t <<= 8;
  t |= Wire.read();

  //Unused CRC
  Wire.read();

  //assign to float for manipulation
  temperature = t;

  // (t * 175.72 / 65536) - 46.85
  temperature = (temperature * 0.00268127441406) - 46.85; 

  return temperature;
}
  
//Reads humidity from the IC
float Adafruit_HTU21DF::readHumidity() 
{
  //Begin transmission to IC
  Wire.beginTransmission(HTU21DF_I2CADDR);
  Wire.write(HTU21DF_READHUM);
  Wire.endTransmission();
  
  // delay(50); // possible delay
  
  Wire.requestFrom(HTU21DF_I2CADDR, 3);

  //clear our counter
  numCommAttempts = 1;

  //to see if we're waiting.
  while ( !Wire.available() && numCommAttempts < 5 ) 
  {
    delay(10);
    Serial.println("Humidity still not available...");
    numCommAttempts++; //increment counter
  }

  uint16_t h = Wire.read();
  h <<= 8;
  h |= Wire.read();

  //Unused CRC
  Wire.read();

  //assign to float for manipulation
  humidity = h;

  // (h * 125 / 65536) - 6
  humidity = (humidity * 0.00190734863281) - 6; 

  return humidity;
}



/*********************************************************************/
