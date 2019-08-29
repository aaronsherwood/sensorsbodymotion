#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofNoFill();
    ofSetLineWidth(3);
    moduleColor = ofColor(0, 0, 0, moduleAlpha);
    ofBackground(255);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(moduleColor);
    
    for (int gridY = 0; gridY < ofGetWidth(); gridY += 25) {
        for (int gridX = 0; gridX < ofGetHeight(); gridX += 25) {
            float diameter = ofDist(mouseX, mouseY, gridX, gridY);
            diameter = diameter / maxDistance * 40;
            diameter = ofClamp(diameter, 5, 1000);
            ofPushMatrix();
            ofTranslate(gridX, gridY, diameter * 5);
            ofDrawRectangle(0, 0, diameter, diameter); // also nice: ellipse(...)
            ofPopMatrix();
        }
    }

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
