void setup() {
  size(600, 600);
}

void draw() {
  background(255);
  noFill();
  //get vectors of our mouse and center locations
  PVector mouse = new PVector(mouseX, mouseY);
  PVector center = new PVector(width/2, height/2);

  //draw circles at those lcoations
  ellipse(center.x, center.y, 300, 300);
  ellipse(mouse.x, mouse.y, 30, 30);

  //get a vector pointing between the mouse and the center
  PVector lineBetween = PVector.sub(mouse, center);
  //get the angle of that vector
  float angle = lineBetween.heading();
  println(angle);
  //get the distance of the mouse from the center
  float distance = lineBetween.mag();

  //move coordinate system to center 
  //so we can rotate a line based on our angle
  translate(center.x, center.y);
  
  //example just showing how to convert from 360 degrees to radians 
  float myAngle = radians(30);
  
  //built in variables
  //println(TWO_PI + " " + PI + " " + HALF_PI);
  
  //actually rotate our line using our angle
  rotate(angle);
  line(0, 0, 150, 0);
}