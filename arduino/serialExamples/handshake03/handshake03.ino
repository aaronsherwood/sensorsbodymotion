void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.write(0);
}

void loop() {
  if(Serial.available()>0){
    int inByte=Serial.read();
    int sensor = analogRead(A0);
    delay(1);
    sensor/=4;
    Serial.write(sensor);
  }
}

/* Processing Code

import processing.serial.*;

Serial myPort;

int xPos=0;

void setup(){
  size(255,255);
  printArray(Serial.list());
  String portname=Serial.list()[1];
  println(portname);
  myPort = new Serial(this,portname,9600);
}

void draw(){
  background(255);
  ellipse(xPos,height/2,30,30);
}

void serialEvent(Serial myPort){
  xPos=myPort.read();
  myPort.write(0);
}



 */
