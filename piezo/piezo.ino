const int peizoPin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int peizoAmount = analogRead(peizoPin);

  if (peizoAmount > 0){
    Serial.println(peizoAmount);
  }   
}
