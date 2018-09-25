const int xAxis=A0;
/*****************************************************************
Hardware Hookup:
  The XBee Shield makes all of the connections you'll need
  between Arduino and XBee. If you have the shield make
  sure the SWITCH IS IN THE "DLINE" POSITION. That will connect
  the XBee's DOUT and DIN pins to Arduino pins 2 and 3.

*****************************************************************/
// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(2, 3); // RX, 

const int yAxis=A1;
const int zAxis=A2;

void setup() {
  // put your setup code here, to run once:
  XBee.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  int x = analogRead(xAxis);
  delay(1);
  int y = analogRead(yAxis);
  delay(1);
  int z = analogRead(zAxis);
  delay(1);
  sendToIsadoraXbee(1,x);
  sendToIsadoraXbee(2,y);
  sendToIsadoraXbee(3,z);
}

void sendToIsadora(int route, int value)
{
  Serial.print(route);
  Serial.print('|');
  Serial.print(value);
  Serial.print(' ');
}
void sendToIsadoraXbee(int route, int value)
{
  XBee.print(route);
  XBee.print('|');
  XBee.print(value);
  XBee.print(' ');
}
