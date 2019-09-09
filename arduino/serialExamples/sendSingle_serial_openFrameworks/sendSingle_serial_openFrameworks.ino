void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int photoResistorVal = analogRead(A0);
  delay(1);

  int valFromOF = 0;
  if (Serial.available() > 0) {
    valFromOF = Serial.read();
  }

  // see if oF is ready for more data
  if (valFromOF == '!') {
    unsigned char valToSend = 0;

    if (photoResistorVal < 800) {
      valToSend = 1;
    }

    Serial.write(valToSend);

    // wait a little bit so we don't send too much data
    delay(20);
  }
  // clear serial buffer just in case
  Serial.flush();
}
