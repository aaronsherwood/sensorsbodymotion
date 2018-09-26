import processing.video.*;

Capture video;

int increment=10;

void setup() {
  size(640, 480);
  noStroke();
  video = new Capture(this, 640, 480, 30);
  video.start();
}

void draw() {
  background(0);
  if (video.available()) {
    video.read(); 
  }
  video.loadPixels();
    for (int y=0; y<height; y+=increment) {
      for (int x=0; x<width; x+=increment) {
        int loc = (video.width-x-1)+(y*width);
        color pix=video.pixels[loc];
        float dims=brightness(pix);
        dims=increment*(dims/255);
        fill(255);
        rect(x, y, dims, dims);
      }
    }
    video.updatePixels();
    increment=(int)map(mouseX, 0, width, 5, 50);
}