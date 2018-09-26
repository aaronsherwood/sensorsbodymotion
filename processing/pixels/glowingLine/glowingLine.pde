void setup() {
  size(640, 640);
}

void draw() {
  loadPixels();
  for (int y=0; y<height; y++) {
    for (int x=0; x<width; x++) {
      float d = abs(y-mouseY);
      if (d>0)d=1/d; 
      else d=1;
      float lineWidth = .2; //number between 0 & 1 mostly, smaller is larger size
      d = map(d, 0, lineWidth, 0, 255);
      pixels[x+y*width]=color(d*.9, d*.5, d*.3);
    }
  }
  updatePixels();
}