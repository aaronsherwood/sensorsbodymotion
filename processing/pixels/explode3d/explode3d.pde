PImage source;
int cellSize=2;
int columns, rows;
void setup() {
  size(512, 512, P3D);
  source = loadImage("baboon.png");
  noStroke();
  columns=width/cellSize;
  rows=height/cellSize;
}

void draw() {
  background(255);
  source.loadPixels();
  for (int i=0; i<columns; i++) {
    for (int j=0; j<rows; j++) {
      int x= i*cellSize+cellSize/2;
      int y= j*cellSize+cellSize/2;
      int loc = x+(y*width);
      color pix=source.pixels[loc];
      float z=map(brightness(pix), 0, 255, 0, mouseX);
      pushMatrix();
      translate(x,y,z);
      fill(pix);
      rectMode(CENTER);
      rect(0,0,cellSize,cellSize);
      popMatrix();
    }
  }
  source.updatePixels();
}