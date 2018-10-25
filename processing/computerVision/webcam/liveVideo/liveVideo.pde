import processing.video.*;

Capture video;

void setup() {
  size(640, 480);
  noStroke();
  video = new Capture(this, 640,480,30);
  video.start();
}

void draw() {
  background(255);
  if (video.available()){
   video.read(); 
  }
  image(video,0,0);
}