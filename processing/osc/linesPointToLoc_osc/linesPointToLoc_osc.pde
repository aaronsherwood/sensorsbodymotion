import oscP5.*;
import netP5.*;
OscP5 oscP5;
NetAddress myRemoteLocation;

float oscX, oscY;
float locX, locY;

void setup() {
  fullScreen();
  oscP5 = new OscP5(this, 12000);
  myRemoteLocation = new NetAddress("127.0.0.1", 1234);
  locX=locY=oscX=oscY=0;
}

void draw() {
  background(255);
  locX += (oscX-locX) * 0.1;
  locY += (oscY-locY) * 0.1;
  for (int y=0; y<height; y+=30) {
    for (int x=0; x<width; x+=30) {
      float xVec= locX-x;
      float yVec = locY-y;
      float angle = atan2(yVec, xVec);
      pushMatrix();
      translate(x, y);
      rotate(angle);
      line(0, 0, 30, 0);
      popMatrix();
    }
  }
}

/* incoming osc message are forwarded to the oscEvent method. */
void oscEvent(OscMessage theOscMessage) {
  /* print the address pattern and the typetag of the received OscMessage */
  print("### received an osc message.");
  print(" addrpattern: "+theOscMessage.addrPattern());
  print(" message 1: "+theOscMessage.get(0).floatValue());
  print(" message 2: "+theOscMessage.get(1).floatValue());
  println(" typetag: "+theOscMessage.typetag());
  oscX = map(theOscMessage.get(0).floatValue(), 0, 640, 0, width);
  oscY = map(theOscMessage.get(1).floatValue(), 0, 480, 0, height);
}