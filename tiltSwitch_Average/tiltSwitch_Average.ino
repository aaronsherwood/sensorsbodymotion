//use pin 2 for the tilt switch
const int tiltSwitch = 2;
//use pin 9 for LED pin
const int ledPin = 9;

const int numReadings = 75;
int readings[numReadings];
int currentPosition = 0;
int total = 0;
int prevAverage=1;
int ledState = LOW;
bool triggerLed = false;

void setup() {
  //set pinMode & begin serial
  pinMode(tiltSwitch, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  for (int i=0; i<numReadings; i++){
    readings[i]=0;
  }

}

void loop() {

  //remove the last reading that was at the current position
  //from the running total
  total = total - readings[currentPosition];
  
  //read the tilt switch
  int tiltState = digitalRead(tiltSwitch);
  //store that reading in the readings array
  readings[currentPosition] = tiltState;
  //add the current tilt state to the total
  total = total + tiltState;

  //advance the current position
  currentPosition++;
  //if past the maximum number of readings we should take
  //loop back to zero
  if (currentPosition >= numReadings) {
    currentPosition = 0;
  }

  //calculate average of all the readings
  int average = total/numReadings;

  if (average != prevAverage) {
    ledState = 1 - ledState;
    digitalWrite(ledPin, ledState);
  }

  prevAverage = average;
  
  Serial.print(average);
  Serial.print("  ");
  Serial.println(prevAverage);

}
