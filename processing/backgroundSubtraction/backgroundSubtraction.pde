import processing.video.*;
Capture video;
int locX, locY;
PImage backgroundImg, subImage, beach;
float threshold=20;

void setup() {
  size(640, 480);
  video = new Capture(this, 640, 480, 30);
  video.start();
  backgroundImg=createImage(640, 480, RGB);
  subImage=createImage(640, 480, RGB);
  beach=loadImage("beach.jpg");
}

void draw() {
  image(beach, 0, 0, width, height);
  if (video.available()) {
    video.read();
  }
  video.loadPixels();
  backgroundImg.loadPixels();
  subImage.loadPixels();
  beach.loadPixels();
  float dist=500;
  for (int y=0; y<height; y++) {
    for (int x=0; x<width; x++) {
      int loc = (video.width-x-1)+(y*width);
      color pix=video.pixels[loc];
      color bPix=backgroundImg.pixels[loc];
      color bg=beach.pixels[loc];
      float r1=red(pix);
      float g1=green(pix);
      float b1=blue(pix);
      float r2=red(bPix);
      float g2=green(bPix);
      float b2=blue(bPix);
      float diff=dist(r1, g1, b1, r2, g2, b2);

      if (diff>threshold) {
        subImage.pixels[loc]=pix;
      } else {
        subImage.pixels[loc]=bg;
      }
    }
  }
  video.updatePixels();
  backgroundImg.updatePixels();
  subImage.updatePixels();
  pushMatrix();
  //translate(width,0);
  //scale(-1,1);
  image(subImage, 0, 0);
  popMatrix();
}

void mousePressed() {
  backgroundImg.copy(video, 0, 0, 640, 480, 0, 0, 640, 480);
  backgroundImg.updatePixels();
}