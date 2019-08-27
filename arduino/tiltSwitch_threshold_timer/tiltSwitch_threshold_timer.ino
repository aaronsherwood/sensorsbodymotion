int triggerThreshold = 0;
bool ledOn = false;
long ledOnLength = 0;

void setup() {
  // set pinmodes
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  // the tilt switch has to be in an ON state for a little bit 
  // in order to actually turn the LED on
  // we use the triggerThreshold for this
  if (digitalRead(2)==HIGH){
    triggerThreshold++;
  } else{
    triggerThreshold = 0;
    digitalWrite(13, LOW);
  }

  // if we've counted up past our threshold then turn LED on
  // and set our timer for when we will turn the LED off
  if (triggerThreshold > 50){
    ledOn = true;
    ledOnLength = millis() + 200;
  }

  // compare the current time to when we said to turn on the LED
  if (millis()>ledOnLength){
    ledOn = false;
  }

  // actually turn the LED on and off
  if (ledOn){
    digitalWrite(13, HIGH);
  } else{
    digitalWrite(13, LOW);
  }

}
