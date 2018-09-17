import processing.sound.*;
int trackAmount = 5;

SoundFile[] soundfiles = new SoundFile[trackAmount];
float[] volumes = new float[trackAmount];
float[] volumeDestinations = new float[trackAmount];

//No need to edit:
PFont myFont, myBigFont;
final int myHeight = 400;
final int myWidth = 400;
int frameNum = 0;
int currentHue = 100;
int currentTextHue = 255;
String currentMessage = "";

//all included soundfiles are 120bpm

void setup() {
  colorMode(HSB);
  size(400, 400, P3D);
  smooth();
  background(255);

  myFont = createFont("Arial", 14);
  myBigFont = createFont("Arial", 80);
  for (int i=0; i<soundfiles.length; i++) {
    String name = "soundfile";
    name+=str(i);
    name+=".wav";
    println(name);
    soundfiles[i] = new SoundFile(this, name);
    soundfiles[i].loop();
    soundfiles[i].amp(0);
    volumes[i]=0;
    volumeDestinations[i]=0;
  }
}

void draw() {
  frameRate(30);
  background(currentHue, 255, 255);
  drawText();

  boolean stillPlaying = false;
  for (int i=0; i<soundfiles.length; i++) {
    //set volume
    volumes[i]=smoothing(volumes[i], volumeDestinations[i]);
    soundfiles[i].amp(volumes[i]);
    //continuously fade volume out
    volumeDestinations[i]-=.1;
    //constrian the fade out to 0
    volumeDestinations[i] = constrain(volumeDestinations[i],0,1);
    //check to see if any sound is still playing
    if (volumeDestinations[i]>0)
      stillPlaying = true;
  }
  //if nothing is playing remove the track number on the screen
  if (!stillPlaying){
    currentMessage = "";
  }
}

//see what section the of the screen the mouse is
//set the message and play the track
void mouseMoved(){
  int track = 0;
  if (mouseX<width/5)
    track = 1;
  else if (mouseX<(width/5)*2)
    track = 2;
  else if (mouseX<(width/5)*3)
    track = 3;
  else if (mouseX<(width/5)*4)
    track = 4;
  else if (mouseX<width)
    track = 5;
  showMessage(track);
  changeTracks(track);
}

void showMessage(int i) {
  currentHue = (int)generateColor(i);
  currentTextHue = (int)generateColor((i+1));
  currentMessage = Integer.toString(i);
}

//Write instructions to screen.
void drawText() {
  stroke(0);
  textFont(myFont);
  textAlign(LEFT, TOP); 
  fill(currentTextHue, 255, 255);

  text("Move mouse horizontally to make sound", 10, 10);

  textFont(myBigFont);
  text(currentMessage, 190, 180);
}


float generateColor(int which) {
  float f = 100; 
  int i = which;
  if (i <= 0) {
    return 100;
  } else {
    return (generateColor(which-1) + 1.61*255) %255;
  }
}

void changeTracks(int which) {
  //playing only one sound at a time
  for (int i=0; i<soundfiles.length; i++) {
    volumeDestinations[i]=0;
  }
    volumeDestinations[which-1]=1;
}

float smoothing(float current, float destination) {
  current += (destination-current)*.5;
  return current;
}