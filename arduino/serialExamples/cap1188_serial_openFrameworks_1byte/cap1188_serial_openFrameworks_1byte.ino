/***************************************************
  This is a library for the CAP1188 I2C/SPI 8-chan Capacitive Sensor

  Designed specifically to work with the CAP1188 sensor from Adafruit
  ----> https://www.adafruit.com/products/1602

  These sensors use I2C/SPI to communicate, 2+ pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_CAP1188.h>

// Reset Pin is used for I2C or SPI
#define CAP1188_RESET  9

// CS pin is used for software or hardware SPI
#define CAP1188_CS  10

// These are defined for software SPI, for hardware SPI, check your
// board's SPI pins in the Arduino documentation
#define CAP1188_MOSI  11
#define CAP1188_MISO  12
#define CAP1188_CLK  13

// For I2C, connect SDA to your Arduino's SDA pin, SCL to SCL pin
// On UNO/Duemilanove/etc, SDA == Analog 4, SCL == Analog 5
// On Leonardo/Micro, SDA == Digital 2, SCL == Digital 3
// On Mega/ADK/Due, SDA == Digital 20, SCL == Digital 21

// Use I2C, no reset pin!
Adafruit_CAP1188 cap = Adafruit_CAP1188();

// Or...Use I2C, with reset pin
//Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_RESET);

// Or... Hardware SPI, CS pin & reset pin
// Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_CS, CAP1188_RESET);

// Or.. Software SPI: clock, miso, mosi, cs, reset
//Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_CLK, CAP1188_MISO, CAP1188_MOSI, CAP1188_CS, CAP1188_RESET);

void setup() {
  Serial.begin(9600);

  // Initialize the sensor, if using i2c you can pass in the i2c address
  // if (!cap.begin(0x28)) {
  if (!cap.begin()) {
    Serial.println("CAP1188 not found");
    while (1);
  }

  /*
    SENSITIVITY SETTINGS
    Decrease sensitivity a little - default is 0x2F (32x) per datasheet
    0x3F - 16x sensitivity
    0x4F - 8x  sensitivity
    0x5F - 4x  sensitivity
    0x6F - 2x  sensitivity THIS SEEMS TO WORK THE BEST FOR 3.5" plate sensors
    0x7F - 1x  sensitivity
  */
  uint8_t reg = cap.readRegister( 0x1f ) & 0x0f;
  cap.writeRegister( 0x1f, reg | 0x6F ); // put the hex sensitivity value in the last spot here
}

void loop() {
  uint8_t touched = cap.touched();
  int val = 0;
  if (Serial.available() > 0) {
    val = Serial.read();
  }

  //check if OF wants data
  //if we get a '!' from OF then we should send the values
  if (val == '!') {
    unsigned char values[8];
    for (uint8_t i = 0; i < 8; i++) {
      int on = 0;
      //gnarley bitwise operations to see if pin i is touched
      //touched returns the number of the touched pin in powers of two
      //1 << i shifts the number 1 in binary over to the left by i number of positions
      //so! if i is 3 we shift one over to the left 3 times and get 1000 in binary
      //which back in decimal is 8
      if (touched & (1 << i)) {
        on = 1;
      }
      values[i] = on;
    }

    unsigned char byteToSend;
    byteToSend = values[0]<<7 | 
      (values[1]<<6) |
      (values[2]<<5) |
      (values[3]<<4) |
      (values[4]<<3) |
      (values[5]<<2) |
      (values[6]<<1) |
      (values[7] & 0x01);

    Serial.write(byteToSend);

    //wait a little bit so we don't send too much data
    //might not be nessecary
    delay(20);
  }
  Serial.flush();
}
