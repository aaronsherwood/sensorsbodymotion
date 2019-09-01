void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int photoResistorVal = analogRead(A0);
  int potentiometerVal = analogRead(A1);
  delay(1);
  
  int val = 0;
  if (Serial.available() > 0) {
    val = Serial.read();
  }

  // see if oF is ready for more data
  if (val == '!') {
    unsigned char val1 = 0;
    unsigned char val2 = 0;

    if (photoResistorVal <800){
      val1 = 1;
    }

    if (potentiometerVal >500){
      val2 = 1;
    }

    // put two values together into one byte
    unsigned char byteToSend = (val1 << 1) | val2;
 
    Serial.write(byteToSend);

    // wait a little bit so we don't send too much data
    delay(20);
  }
  // clear serial buffer just in case
  Serial.flush();
}
