import gab.opencv.*;
import com.thomasdiewald.ps3eye.PS3EyeP5;
import java.awt.Rectangle;

PS3EyeP5 ps3eye;
OpenCV opencv;

int blobSizeThreshold = 1;

void setup() {
  size(640, 480);
  ps3eye = PS3EyeP5.getDevice(this);
  ps3eye.start();
  opencv = new OpenCV(this, 640, 480);

}

void draw() {
  background(0);
  //image(ps3eye.getFrame(), 0, 0);  
  opencv.loadImage(ps3eye.getFrame());
  

  opencv.threshold(100);

  //opencv.blur(50);
  //image(opencv.getSnapshot(), 0, 0); 
  noFill();
  stroke(255, 0, 0);
  strokeWeight(3);
  for (Contour contour : opencv.findContours()) {
    contour.draw();
     Rectangle r = contour.getBoundingBox();

    //if (r.width < blobSizeThreshold || r.height < blobSizeThreshold)
    //  continue;
    
    stroke(255, 0, 0);
    fill(255, 0, 0, 150);
    strokeWeight(2);
    rect(r.x, r.y, r.width, r.height);
    ellipse((float)r.getCenterX(),(float)r.getCenterY(),5,5);
  }
}