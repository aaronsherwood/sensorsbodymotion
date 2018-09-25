// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(2, 3); // RX, TX

void setup()
{
  // Set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.
  XBee.begin(9600);
  Serial.begin(9600);
}

void loop()
{
 sendToIsadoraXbee(1,0);
 digitalWrite(13,LOW);
 delay(500);
 sendToIsadoraXbee(1,1);
 digitalWrite(13,HIGH);
 delay(500);
}

void sendToIsadoraXbee(int route, int value)
{
  XBee.print(route);
  XBee.print('|');
  XBee.print(value);
  XBee.print(' ');
}
