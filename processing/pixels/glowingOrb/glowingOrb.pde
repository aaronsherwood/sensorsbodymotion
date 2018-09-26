void setup() {
  size(640, 640);
}

void draw() {
  loadPixels();
  for (int y=0; y<height; y++) {
    for (int x=0; x<width; x++) {
      float d = dist(x, y, mouseX, mouseY); // just change from this abs(y-mouseY) for circle
      if (d>0)d=1/d; //don't divide by zero
      else d=1;
      float radius = .015; //number between 0 & 1 mostly, smaller is larger size
      d = map(d, 0, radius, 0, 255);
      pixels[x+y*width]=color(d*.9, d*.5, d*.3);
    }
  }
  updatePixels();
}