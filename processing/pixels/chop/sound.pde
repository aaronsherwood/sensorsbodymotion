import processing.sound.*;

float oFreq=midiToFreq(95);
float freq=oFreq;
float amp=0.0;
SinOsc sine;
TriOsc tri;

PinkNoise noise;
Env env, env1, env2, env3; 
float attackTime = 0.001;
float sustainTime = 0.004;
float sustainLevel = 0.3;
float releaseTime = 0.2;

int speed=105;
int oSpeed = speed;
int trigger;
boolean play=false;
SoundFile soundfile;
int counter = 0;

boolean go =false;

void initialize() {
  sine = new SinOsc(this);
  tri = new TriOsc(this);
  noise = new PinkNoise(this);
  noise.amp(.15);
  trigger=millis();
  env  = new Env(this);
  env1  = new Env(this);
  env2  = new Env(this);
  env3  = new Env(this);
}

void rhythm() {
  if (counter==0) {
    freq=oFreq;
  }
  if (millis()>trigger) {
    play=true;
    trigger=millis()+speed;
    if(counter==0){
      if (go)
     speed-=10;
     if(speed<10) exit();
    }
    if (counter%2==0) {
      //sine.play(midiToFreq(31), 5);
      //env.play(sine, attackTime, sustainTime, sustainLevel, releaseTime); 
    }
    if (counter%(int)random(1, 5)==0) {
      //sine.play(freq, .08);
      //env1.play(sine, attackTime, sustainTime, sustainLevel, releaseTime);
      //noise.play();
      //env1.play(noise, attackTime, sustainTime, sustainLevel, releaseTime);
    }
    if (counter%3==0) {
      //tri.play(100, 1);
      //env2.play(tri, attackTime, sustainTime, sustainLevel, releaseTime);
    }
    freq-=5;
    counter=(counter+1)%32;
  }
  println(speed);
}

float midiToFreq(int note){
    return (pow(2, ((note-69)/12.0)))*440; 
}

void mousePressed(){
 go=true; 
}