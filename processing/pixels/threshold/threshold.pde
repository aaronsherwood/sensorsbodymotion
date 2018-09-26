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
      if(brightness(source.pixels[loc])>map(mouseX,0,width,255,0))
        destination.pixels[loc]=color(255); 
      else
        destination.pixels[loc]=color(0);
    }
  }
  source.updatePixels();
  destination.updatePixels();
 
  image(destination, 0, 0);
}