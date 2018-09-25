int smoothed = 0;               

const int inputPin = A0;

void setup() {
  // initialize serial communication with computer:
  Serial.begin(9600);
}

void loop() {
 
  int currentRead = analogRead(inputPin);
  smoothed += (currentRead - smoothed) * .05;
  Serial.print(currentRead);
  Serial.print("  ");
  Serial.println(smoothed);
  delay(2);        // delay in between reads for stability
}


