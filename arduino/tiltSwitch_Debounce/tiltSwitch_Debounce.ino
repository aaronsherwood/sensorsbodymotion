/*
 created 21 November 2006
 by David A. Mellis
 modified 30 Aug 2011
 by Limor Fried
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/Debounce
 */

//use pin 2 for the tilt switch
const int tiltSwitch = 2;
//use pin 9 for LED pin
const int ledPin = 13;

int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 20;    // the debounce time; increase if the output flickers

void setup() {
  //set pinMode
  pinMode(tiltSwitch, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = 1 - digitalRead(tiltSwitch);

  // check to see if you just pressed the button 
  // (i.e. the input went from LOW to HIGH),  and you've waited 
  // long enough since the last press to ignore any noise:  

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    buttonState = reading;
    Serial.println(buttonState);
  }
  
  // set the LED using the state of the button:
  digitalWrite(ledPin, buttonState);

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
}
