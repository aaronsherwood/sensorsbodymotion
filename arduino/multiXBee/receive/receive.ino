#include <SoftwareSerial.h>
SoftwareSerial XBee(2, 3);

bool in = false;
bool pIn = false;

void setup() {
  Serial.begin(9600);
  XBee.begin(9600);
}

void loop() {
  while (XBee.available() > 0) {
    int reading = XBee.read();
    if (reading == 49) { //ascii for 1
      in = true;
    } else if (reading == 48) { //ascii for 0
      in = false;
    }
  }

  if (in != pIn) {
    if (in) {
      digitalWrite(13, HIGH);
      Serial.println("on");
    } else {
      digitalWrite(13, LOW);
      Serial.println("off");
    }
  }
  pIn = in;
}
