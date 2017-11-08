//HINT need pulldown resistor

const int humanPin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int touchAmount = analogRead(humanPin);
  delay(1);
  if (touchAmount > 0){
    Serial.println(touchAmount);
  }   
}
