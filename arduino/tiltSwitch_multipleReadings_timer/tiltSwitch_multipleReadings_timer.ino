int tiltPin = 2;
int ledPin = 13; //built in LED
long waitUntil = 0;
bool triggered = false;
int thresh = 10;
float onTime = 1500;

void setup() {
  pinMode(tiltPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // counter to count up how many on readings we get
  int counter = 0;
  
  // if we're not waiting after a trigger
  // this means the millis have gone higher than the wait time
  if (waitUntil < millis()) {
    // turn the trigger off
    triggered = false;

    // read the tilt switch as many times as we  decided with thresh
    for (int i = 0; i < thresh; i++) {
      bool tiltRead = digitalRead(tiltPin);
      if (tiltRead)
        counter++; // count up how many times it is on
      else
        counter = 0;
    }
  }

  // if the counter equals our thresh than consider it triggered
  if (counter >= thresh) {
    triggered = true;
    // set the wait time
    waitUntil = millis() + onTime;
  }

  // turn LED on or off
  if (triggered) {
    Serial.println("triggered");
    digitalWrite(ledPin, HIGH);
  } else {
    Serial.println("not triggered");
    digitalWrite(ledPin, LOW);
  }
}
