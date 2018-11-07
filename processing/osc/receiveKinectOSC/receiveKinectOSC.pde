/*
Order of Info from KinectOSC
it will send two coords for each joint if screen is selected in KinectOSC
it will send 3 coords for each if world is selected in KinectOSC
JOINT_TORSO
JOINT_NECK
JOINT_HEAD
JOINT_LEFT_SHOULDER
JOINT_LEFT_ELBOW
JOINT_LEFT_HAND
JOINT_RIGHT_SHOULDER
JOINT_RIGHT_ELBOW
JOINT_RIGHT_HAND
JOINT_LEFT_HIP
JOINT_LEFT_KNEE
JOINT_LEFT_FOOT
JOINT_RIGHT_HIP
JOINT_RIGHT_KNEE
JOINT_RIGHT_FOOT
 */
PVector JOINT_HEAD, 
  JOINT_NECK, 
  JOINT_LEFT_SHOULDER, 
  JOINT_LEFT_ELBOW, 
  JOINT_LEFT_HAND, 
  JOINT_RIGHT_SHOULDER, 
  JOINT_RIGHT_ELBOW, 
  JOINT_RIGHT_HAND, 
  JOINT_TORSO, 
  JOINT_LEFT_HIP, 
  JOINT_LEFT_KNEE, 
  JOINT_LEFT_FOOT, 
  JOINT_RIGHT_HIP, 
  JOINT_RIGHT_KNEE, 
  JOINT_RIGHT_FOOT;

import oscP5.*;
import netP5.*;

OscP5 oscP5;


void setup() {
  size(640, 480,P3D);
  oscP5 = new OscP5(this, 6448);
  JOINT_TORSO = new PVector(); 
  JOINT_NECK = new PVector();
  JOINT_HEAD = new PVector(); 
   
  JOINT_LEFT_SHOULDER = new PVector(); 
  JOINT_LEFT_ELBOW = new PVector(); 
  JOINT_LEFT_HAND = new PVector(); 
  
  JOINT_RIGHT_SHOULDER = new PVector(); 
  JOINT_RIGHT_ELBOW = new PVector(); 
  JOINT_RIGHT_HAND = new PVector(); 
  
  JOINT_LEFT_HIP = new PVector(); 
  JOINT_LEFT_KNEE = new PVector(); 
  JOINT_LEFT_FOOT = new PVector();
  
  JOINT_RIGHT_HIP = new PVector(); 
  JOINT_RIGHT_KNEE = new PVector(); 
  JOINT_RIGHT_FOOT = new PVector();
}


void draw() {
  background(0);
  stroke(0,255,0);
  fill(0,255,0);
  ellipse(JOINT_RIGHT_HAND.x,JOINT_RIGHT_HAND.y,20,20);
}


/* incoming osc message are forwarded to   the oscEvent method. */
void oscEvent(OscMessage theOscMessage) {
  if (theOscMessage.checkAddrPattern("/kinect/screen")==true) {
    //println("received: "+theOscMessage.addrPattern());
    JOINT_TORSO.set((float)theOscMessage.arguments()[0],(float)theOscMessage.arguments()[1],0);
    JOINT_NECK.set((float)theOscMessage.arguments()[2],(float)theOscMessage.arguments()[3],0);
    JOINT_HEAD.set((float)theOscMessage.arguments()[4],(float)theOscMessage.arguments()[5],0);
    JOINT_LEFT_SHOULDER.set((float)theOscMessage.arguments()[6],(float)theOscMessage.arguments()[7],0);
    JOINT_LEFT_ELBOW.set((float)theOscMessage.arguments()[8],(float)theOscMessage.arguments()[9],0);
    JOINT_LEFT_HAND.set((float)theOscMessage.arguments()[10],(float)theOscMessage.arguments()[11],0);
    JOINT_RIGHT_SHOULDER.set((float)theOscMessage.arguments()[12],(float)theOscMessage.arguments()[13],0);
    JOINT_RIGHT_ELBOW.set((float)theOscMessage.arguments()[14],(float)theOscMessage.arguments()[15],0);
    JOINT_RIGHT_HAND.set((float)theOscMessage.arguments()[16],(float)theOscMessage.arguments()[17],0);
    JOINT_LEFT_HIP.set((float)theOscMessage.arguments()[18],(float)theOscMessage.arguments()[19],0);
    JOINT_LEFT_KNEE.set((float)theOscMessage.arguments()[20],(float)theOscMessage.arguments()[21],0);
    JOINT_LEFT_FOOT.set((float)theOscMessage.arguments()[22],(float)theOscMessage.arguments()[23],0);
    JOINT_RIGHT_HIP.set((float)theOscMessage.arguments()[24],(float)theOscMessage.arguments()[25],0);
    JOINT_RIGHT_KNEE.set((float)theOscMessage.arguments()[26],(float)theOscMessage.arguments()[27],0);
    JOINT_RIGHT_FOOT.set((float)theOscMessage.arguments()[28],(float)theOscMessage.arguments()[29],0);
  }
  if (theOscMessage.checkAddrPattern("/kinect/realWorld")==true) {
    //println("received: "+theOscMessage.addrPattern());
    JOINT_TORSO.set((float)theOscMessage.arguments()[0],(float)theOscMessage.arguments()[1],(float)theOscMessage.arguments()[2]);
    JOINT_NECK.set((float)theOscMessage.arguments()[3],(float)theOscMessage.arguments()[4],(float)theOscMessage.arguments()[5]);
    JOINT_HEAD.set((float)theOscMessage.arguments()[6],(float)theOscMessage.arguments()[7],(float)theOscMessage.arguments()[8]);
    JOINT_LEFT_SHOULDER.set((float)theOscMessage.arguments()[9],(float)theOscMessage.arguments()[10],(float)theOscMessage.arguments()[11]);
    JOINT_LEFT_ELBOW.set((float)theOscMessage.arguments()[12],(float)theOscMessage.arguments()[13],(float)theOscMessage.arguments()[14]);
    JOINT_LEFT_HAND.set((float)theOscMessage.arguments()[15],(float)theOscMessage.arguments()[16],(float)theOscMessage.arguments()[17]);
    JOINT_RIGHT_SHOULDER.set((float)theOscMessage.arguments()[18],(float)theOscMessage.arguments()[19],(float)theOscMessage.arguments()[20]);
    JOINT_RIGHT_ELBOW.set((float)theOscMessage.arguments()[21],(float)theOscMessage.arguments()[22],(float)theOscMessage.arguments()[23]);
    JOINT_RIGHT_HAND.set((float)theOscMessage.arguments()[24],(float)theOscMessage.arguments()[25],(float)theOscMessage.arguments()[26]);
    JOINT_LEFT_HIP.set((float)theOscMessage.arguments()[27],(float)theOscMessage.arguments()[28],(float)theOscMessage.arguments()[29]);
    JOINT_LEFT_KNEE.set((float)theOscMessage.arguments()[30],(float)theOscMessage.arguments()[31],(float)theOscMessage.arguments()[32]);
    JOINT_LEFT_FOOT.set((float)theOscMessage.arguments()[33],(float)theOscMessage.arguments()[34],(float)theOscMessage.arguments()[35]);
    JOINT_RIGHT_HIP.set((float)theOscMessage.arguments()[36],(float)theOscMessage.arguments()[37],(float)theOscMessage.arguments()[38]);
    JOINT_RIGHT_KNEE.set((float)theOscMessage.arguments()[39],(float)theOscMessage.arguments()[40],(float)theOscMessage.arguments()[41]);
    JOINT_RIGHT_FOOT.set((float)theOscMessage.arguments()[42],(float)theOscMessage.arguments()[43],(float)theOscMessage.arguments()[44]);
  }
  //printArray(theOscMessage.arguments());
}