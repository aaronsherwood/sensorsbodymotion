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
    

    mover = Mover(ofGetWidth()/2,ofGetHeight()/2,ofRandom(1, 4));
    shader.load("shader");
    ofEnableBlendMode(OF_BLENDMODE_ADD);
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
    
    ofVec2f f = fb.getAverageFlow();
    f*=7; //scale the force up a little
    mover.applyForces(f);
    mover.update();

}

void ofApp::draw(){

    camera.draw(0,0,ofGetWidth(),ofGetHeight());
    
    shader.begin();
    shader.setUniform2f("loc", ofVec2f(mover.position.x, ofGetHeight()-mover.position.y) );
    // the shader 'draws' on this rectangle
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();
    
    gui.draw();
}
