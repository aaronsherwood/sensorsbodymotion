int left = 0;
int right = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("0,0");
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  while (Serial.available()) {
    right = Serial.parseInt();
    left = Serial.parseInt();
    if (Serial.read() == '\n') {
      digitalWrite(3, right);
      digitalWrite(5, left);
      int sensor = analogRead(A0);
      delay(0);
      int sensor2 = analogRead(A1);
      delay(0);
      Serial.print(sensor);
      Serial.print(',');
      Serial.println(sensor2);
    }
  }
}

/*

import processing.serial.*;
Serial myPort;
int xPos=0;
int yPos=0;
boolean onOff=false;
boolean onOff2=false;

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
  if (mousePressed){
    if(mouseX<=width/2)
      onOff2=true;
    else
      onOff=true;
  }else{
    onOff=onOff2=false;
  }
}

void serialEvent(Serial myPort){
  String s=myPort.readStringUntil('\n');
  s=trim(s);
  if (s!=null){
    println(s);
    int values[]=int(split(s,','));
    if (values.length==2){
      xPos=(int)map(values[0],0,1023,0, width);
      yPos=(int)map(values[1],0,1023,0, height);
    }
  }
  myPort.write(int(onOff)+","+int(onOff2)+"\n");
}

 */
