void cv() {
  opencv.loadImage(ps3eye.getFrame());
  opencv.threshold(30);
  opencv.setGray(warpPerspective(vectors, videoWidth, videoHeight));
  opencv.toPImage(warpPerspective(vectors, videoWidth, videoHeight), warped);
  opencv.contrast(30);
  opencv.dilate();
  opencv.erode();
  opencv.blur(50);
  //image(opencv.getSnapshot(), 0, 0); 
  noFill();
  stroke(255, 0, 0);
  strokeWeight(3);
  pushMatrix();
  translate(videoWidth, 0);
  //image(warped, 0, 0);

  for (Contour contour : opencv.findContours()) {
    
    Rectangle r = contour.getBoundingBox();
    if (//(contour.area() > 0.9 * src.width * src.height) ||
      (r.width < blobSizeThreshold || r.height < blobSizeThreshold))
      continue;
    contour.draw();
    stroke(255, 0, 0);
    fill(255, 0, 0, 150);
    strokeWeight(2);
    rect(r.x, r.y, r.width, r.height);
    x = (float)r.getCenterX();
    y = (float)r.getCenterY();
    ellipse(x, y, 5, 5);
  }
  popMatrix();
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
  Imgproc.warpPerspective(opencv.getGray(), unWarpedMarker, transform, new Size(w, h));
  return unWarpedMarker;
}