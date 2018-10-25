const int ledPin = 9;
int incomingByte;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
    analogWrite(ledPin, incomingByte);
  }
}
