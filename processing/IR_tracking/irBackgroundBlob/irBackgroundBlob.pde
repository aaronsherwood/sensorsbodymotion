import gab.opencv.*;
import com.thomasdiewald.ps3eye.PS3EyeP5;
import java.awt.Rectangle;

PS3EyeP5 ps3eye;
OpenCV opencv;

int blobSizeThreshold = 20;

void setup() {
  size(640, 480);
  ps3eye = PS3EyeP5.getDevice(this);
  ps3eye.start();
  opencv = new OpenCV(this, 640, 480);
  
  opencv.startBackgroundSubtraction(50, 3, 0.5);
}

void draw() {
  image(ps3eye.getFrame(), 0, 0);  
  opencv.loadImage(ps3eye.getFrame());
  
  opencv.updateBackground();
  opencv.contrast(30);
  opencv.dilate();
  opencv.erode();
  opencv.blur(50);
  //image(opencv.getSnapshot(), 0, 0); 
  noFill();
  stroke(255, 0, 0);
  strokeWeight(3);
  for (Contour contour : opencv.findContours()) {
    contour.draw();
     Rectangle r = contour.getBoundingBox();
    if (//(contour.area() > 0.9 * src.width * src.height) ||
        (r.width < blobSizeThreshold || r.height < blobSizeThreshold))
      continue;
    
    stroke(255, 0, 0);
    fill(255, 0, 0, 150);
    strokeWeight(2);
    rect(r.x, r.y, r.width, r.height);
    ellipse((float)r.getCenterX(),(float)r.getCenterY(),5,5);
  }
}