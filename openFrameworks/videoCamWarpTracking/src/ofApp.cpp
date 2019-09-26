#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
    cam.setup(640, 480);
    
    ofSetVerticalSync(true);
    warpedColor.allocate(640, 480, OF_IMAGE_COLOR);
    
    movingPoint = false;
    saveMatrix = false;
    homographyReady = false;
    settingNewPoints = false;
    
    destPoints.push_back(ofVec2f(0,0));
    destPoints.push_back(ofVec2f(warpedColor.getWidth(),0));
    destPoints.push_back(ofVec2f(warpedColor.getWidth(),warpedColor.getHeight()));
    destPoints.push_back(ofVec2f(0,warpedColor.getHeight()));
    
    srcPoints.push_back(ofVec2f(0+warpedColor.getWidth()+100,30));
    srcPoints.push_back(ofVec2f(warpedColor.getWidth()+warpedColor.getWidth()-100,30));
    srcPoints.push_back(ofVec2f(warpedColor.getWidth()+warpedColor.getWidth()-100,warpedColor.getHeight()-30));
    srcPoints.push_back(ofVec2f(0+warpedColor.getWidth()+100,warpedColor.getHeight()-30));
    
    // load the previous homography if it's available
    ofFile previous("homography.yml");
    if(previous.exists()) {
        FileStorage fs(ofToDataPath("homography.yml"), FileStorage::READ);
        fs["homography"] >> homography;
        homographyReady = true;

    }
    
    ofSetVerticalSync(true);
}

void ofApp::update() {
    cam.update();
    if(cam.isFrameNew()) {
        if(settingNewPoints) {
            vector<Point2f> sPoints, dPoints;
            for(int i = 0; i < destPoints.size(); i++) {
                sPoints.push_back(Point2f(srcPoints[i].x - warpedColor.getWidth(), srcPoints[i].y));
                dPoints.push_back(Point2f(destPoints[i].x, destPoints[i].y));
            }
            
            // generate a homography from the two sets of points
            homography = findHomography(Mat(sPoints), Mat(dPoints));
            homographyReady = true;
            
            if(saveMatrix) {
                FileStorage fs(ofToDataPath("homography.yml"), FileStorage::WRITE);
                fs << "homography" << homography;
                saveMatrix = false;
                settingNewPoints = false;
            }
        }
        
        if(homographyReady) {
            // this is how you warp one ofImage into another ofImage given the homography matrix
            // CV INTER NN is 113 fps, CV_INTER_LINEAR is 93 fps
            warpPerspective(cam, warpedColor, homography, CV_INTER_LINEAR);
            warpedColor.update();
        }
    }
}

void drawPoints(vector<ofVec2f>& points) {
    ofNoFill();
    for(int i = 0; i < points.size(); i++) {
        ofDrawCircle(points[i], 10);
        ofDrawCircle(points[i], 1);
    }
}

void ofApp::draw() {
    
    ofSetColor(255);
    cam.draw(warpedColor.getWidth(), 0);
    if(homographyReady) {
        warpedColor.draw(0, 0);
    }
    if (settingNewPoints){
        ofPushStyle();
        ofSetColor(ofColor::blue);
        drawPoints(srcPoints);
        ofSetColor(128);
        ofSetLineWidth(2);
        for(int i = 1; i < srcPoints.size(); i++) {
            ofDrawLine(srcPoints[i-1], srcPoints[i]);
        }
        ofDrawLine(srcPoints[srcPoints.size()-1], srcPoints[0]);
        ofPopStyle();
    }
    
    ofSetColor(255);
    string message = ofToString((int) ofGetFrameRate());
    message += "\nPress 'n' to set points\nPress 's' to save";
    ofDrawBitmapString(message, 10, 20);
}

bool ofApp::movePoint(vector<ofVec2f>& points, ofVec2f point) {
    for(int i = 0; i < points.size(); i++) {
        if(points[i].distance(point) < 20) {
            movingPoint = true;
            curPoint = &points[i];
            return true;
        }
    }
    return false;
}

void ofApp::mousePressed(int x, int y, int button) {
    ofVec2f cur(x, y);
    ofVec2f rightOffset(warpedColor.getWidth(), 0);
    movePoint(srcPoints, cur);
}

void ofApp::mouseDragged(int x, int y, int button) {
    if(movingPoint) {
        curPoint->set(x, y);
    }
}

void ofApp::mouseReleased(int x, int y, int button) {
    movingPoint = false;
}

void ofApp::keyPressed(int key) {
    if(key == 's') {
        saveMatrix = true;
    }
    if(key == 'n') {
        settingNewPoints = true;
    }
}
