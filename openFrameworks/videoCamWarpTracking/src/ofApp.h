#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void drawPoints(vector<ofVec2f>& points);
    bool movePoint(vector<ofVec2f>& points, ofVec2f point);
    void mousePressed(int x, int y, int button);
    void mouseDragged(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void keyPressed(int key);
    
    ofxCvColorImage warped;
    vector<ofVec2f> destPoints, srcPoints;
    bool movingPoint;
    ofVec2f* curPoint;
    bool saveMatrix;
    bool homographyReady;
    bool settingNewPoints;
    int currentPoint;
    
    cv::Mat homography;
    ofVideoGrabber cam;
};
