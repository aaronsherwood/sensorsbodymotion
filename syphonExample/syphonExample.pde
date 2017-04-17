PGraphics canvas;

void setup() {
  size(400,400, P3D);
  canvas = createGraphics(400, 400, P3D);
  canvas.smooth(4);
  setupSyphonServer("Syphon Test");
}

void draw() {
  canvas.beginDraw();
  canvas.background(255);
  canvas.ellipse(mouseX,mouseY,30,30);
  canvas.endDraw();
  image(canvas,0,0);
  server.sendImage(canvas);
}
