// Daniel Shiffman
// All features test

// https://github.com/shiffman/OpenKinect-for-Processing
// http://shiffman.net/p5/kinect/

import org.openkinect.freenect.*;
import org.openkinect.processing.*;

Kinect kinect;

float deg;
boolean mirror = false;

void setup() {
  size(640, 480);
  kinect = new Kinect(this);
  kinect.initDepth();

}


void draw() {
  background(0);
  image(kinect.getDepthImage(), 0, 0);
  fill(255);
}

void keyPressed() {
  if(key == 'm'){
    mirror = !mirror;
    kinect.enableMirror(mirror);
  } 
}