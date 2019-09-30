#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "Mover.hpp"

#define NUMMOVERS 300

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    ofVideoGrabber camera;
    
    ofxCv::FlowFarneback fb;

    ofxPanel gui;
    ofParameter<float> fbPyrScale, fbPolySigma;
    ofParameter<int> fbLevels, fbIterations, fbPolyN, fbWinSize;
    
    Mover mover;
    ofShader shader;
};

