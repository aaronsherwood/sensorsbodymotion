PImage source;
int increment=10;
void setup() {
  size(512, 512);
  source = loadImage("baboon.png");
  noStroke();
}

void draw() {
  background(255);
  source.loadPixels();
  for (int y=0; y<height; y+=increment) {
    for (int x=0; x<width; x+=increment) {
      int loc = x+(y*width);
      color pix=source.pixels[loc];
      float dims=brightness(pix);
      dims=increment*(dims/255);
      fill(0);
      rect(x,y,dims,dims);
    }
  }
  source.updatePixels();
  increment=(int)map(mouseX,0,width,5,50);
}