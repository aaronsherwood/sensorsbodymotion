PImage source;
int increment=10;
void setup() {
  size(512, 512);
  source = loadImage("baboon.png");
  noStroke();
}

void draw() {
  background(0);
  source.loadPixels();
  for (int y=0; y<height; y+=increment) {
    for (int x=0; x<width; x+=increment) {
      int loc = x+(y*width);
      color pix=source.pixels[loc];
      fill(pix);
      ellipse(x,y,increment,increment);
    }
  }
  source.updatePixels();
  increment=constrain(mouseX,1,512);
}