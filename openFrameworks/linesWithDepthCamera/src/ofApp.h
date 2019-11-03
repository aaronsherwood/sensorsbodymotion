#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxRSSDKv2.h"
#include "ofxCv.h"

using namespace ofxRSSDK;

//#define USE_KINECT
#define USE_REALSENSE

enum {THRESHOLD, CLOSEST, AVERAGE };


class ofApp : public ofBaseApp {
public:
    
    void setup();
    void update();
    void draw();
    void exit();
    
    void closestPoint();
    void averageDepth();
    void threshold();
    void drawLines();
    
    void keyPressed(int key);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    
#ifdef USE_KINECT
    ofxKinect kinect;
#endif
    
#ifdef USE_REALSENSE
    RSDevicePtr	realSense;
#endif
    
    
    ofxCvColorImage colorImg;
    
    ofxCvGrayscaleImage grayImage; // grayscale depth image
    ofxCvContourFinder contourFinder;
    
    int nearThreshold;
    int farThreshold;
    
    float trackingX, trackingY;
    
    int trackingMode;
    int depthWidth, depthHeight;
    
    bool debug;
    
    int tileCount = 20;
    float tileWidth;
    float tileHeight;
    float shapeSize = 50;
    float newShapeSize = shapeSize;
    float shapeAngle = 0;
    float maxDist;
    int sizeMode = 0;
};
