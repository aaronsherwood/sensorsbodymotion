void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int photoResistorVal = analogRead(A0);
  delay(1);
  
  int val = 0;
  if (Serial.available() > 0) {
    val = Serial.read();
  }

  // see if oF is ready for more data
  if (val == '!') {
    unsigned char val1;
    unsigned char val2;

    // & 0xFF is what is called a mask, to make the number be whatever is in the first byte of that number
    val1 =  photoResistorVal & 0xFF;
    // next we bit shift the number over to the right (which gets the second byte), and mask again (just for safety)
    val2 = (photoResistorVal >> 8) & 0xFF;

    Serial.write(val1);
    Serial.write(val2);

    // wait a little bit so we don't send too much data
    delay(20);
  }
  // clear serial buffer just in case
  Serial.flush();
}
