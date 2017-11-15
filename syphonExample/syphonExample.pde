import codeanticode.syphon.*;
import com.thomasdiewald.ps3eye.PS3EyeP5;

PS3EyeP5 ps3eye;

SyphonServer server;

void settings() {
  size(640,360, P3D);
  PJOGL.profile=1;
}

void setup() {
  // Create syhpon server to send frames out.
  server = new SyphonServer(this, "Processing Syphon");
  ps3eye = PS3EyeP5.getDevice(this);
  // start capturing with 60 fps (default)
  ps3eye.start();
  
  // if "false" Processing/PS3Eye frameRates are not "synchronized".
  // default value is "true".
  // ps3eye.waitAvailable(false); 
  
  frameRate(1000);
}

void draw() {
  image(ps3eye.getFrame(), 0, 0);
  server.sendScreen();
}