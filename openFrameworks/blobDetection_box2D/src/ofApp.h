#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxBox2d.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    
    ofVideoGrabber cam;
    ofxCv::RunningBackground background;
    ofxCv::ContourFinder contourFinder;
    ofImage thresholded, blurred;
    
    ofxPanel gui;
    ofParameter<bool> resetBackground;
    ofParameter<float> learningTime, thresholdValue;
    ofParameter<float> minArea, maxArea, contoursThreshold;
    ofParameter<bool> holes;
    ofParameter<int> radius;
    ofParameter<bool> useGaussian;
    
    ofxBox2d                             box2d;
    vector <shared_ptr<ofxBox2dCircle>>  circles;
    vector <shared_ptr<ofxBox2dEdge>>    edges;
};
