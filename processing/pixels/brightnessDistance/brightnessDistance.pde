PImage source, destination;

void setup() {
  size(512, 512);
  source = loadImage("baboon.png");
  destination = createImage(512, 512, RGB);
}

void draw() {
  source.loadPixels();
  destination.loadPixels();
  for (int y=0; y<height; y++) {
    for (int x=0; x<width; x++) {
      int loc = x+(y*width);
      float r = red(source.pixels[loc]);
      float g = green(source.pixels[loc]);
      float b = blue(source.pixels[loc]);
      float distance=dist(x,y,mouseX,mouseY);
      float adjustBrightness = (50-distance)/50;//((float) mouseX / width) * 8.0;
      r*=adjustBrightness;
      g*=adjustBrightness;
      b*=adjustBrightness;
      r=constrain(r, 0, 255);
      g=constrain(g, 0, 255);
      b=constrain(b, 0, 255);
      destination.pixels[loc]=color(r, g, b);
    }
  }
  source.updatePixels();
  destination.updatePixels();
  image(destination, 0, 0);
}