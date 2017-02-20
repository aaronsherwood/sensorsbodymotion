const int humanPin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int touchAmount = analogRead(humanPin);
  delay(1);
  int mapped = map(touchAmount, 0, 12, 0, 100);
  if (touchAmount > 0){
    Serial.println(touchAmount);
  }   
}
