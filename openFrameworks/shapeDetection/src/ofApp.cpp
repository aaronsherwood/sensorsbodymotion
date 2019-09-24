#include "ofApp.h"

/*
 INSTRUCTIONS
 Draw in the window to test shapes
 Click space bar to erase shape
 */


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(false);
    fbo.allocate(300,300);
    fbo.begin();
    ofClear(0,0,0,255);
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPixels pix;
    fbo.readToPixels(pix);
    cvs.update(pix); // this is the important part, you need to send in ofPixels to cvs.update
    fbo.draw(0,0);
    ofDrawBitmapStringHighlight(cvs.getLabel(),220,20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' '){
        fbo.begin();
        ofClear(0,0,0,255);
        fbo.end();
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    fbo.begin();
    ofSetColor(ofColor::red);
    ofDrawRectangle(x,y,10,10);
    fbo.end();
}
