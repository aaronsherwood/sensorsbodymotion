import processing.video.*;
Capture video;
int locX, locY;
PImage prevFrame;
float threshold=50;
boolean drawRect=false;

void setup() {
  size(640, 480);
  video = new Capture(this, 640, 480, 30);
  video.start();
  prevFrame=createImage(640, 480, RGB);
}

void draw() {
  background(0);
  if (video.available()) {
    prevFrame.copy(video, 0, 0, 640, 480, 0, 0, 640, 480);
    prevFrame.updatePixels();
    video.read();
  }
  video.loadPixels();
  prevFrame.loadPixels();
  loadPixels();
  float totalMotion=0;
  for (int y=0; y<height; y++) {
    for (int x=0; x<width; x++) {
      int loc = x+(y*width);
      color pix=video.pixels[loc];
      color prevPix=prevFrame.pixels[loc];
      float r1=red(pix);
      float g1=green(pix);
      float b1=blue(pix);
      float r2=red(prevPix);
      float g2=green(prevPix);
      float b2=blue(prevPix);
      float diff=dist(r1, g1, b1, r2, g2, b2);
      totalMotion+=diff;
      if (diff>threshold) {
        pixels[loc]=color(255);
        if(x>20&&x<120&y>20&&y<120)
          drawRect=true;
      } else {
        pixels[loc]=color(0);
      }
    }
  }
  float avgMotion=totalMotion/pixels.length;
  println(avgMotion);
  video.updatePixels();
  prevFrame.updatePixels();
  updatePixels();
  fill(255);
  if(drawRect)
    rect(20,20,100,100);
  drawRect=false;
}