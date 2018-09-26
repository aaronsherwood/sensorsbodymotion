PImage img;

void setup() {
  size(640, 640);
  img = loadImage("nyuad.jpg");
  imageMode(CENTER);
  background(img);
  initialize();
}

void draw() {
  rhythm();
  if (counter<4) background(img);
  else if (play) {
    for (int i=0; i<5; i++) {
      PImage section = img.get((int)random(width), (int)random(height), (int)random(width), (int)random(height));
      image(section, random(width), random(height), random(width), random(height));
    }
    play=false;
  } 
}