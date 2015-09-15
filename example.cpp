#include "application.h"
#include "Adafruit_HTU21DF.h"

SYSTEM_MODE(MANUAL);

Adafruit_HTU21DF mySensor; 

void setup()
{
  Serial.begin(9600);
  Serial.println("Beginning!");
  Wire.begin();

  mySensor.reset();
}


void loop()
{
  Serial.println("Temp: " + String(mySensor.readTemperature() ) );
  Serial.println("Humidity: " + String(mySensor.readHumidity() ) );

  delay(1000);
}