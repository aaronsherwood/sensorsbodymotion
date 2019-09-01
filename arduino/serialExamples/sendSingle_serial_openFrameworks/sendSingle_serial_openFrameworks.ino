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
    unsigned char val1 = 0;

    if (photoResistorVal <800){
      val1 = 1;
    }
 
    Serial.write(val1);

    // wait a little bit so we don't send too much data
    delay(20);
  }
  // clear serial buffer just in case
  Serial.flush();
}
