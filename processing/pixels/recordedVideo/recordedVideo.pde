import processing.video.*;
Movie video;

void setup() {
  size(320, 240);
  noStroke();
  video = new Movie(this, "dancer.mov");
  video.loop();
}

void draw() {
  background(0);
  if (video.available()) {
    video.read();
  }
  image(video, 0, 0);
}