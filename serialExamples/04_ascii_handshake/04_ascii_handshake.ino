void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println('0');
}

void loop() {
  if(Serial.available()>0){
    char inByte=Serial.read();
    int sensor = analogRead(A0);
    delay(0);
    Serial.println(sensor);
  }
}

/* Processing Code

import processing.serial.*;
Serial myPort;
int xPos=0;

void setup(){
  size(960,720);
  printArray(Serial.list());
  String portname=Serial.list()[1];
  println(portname);
  myPort = new Serial(this,portname,9600);
  myPort.clear();
  myPort.bufferUntil('\n');
}

void draw(){
  background(255);
  ellipse(xPos,height/2,30,30);
}

void serialEvent(Serial myPort){
  String s=myPort.readStringUntil('\n');
  s=trim(s);
  if (s!=null){
    xPos=(int)map(int(s),0,1023,0, width);
  }
  println(xPos);
  myPort.write('0');
}



 */
