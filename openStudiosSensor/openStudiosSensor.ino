#include <SoftwareSerial.h>
SoftwareSerial XBee(2, 3);

const int lightPin = A0;  //define a pin for infred
boolean trigger = false;
int timer = 0;
const int signPin =  7;
int counter = 0;
bool signOnOff = true;
bool flashing = false;
long flashCounter = 0;

void setup()
{
  XBee.begin(9600);
  Serial.begin(9600);
    // initialize the LED pin as an output:
  pinMode(signPin, OUTPUT);
}

void loop()
{
  
  int val = analogRead(lightPin);
//  Serial.println(val);
  if (val > 400 && trigger == false) {
    trigger = true;
    timer = 1000;
//    Serial.println(trigger);
   sendToIsadoraXbee(1, 1);
  }
  if (trigger == true) {
    if (timer <= 0 && val < 400) {
      trigger = false;
//      Serial.println(trigger);
      sendToIsadoraXbee(1, 0);
    }
    else {
      timer--;
    }
  }
  //  if (val < 355) {
  //    trigger = false;
  //        Serial.println(trigger);
//      sendToIsadoraXbee(1,0);
  //  }
  delay(1);

  flash_IM_Sign(trigger);
}
void sendToIsadoraXbee(int route, int value)
{
  XBee.print(route);
  XBee.print('|');
  XBee.print(value);
  XBee.print(' ');
}

void flash_IM_Sign(bool onOff) {
  //adjust numbers for counter and flashCounter modulo to adjust speed
  //printing things out to serial will effect this greatly
  if (onOff == HIGH) {
    flashing = true;
    counter = 300;
  }
  else if (flashing) {
    counter--;
  }
  if (flashing) {
    if (flashCounter % 50 == 0)
      signOnOff = !signOnOff;

  }
  if (counter <= 0) {
    flashing = false;
    signOnOff = true;
  }

  digitalWrite(signPin, signOnOff);
  flashCounter++;

  if (flashCounter == 1000) flashCounter = 0;
}
