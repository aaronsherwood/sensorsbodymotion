void setup() {
  size(640, 640);
}

void draw() {
  loadPixels();
  for (int y=0; y<height; y++) {
    for (int x=0; x<width; x++) {
      float n = noise(x*.005, y*.005);
      pixels[x+y*width]=color(n*255);
    }
  }
  updatePixels();
}