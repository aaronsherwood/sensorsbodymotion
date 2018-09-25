import gab.opencv.*;
import org.opencv.imgproc.Imgproc;
import org.opencv.core.MatOfPoint2f;
import org.opencv.core.Point;
import org.opencv.core.Size;
import org.opencv.core.Mat;
import org.opencv.core.CvType;
import processing.video.*;
Capture video;
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
  video = new Capture(this, videoWidth, videoHeight);
  video.start();
  opencv = new OpenCV(this, video);
}

void draw() {
  background(0);
  if (video.available()) {
    video.read();
    opencv.loadImage(video);
    opencv.toPImage(warpPerspective(vectors, videoWidth, videoHeight), warped);
  }
  image(video, 0, 0);

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

  pushMatrix();
  translate(videoWidth, 0);
  image(warped, 0, 0);
  popMatrix();
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

Mat getPerspectiveTransformation(ArrayList<PVector> inputPoints, int w, int h) {
  Point[] canonicalPoints = new Point[4];
  canonicalPoints[0] = new Point(w, 0);
  canonicalPoints[1] = new Point(0, 0);
  canonicalPoints[2] = new Point(0, h);
  canonicalPoints[3] = new Point(w, h);

  MatOfPoint2f canonicalMarker = new MatOfPoint2f();
  canonicalMarker.fromArray(canonicalPoints);

  Point[] points = new Point[4];
  for (int i = 0; i < 4; i++) {
    points[i] = new Point(inputPoints.get(i).x, inputPoints.get(i).y);
  }
  MatOfPoint2f marker = new MatOfPoint2f(points);
  return Imgproc.getPerspectiveTransform(marker, canonicalMarker);
}

Mat warpPerspective(ArrayList<PVector> inputPoints, int w, int h) {
  Mat transform = getPerspectiveTransformation(inputPoints, w, h);
  Mat unWarpedMarker = new Mat(w, h, CvType.CV_8UC1);    
  Imgproc.warpPerspective(opencv.getColor(), unWarpedMarker, transform, new Size(w, h));
  return unWarpedMarker;
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