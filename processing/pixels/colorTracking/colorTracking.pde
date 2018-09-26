import processing.video.*;
Capture video;
color trackColor;
int locX, locY;

void setup() {
  size(640, 480);
  video = new Capture(this, 640, 480, 30);
  video.start();
}

void draw() {
  if (video.available()) {
    video.read();
  }
  video.loadPixels();
  float dist=500;
  for (int y=0; y<height; y++) {
    for (int x=0; x<width; x++) {
      int loc = (video.width-x-1)+(y*width);
      color pix=video.pixels[loc];
      float r1=red(pix);
      float g1=green(pix);
      float b1=blue(pix);
      float r2=red(trackColor);
      float g2=green(trackColor);
      float b2=blue(trackColor);
      float diff=dist(r1,g1,b1,r2,g2,b2);
      
      if (diff<dist){
        dist=diff;
        locX=x;
        locY=y;
      }
    }
  }
  video.updatePixels();
  pushMatrix();
  translate(width,0);
  scale(-1,1);
  image(video,0,0);
  popMatrix();
  fill(trackColor);
  ellipse(locX,locY,30,30);
}

void mousePressed(){
  int loc=(video.width-mouseX-1)+(mouseY*width);
  trackColor=video.pixels[loc];
}