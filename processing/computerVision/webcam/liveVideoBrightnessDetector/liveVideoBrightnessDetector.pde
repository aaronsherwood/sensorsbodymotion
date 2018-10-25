import processing.video.*;
Capture video;

float avgBrightness=0;

void setup() {
  size(640, 480);
  noStroke();
  video = new Capture(this, 640, 480, 30);
  video.start();
}

void draw() {
  background(255-avgBrightness);
  if (video.available()) {
    video.read();
  }
  video.loadPixels();
  avgBrightness=0;
  for (int y=0; y<height; y++) {
    for (int x=0; x<width; x++) {
      int loc = (video.width-x-1)+(y*width);
      color pix=video.pixels[loc];
      avgBrightness+=brightness(pix);
    }
  }
  avgBrightness/=video.pixels.length;
  video.updatePixels();
}