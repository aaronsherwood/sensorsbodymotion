//use the fiducials in the fiducialUsed.jpg file
//this sketch will track those 4 markers

import processing.video.*;
import jp.nyatla.nyar4psg.*;

Capture cam;
MultiMarker nya;

PGraphics pg;

PVector locs[] = new PVector[4];

boolean debug=false;
float smoothValue = .3;

void setup() {
  size(640, 480, P3D);
  colorMode(RGB, 100);
  println(MultiMarker.VERSION);
  cam=new Capture(this, 640, 480);
  nya=new MultiMarker(this, width, height, "camera_para.dat", NyAR4PsgConfig.CONFIG_PSG);
  //second arg is actual size of marker in mm, i think
  nya.addNyIdMarker(0, 80);//id=0
  nya.addNyIdMarker(1, 80);//id=1
  nya.addNyIdMarker(2, 80);//id=2
  nya.addNyIdMarker(3, 80);//id=3
  cam.start();
  pg = createGraphics(width, height);
  //draw in pgraphics (this can be in draw loop!)
  pg.beginDraw();
  pg.clear();
  pg.fill(233, 224 , 71);
  pg.strokeWeight(7);
  pg.ellipse(250, 250, 300 ,300);
  pg.fill(0);
  pg.ellipse(200, 210 , 30, 70);
  pg.fill(0);
  pg.ellipse(300, 210 , 30, 70);
  pg.fill (255);
  pg.bezier(150, 295, 200, 370, 300, 370, 350, 295);
  pg.line(150, 295, 350, 295);
  pg.line(160, 180, 210, 135);
  pg.line(340, 100, 290,75 );
  pg.endDraw();

  for (int i=0; i<4; i++) {
    locs[i] = new PVector(0, 0);
  }
  noStroke();
  textureMode(NORMAL);
}

void draw()
{
  if (cam.available() !=true) {
    return;
  }
  cam.read();
  nya.detect(cam);
  background(0);
  nya.drawBackground(cam);
  //make sure there are enough markers found
  boolean pointPresent[] = {true, true, true, true};
  int testIndex = 3;
  for (int i=0; i<4; i++) {
    if ((!nya.isExist(i))) {
      pointPresent[i]=false;
      testIndex--;
      continue;
    }
    //smooth the transition if points are lost
    //lower value is more smoothing/delay
    locs[i].add(PVector.sub(nya.object2ScreenCoordSystem(i, 0, 0, 0), locs[i]).mult(smoothValue));
    if (debug) {
      rectMode(CENTER);
      rect(locs[i].x, locs[i].y, 20, 20);
    }
  }

  //only draw if a marker is present
  if (testIndex>=0) {
    //i think it works better without this
    //altCoord(pointPresent); //if some point is not there use a neighboring point for the loc

    //draw a polygon
    beginShape();
    //use the pgraphics as a texture for the polygon
    texture(pg);
    //winding order starts upper left and goes clockwise
    //marker id's are placed like this:
    //0 1
    //2 3
    //so winding order is marker ids 0, 1, 3, 2
    vertex(locs[0].x, locs[0].y, 0, 0);
    vertex(locs[1].x, locs[1].y, 1, 0);
    vertex(locs[3].x, locs[3].y, 1, 1);
    vertex(locs[2].x, locs[2].y, 0, 1);
    endShape();
  }
}

void altCoord(boolean pointPresent[]) {
  //have built in a somewhat safeguard, if some point is not there use a neighboring point for the loc
  //smooth to that location
  if (!pointPresent[0]) {
    PVector dest = new PVector(locs[2].x, locs[1].y);
    locs[0].add(PVector.sub(dest, locs[0]).mult(smoothValue));
  }
  if (!pointPresent[1]) {
    PVector dest = new PVector(locs[3].x, locs[0].y);
    locs[0].add(PVector.sub(dest, locs[0]).mult(smoothValue));
  }
  if (!pointPresent[2]) {
    PVector dest = new PVector(locs[0].x, locs[3].y);
    locs[0].add(PVector.sub(dest, locs[0]).mult(smoothValue));
  }
  if (!pointPresent[3]) {
    PVector dest = new PVector(locs[1].x, locs[2].y);
    locs[0].add(PVector.sub(dest, locs[0]).mult(smoothValue));
  }
}