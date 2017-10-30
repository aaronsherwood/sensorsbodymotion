///////////// NEOPIXEL STUFF //////////////////////////////////////////////////////////////////////////////
#include <Adafruit_NeoPixel.h>

// Adapted from NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define NEOPIXELPIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      9

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);
////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////// MOVER CLASS //////////////////////////////////////////////////////////////////////////////////
class PixelMover {
  public:
    PixelMover();
    int location;
    int red;
    int green;
    int blue;
    int speedCounter;
    int velocity;
    bool active;
    void advanceLocation(int numpixels);
    void show();
    void activate();
};

PixelMover::PixelMover() {
  location = 0;
  red   = random(256);
  green = random(256);
  blue  = 128;//random(256);
  speedCounter = 0;
  velocity = 600;
  active = false;
}

void PixelMover::advanceLocation(int numpixels) {
  if ((int)speedCounter % velocity == 0 && speedCounter > 0) //speed counter greater than 0 so that we wait one round before moving to the next spot
    location++;
  if (location == numpixels) {
    active = false;
  }
  speedCounter++;
}

void PixelMover::show() {
  pixels.setPixelColor(location, pixels.Color(red, green, blue));
}

void PixelMover::activate() {
  location = 0;
  speedCounter = 0;
  active = true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////



const int buttonPin = 2;
boolean switchOn = false;
boolean pButtonState = LOW;
PixelMover movers[10];

void setup() {
  pinMode(buttonPin, INPUT);
  pixels.begin(); // This initializes the NeoPixel library.;
  for (int i = 0; i < 10; i++) {
    movers[i] = PixelMover();
  }
  pixels.show();
  Serial.begin(9600);

}

void loop() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }

  for (int i = 0; i < 10; i++) {
    if (movers[i].active) {
      movers[i].show();
      movers[i].advanceLocation(NUMPIXELS);
    }
  }
  
  pixels.show();

  // see if the button is pressed
  int buttonState = digitalRead(buttonPin);

  // if the button state is different then last time, let's do something
  if (buttonState != pButtonState) {
    //if button pressed
    if (buttonState == HIGH ) {
      for (int i = 0; i < 10; i++) {
        if (movers[i].active == false) {
          movers[i].activate();
          Serial.println(i);
          break;
        }
      }

    }
  }
  // remember what state the button is this frame
  pButtonState = buttonState;
}



