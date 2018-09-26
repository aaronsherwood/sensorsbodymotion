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
    for (int x=1; x<width; x++) {
      int loc = x+(y*width);
      int leftLoc = (x-1)+(y*width);
      color pix=source.pixels[loc];
      color leftPix=source.pixels[leftLoc];
      float diff=abs(brightness(pix)-brightness(leftPix));
      destination.pixels[loc]=color(diff);
    }
  }
  source.updatePixels();
  destination.updatePixels();

  image(destination, 0, 0);
}