import gab.opencv.*;
import org.opencv.imgproc.Imgproc;
import org.opencv.core.MatOfPoint2f;
import org.opencv.core.Point;
import org.opencv.core.Size;
import org.opencv.core.Mat;
import org.opencv.core.CvType;
import processing.video.*;
import com.thomasdiewald.ps3eye.PS3EyeP5;
import java.awt.Rectangle;
PS3EyeP5 ps3eye;
import oscP5.*;
import netP5.*;
float x, y;

OscP5 oscP5;
NetAddress dest;

OpenCV opencv;
JSONObject json;
PImage warped;
int videoWidth = 640;
int videoHeight = 480;
Mat transform;
ArrayList<PVector> vectors = new ArrayList<PVector>();
int pointCounter = 0;
boolean recording=false;


void setup() {
  size(1280, 480);

  warped = createImage(videoWidth, videoHeight, ARGB); 
  loadData();
  ps3eye = PS3EyeP5.getDevice(this);
  ps3eye.start();
  opencv = new OpenCV(this, 640, 480);
  oscP5 = new OscP5(this, 1234);
  dest = new NetAddress("127.0.0.1", 12000);
  x = 640/2;
  y = 480/2;
  opencv.startBackgroundSubtraction(50, 3, 0.5);
}

void draw() {
  background(0);
  image(ps3eye.getFrame(), 0, 0);  




  for (int i=0; i<4; i++) {
    PVector p = vectors.get(i);
    stroke(255, 0, 0);
    if (i<3) {
      PVector pNext = vectors.get(i+1);
      line(p.x, p.y, pNext.x, pNext.y);
    } else {
      PVector pBegin = vectors.get(0);
      line(p.x, p.y, pBegin.x, pBegin.y);
    }
    fill(255, 0, 0, 75);
    ellipse(p.x, p.y, 20, 20);
  }

  cv();
  fill(255);
  text("Press r to record a new set of points.", 20, 20);
  text("Start in the upper right of where you want to map, and go counter clockwise.", 20, 40);
  fill(255, 0, 0);
  if (recording) {
    String str = "RECORDING! Location: ";
    switch(pointCounter) {
    case 0: 
      str+=("Upper Right");
      break;
    case 1: 
      str+=("Upper Left");
      break;
    case 2: 
      str+=("Bottom Left");
      break;
    case 3: 
      str+=("Bottom Right");
      break;
    }
    text(str, 20, 60);
  }
  sendOsc();
}

void mousePressed() {
  if (mouseX<videoWidth && mouseY<videoHeight) {
    if (recording) {
      PVector p = vectors.get(pointCounter);
      p.x=mouseX;
      p.y=mouseY;
      JSONArray coordsData = json.getJSONArray("coords");
      JSONObject coord = coordsData.getJSONObject(pointCounter); 
      JSONObject position = coord.getJSONObject("position");
      position.setInt("x", mouseX);
      position.setInt("y", mouseY);
      pointCounter++;
    }
    if (pointCounter==4) {
      saveJSONObject(json, "data/coords.json");
      loadData();
      println("SAVED!");
      recording=false;
    }
  }
}

void keyPressed() {
  if (key=='r') {
    pointCounter=0; 
    recording=!recording;
  }
}

void sendOsc() {
  OscMessage msg = new OscMessage("/irMapped");
  msg.add(x); 
  msg.add(y);
  oscP5.send(msg, dest);
}

void loadData() {
  json = loadJSONObject("coords.json");
  JSONArray coordsData = json.getJSONArray("coords");
  for (int i = 0; i < coordsData.size(); i++) {
    // Get each object in the array
    JSONObject coord = coordsData.getJSONObject(i); 
    // Get a position object
    JSONObject position = coord.getJSONObject("position");
    // Get x,y from position
    int x = position.getInt("x");
    int y = position.getInt("y");
    vectors.add(new PVector(x, y, 0.0));
  }
}