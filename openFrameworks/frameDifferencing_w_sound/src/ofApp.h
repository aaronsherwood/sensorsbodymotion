#pragma once

#include "ofMain.h"
#include "ofxCv.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    
    ofVideoGrabber cam;
    ofPixels previous;
    ofImage thresh, diff;
    cv::Mat columnMean;
    ofSoundPlayer  sound1, sound2;
    float thresholdValue;
    bool section1Triggered, section2Triggered;
    ofTrueTypeFont font;
};
