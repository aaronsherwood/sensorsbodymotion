import processing.video.*;
Capture video;

float brightest=0;
int brightestX;
int brightestY;

void setup() {
  size(640, 480);
  noStroke();
  video = new Capture(this, 640, 480, 30);
  video.start();
}

void draw() {
  if (video.available()) {
    video.read();
  }
  video.loadPixels();
  brightest=0;
  for (int y=0; y<height; y++) {
    for (int x=0; x<width; x++) {
      int loc = (video.width-x-1)+(y*width);
      color pix=video.pixels[loc];
      float b = brightness(pix);
      if (b>brightest){
        brightest=b;
        brightestX=x;
        brightestY=y;
      }
    }
  }
  video.updatePixels();
  pushMatrix();
  translate(width,0);
  scale(-1,1);
  image(video,0,0);
  popMatrix();
  ellipse(brightestX,brightestY,30,30);
}