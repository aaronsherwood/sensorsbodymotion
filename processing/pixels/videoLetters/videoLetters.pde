import processing.video.*;

String quotes;
Capture video;
PFont f;
int increment=20;

void setup() {
  size(640, 480);
  noStroke();
  video = new Capture(this, 640, 480, 30);
  video.start();
  String q[]=loadStrings("einstein.txt");
  f= createFont("Monaco",32);
  quotes="";
  for (int i=0; i<q.length;i++){
   quotes+=q[i]; 
  }
  println(quotes.length());
}

void draw() {
  background(0);
  if (video.available()) {
    video.read(); 
  }
  int letterIndex=0;
  video.loadPixels();
    for (int y=0; y<height; y+=increment) {
      for (int x=0; x<width; x+=increment) {
        int loc = (video.width-x-1)+(y*width);
        color pix=video.pixels[loc];
        float dims=brightness(pix);
        dims=increment*(dims/255);
        fill(pix);
        textAlign(CENTER);
        textFont(f,dims*2);
        text(quotes.charAt(letterIndex),x,y);
        letterIndex++;
        if(letterIndex>=quotes.length())
          letterIndex=0;
      }
    }
    video.updatePixels();
    increment=(int)map(mouseX,0,width,5,50);
}