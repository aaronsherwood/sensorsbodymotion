/**
 * oscP5sendreceive by andreas schlegel
 * example shows how to send and receive osc messages.
 * oscP5 website at http://www.sojamo.de/oscP5
 */
 
import oscP5.*;
import netP5.*;
  
OscP5 oscP5;
NetAddress myRemoteLocation;
PFont f;
String message1="";
String message2="";
Mover m;
float x, y;

void setup() {
  size(400,400);
  frameRate(25);
  f = createFont("FranklinGoth-ExtCondensed", 32);
  textFont(f,32);
  /* start oscP5, listening for incoming messages at port 12000 */
  oscP5 = new OscP5(this,12000);
  /* myRemoteLocation is a NetAddress. a NetAddress takes 2 parameters,
   * an ip address and a port number. myRemoteLocation is used as parameter in
   * oscP5.send() when sending osc packets to another computer, device, 
   * application. usage see below. for testing purposes the listening port
   * and the port of the remote location address are the same, hence you will
   * send messages back to this sketch.
   */
  myRemoteLocation = new NetAddress("127.0.0.1",1234);
  m = new Mover();
  x = y = 0;
}


void draw() {
  background(0); 
  textAlign(CENTER);
  fill(255);
  text(message1,width/2,height/2-50); 
  text(message2,width/2,height/2+50); 
  PVector opFlow = new PVector(x, y);
  m.applyForce(opFlow);
  m.update();
  m.checkEdges();
  m.display();
}

/* incoming osc message are forwarded to the oscEvent method. */
void oscEvent(OscMessage theOscMessage) {
  /* print the address pattern and the typetag of the received OscMessage */
  print("### received an osc message.");
  print(" addrpattern: "+theOscMessage.addrPattern());
  print(" message 1: "+theOscMessage.get(0).floatValue());
  print(" message 2: "+theOscMessage.get(1).floatValue());
  println(" typetag: "+theOscMessage.typetag());
  x = theOscMessage.get(0).floatValue();
  y = theOscMessage.get(1).floatValue();
  message1=str(x);
  message2=str(y);
}