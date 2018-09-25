//In this example we'll draw an image and a circle over that image into
//an offscreen PGraphics buffer
//You of course can substitute the picture for your kinect feed
//and then send that pg image into OpenCV for computer vision

PGraphics pg; //this is our offscreen buffer
PImage img;

void setup() {
  size(640, 480);
  pg = createGraphics(640, 480); //create our offscreen buffer
  img = loadImage("street.jpg"); //dummy image just for example
}

void draw() {
  background(255);
  pg.beginDraw(); //start drawing into our PGraphics buffer
    pg.background(0); //everything that is being drawn in the buffer needs to start with pg.
    pg.image(img, 0, 0, width, height);
    pg.fill(0);
    pg.ellipse(width/2, height/2, 100, 100);
  pg.endDraw();//stop drawing into our buffer
  
  //draw our buffer on screen if we want
  //instead of this you could send this buffer into opencv every frame via: 
  //opencv.loadImage(pg); 
  //comment the line out below to see how nothing will draw to the screen without it
  image(pg,0,0);
}