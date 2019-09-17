#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
    ofBackground(0);
    
    camera.setup(320, 240);
    
    gui.setup();
   
    gui.add(fbPyrScale.set("fbPyrScale", .5, 0, .99));
    gui.add(fbLevels.set("fbLevels", 4, 1, 8));
    gui.add(fbIterations.set("fbIterations", 2, 1, 8));
    gui.add(fbPolyN.set("fbPolyN", 7, 5, 10));
    gui.add(fbPolySigma.set("fbPolySigma", 1.5, 1.1, 2));
    gui.add(fbWinSize.set("winSize", 32, 4, 64));
    
    for (int i=0; i<NUMMOVERS; i++){
        movers[i] = Mover(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),ofRandom(1, 4));
    }
}

void ofApp::update(){
    camera.update();
    
    if(camera.isFrameNew()) {
        fb.setPyramidScale(fbPyrScale);
        fb.setNumLevels(fbLevels);
        fb.setWindowSize(fbWinSize);
        fb.setNumIterations(fbIterations);
        fb.setPolyN(fbPolyN);
        fb.setPolySigma(fbPolySigma);
        fb.calcOpticalFlow(camera);
        
    }
    
    for (int i=0; i<NUMMOVERS; i++){
        ofVec2f f = fb.getFlowOffset(
             // the flow is in the same dimensions of the camera, so need to map from rect pos. to flow pos.
             ofMap(movers[i].position.x,0,ofGetWidth(),0,fb.getWidth()),
             ofMap(movers[i].position.y,0,ofGetHeight(),0,fb.getHeight())
        );
        movers[i].applyForces(f);
        movers[i].update();
    }
}

void ofApp::draw(){
    ofPushMatrix();
    camera.draw(0,0,ofGetWidth(),ofGetHeight());
    fb.draw(0,0,ofGetWidth(),ofGetHeight());
    ofDrawBitmapStringHighlight(ofToString((int) ofGetFrameRate()) + "fps", 970, 20);
    ofPopMatrix();
    
    for (int i=0; i<NUMMOVERS; i++){
        movers[i].display();
    }
    
    gui.draw();
}
