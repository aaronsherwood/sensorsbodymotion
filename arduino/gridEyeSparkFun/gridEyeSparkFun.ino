#include <Wire.h>
#include <SparkFun_GridEYE_Arduino_Library.h>

GridEYE grideye;

void setup() {

  // Start your preferred I2C object 
  Wire.begin();
  // Library assumes "Wire" for I2C but you can pass something else with begin() if you like
  grideye.begin();
  // Pour a bowl of serial
  Serial.begin(115200);

}

void loop() {

  // Print the temperature value of each pixel in floating point degrees Celsius
  // separated by commas 
  for(unsigned char i = 0; i < 64; i++){
    Serial.print(grideye.getPixelTemperature(i));
    Serial.print(",");
  } 

  // End each frame with a linefeed
  Serial.println();

  // Give Processing time to chew
  delay(100);

}
