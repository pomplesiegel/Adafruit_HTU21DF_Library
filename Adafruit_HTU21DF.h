/*************************************************** 
  This is a library for the HTU21D-F Humidity & Temp Sensor

  Designed specifically to work with the HTU21D-F sensor from Adafruit
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

#include "application.h"

#define HTU21DF_I2CADDR       0x40
#define HTU21DF_READTEMP      0xE3
#define HTU21DF_READHUM       0xE5
#define HTU21DF_WRITEREG       0xE6
#define HTU21DF_READREG       0xE7
#define HTU21DF_RESET       0xFE

class Adafruit_HTU21DF 
{
 public:

  //constructor
  Adafruit_HTU21DF();

  //sends initialization signal to HTU21D-F IC
  //Returns back true if it receives the expected response from the IC
  //Wire.begin() must be called before this
  bool reset();

  //Reads temperature from the IC
  float readTemperature();

  //Reads humidity from the IC
  float readHumidity();

 protected:
  //Represents the most recent humidity and temperature taken
  float humidity, temperature;

  //Number of consecutive times we've tried to read from this IC
  int numCommAttempts; 
};

