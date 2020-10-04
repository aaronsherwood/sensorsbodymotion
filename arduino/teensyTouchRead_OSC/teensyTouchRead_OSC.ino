void setup() {
  //begin serial
  Serial.begin(9600);
}

void loop() {
  // touch pin 15
  float data = touchRead(15);
  data = map(data, 900, 7000, 0, 1);
  data = constrain(data, 0, 1);
  Serial.print("/ctrl,touchRead1,");
  Serial.println(data);

  // touch pin 16
  data = touchRead(16);
  data = map(data, 900, 7000, 0, 1);
  data = constrain(data, 0, 1);
  Serial.print("/ctrl,touchRead2,");
  Serial.println(data);
}
