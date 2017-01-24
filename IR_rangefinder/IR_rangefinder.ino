int irSensor = A2;     // the analog in pin
int led = 9;           // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 15;   // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  int sensorValue = analogRead(irSensor);
  //if the reading is over a certain threshold, fade the LED in
  //otherwise, fade the LED out
  if (sensorValue > 100 && brightness < 255) {
    brightness = brightness + fadeAmount; 
  } else if (brightness > 0) {
    brightness = brightness - fadeAmount;
  }
  // set the brightness of pin 9:
  analogWrite(led, brightness);
 
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}
