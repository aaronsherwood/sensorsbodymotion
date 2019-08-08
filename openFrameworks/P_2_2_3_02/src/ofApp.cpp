#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // init shape
    centerX = ofGetWindowWidth() / 2;
    centerY = ofGetWindowHeight() / 2;
    float angle = glm::radians(360 / formResolution);
    for (int i = 0; i < formResolution; i++) {
        x.push_back(cos(angle * i) * initRadius);
        y.push_back(sin(angle * i) * initRadius);
    }
    
    ofSetColor(0, 50);
    ofSetLineWidth(0.75);
    ofNoFill();
    ofBackground(255);
    ofSetBackgroundAuto(false);
    ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){
    // floating towards mouse position
    centerX += (ofGetMouseX() - centerX) * 0.01;
    centerY += (ofGetMouseY() - centerY) * 0.01;
    
    // calculate new points
    for (int i = 0; i < formResolution; i++) {
        x[i] += ofRandom(-stepSize, stepSize);
        y[i] += ofRandom(-stepSize, stepSize);
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBeginShape();
    // start controlpoint
    ofCurveVertex(x[formResolution - 1] + centerX, y[formResolution - 1] + centerY);
    
    // only these points are drawn
    for (int i = 0; i < formResolution; i++) {
        ofCurveVertex(x[i] + centerX, y[i] + centerY);
    }
    ofCurveVertex(x[0] + centerX, y[0] + centerY);
    
    // end controlpoint
    ofCurveVertex(x[1] + centerX, y[1] + centerY);
    ofEndShape(true);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
