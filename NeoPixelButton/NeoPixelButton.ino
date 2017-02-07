#include <Adafruit_NeoPixel.h>

// Adapted from NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define NEOPIXELPIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      1

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);

const int buttonPin = 2;
boolean switchOn = false;
boolean pButtonState = false;

void setup() {
  pinMode(buttonPin, INPUT);
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {

  // see if the button is pressed
  int buttonState = digitalRead(buttonPin);

  // if the button state is different then last time, let's do something
  if (buttonState != pButtonState) {
    //if button pressed 
    int red;
    int green;
    int blue;
    if (buttonState == HIGH ){
      //choose some random colors
      red   = random(256);
      green = random(256);
      blue  = 128;//random(256);
      
    // if button is not released
    } else {
      red = green = blue = 0;
    }
    //for loop!
    //set all the pixels
    for(int i=0;i<NUMPIXELS;i++){
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(red,green,blue)); 
       // This sends the updated pixel color to the hardware.
    }
    pixels.show();
  }
  // remember what state the button is this frame
  pButtonState=buttonState;
}
