import processing.video.*;
import processing.sound.*;
import de.looksgood.ani.*;

Capture video;
int locX, locY;
PImage prevFrame;
float threshold=75;
boolean drawRect=false;
boolean drawRect2=false;
SoundFile[] sounds;
float timing=0.;
float timing2=0.;

void setup() {
  size(640, 480);
  video = new Capture(this, 640, 480, 30);
  video.start();
  prevFrame=createImage(640, 480, RGB);

  sounds = new SoundFile[5];
  for (int i = 0; i < 5; i++) {
    sounds[i] = new SoundFile(this, (i+1) + ".aif");
  }
  Ani.init(this);
  noStroke();
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
  for (int y=0; y<height; y++) {
    for (int x=0; x<width; x++) {
      int loc = (video.width-x-1)+(y*width);
      color pix=video.pixels[loc];
      color prevPix=prevFrame.pixels[loc];
      float r1=red(pix);
      float g1=green(pix);
      float b1=blue(pix);
      float r2=red(prevPix);
      float g2=green(prevPix);
      float b2=blue(prevPix);
      float diff=dist(r1, g1, b1, r2, g2, b2);
      if (diff>threshold) {
        if (x>width-120&&x<width-20&y>20&&y<120)
          drawRect2=true;
        if (x>20&&x<120&y>20&&y<120)
          drawRect=true;
      }
    }
  }
  video.updatePixels();

  pushMatrix();
  translate(width, 0);
  scale(-1, 1);
  image(video, 0, 0);
  popMatrix();
  prevFrame.updatePixels();

  if (drawRect==true ) {
    fill(255, map(timing, 0, 1, 0, 255));
    rect(20, 20, 100, 100);
    if (timing==0.) {
      timing=1;
      int sound=(int)random(5);
      Ani.to(this, sounds[sound].duration(), "timing", 0.);
      sounds[sound].play(1., 1.);
    }
  } 
  if (drawRect2==true ) {
    fill(255, map(timing2, 0, 1, 0, 255));
    rect(width-120, 20, 100, 100);
    if (timing2==0.) {
      timing2=1;
      int sound=(int)random(5);
      Ani.to(this, sounds[sound].duration(), "timing2", 0.);
      sounds[sound].play(1., 1.);
    }
  }

  if (timing<0.01)
    drawRect=false;
  if (timing2<0.01)
    drawRect2=false;
}