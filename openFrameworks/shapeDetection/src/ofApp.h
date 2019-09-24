#pragma once

#include "ofMain.h"

#include "ofMain.h"
#include "ofxCv.h"
#include "cvshape.hpp"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void mouseDragged(int x, int y, int button);
    
    CVShape cvs;
    ofFbo fbo;
};

