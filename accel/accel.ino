const int xAxis=A0;
const int yAxis=A1;
const int zAxis=A2;

void setup() {
  // put your setup code here, to run once:
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
  sendToIsadora(1,x);
  sendToIsadora(2,y);
  sendToIsadora(3,z);
}

void sendToIsadora(int route, int value)
{
  Serial.print(route);
  Serial.print('|');
  Serial.print(value);
  Serial.print(' ');
}
