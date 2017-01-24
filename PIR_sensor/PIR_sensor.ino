// designate which pins to use for the LED and for the IR Sensor
int ledPin = 9;
int sensorPin = 2;

void setup() {
  //set the LED pin to output
  pinMode(ledPin, OUTPUT);
  //set the sensor pin to input
  pinMode(sensorPin, INPUT);
  
  //begin serial so we can print out the results
  Serial.begin(9600);
}

void loop() {
  //the Passive Infra Red (PIR) sensor detects motion, not distance,
  //so digital read the sensor, if HIGH activate the LED,
  //if LOW, turn the LED off
  if (digitalRead(sensorPin)==1) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  //print the results to the serial monitor
  Serial.println(digitalRead(sensorPin));

  //a short delay. delays can help efficiency
  //if very quick readings are not needed.
  delay(50);
}
