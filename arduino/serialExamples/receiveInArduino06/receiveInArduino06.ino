void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("0,0");
  pinMode(2,OUTPUT);
}

void loop() {
  if(Serial.available()>0){
    int inByte=Serial.read();
    digitalWrite(2,inByte);
    int sensor = analogRead(A0);
    delay(0);
    int sensor2 = analogRead(A1);
    delay(0);
    Serial.print(sensor);
    Serial.print(',');
    Serial.println(sensor2);
  }
}

/* Processing Code

import processing.serial.*;
Serial myPort;
int xPos=0;
int yPos=0;
boolean onOff=false;

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
  ellipse(xPos,yPos,30,30);
  if (mousePressed)
    onOff=true;
  else
    onOff=false;
}

void serialEvent(Serial myPort){
  String s=myPort.readStringUntil('\n');
  s=trim(s);
  if (s!=null){
    int values[]=int(split(s,','));
    if (values.length==2){
      xPos=(int)map(values[0],0,1023,0, width);
      yPos=(int)map(values[1],0,1023,0, height);
    }
  }
  myPort.write(int(onOff));
}

 */
