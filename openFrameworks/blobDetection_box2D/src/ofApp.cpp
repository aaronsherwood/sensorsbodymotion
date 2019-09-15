#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
    cam.setup(640, 480);
    
    gui.setup();
    gui.add(resetBackground.set("Reset Background", false));
    gui.add(learningTime.set("Learning Time", 3000, 0, 3000));
    gui.add(thresholdValue.set("Threshold Value", 50, 0, 255));
    gui.add(minArea.set("Min area", 10, 1, 100));
    gui.add(maxArea.set("Max area", 200, 1, 500));
    gui.add(contoursThreshold.set("Contours Threshold", 128, 0, 255));
    gui.add(holes.set("Holes", false));
    gui.add(useGaussian.set("Use Gaussian", false));
    gui.add(radius.set("Radius", 30, 0, 100));
    
    // can play different ways of differencing
    //background.setDifferenceMode(ofxCv::RunningBackground::DARKER);
    
    // Box2d
    box2d.init();
    box2d.setGravity(0, 30);
    box2d.createGround();
    box2d.setFPS(60.0);
}

void ofApp::update() {
    cam.update();
    // get a new background
    if(resetBackground) {
        background.reset();
        resetBackground = false;
    }
    if(cam.isFrameNew()) {
        // set background update values
        background.setLearningTime(learningTime);
        background.setThresholdValue(thresholdValue);
        
        // do blurring
        ofxCv::copy(cam, blurred);
        if(useGaussian) {
            ofxCv::GaussianBlur(blurred, radius);
        } else {
            ofxCv::blur(blurred, radius);
        }
        blurred.update();
        
        // send blurred image into background subtraction
        // blurring should happen before thresholding (which happens inside the background.update)
        background.update(blurred, thresholded);
        thresholded.update();
        
        // find the contours
        contourFinder.setMinAreaRadius(minArea);
        contourFinder.setMaxAreaRadius(maxArea);
        contourFinder.setThreshold(contoursThreshold);
        contourFinder.findContours(thresholded);
        contourFinder.setFindHoles(holes);
    }
    
    // clear all the edges from last frame
    edges.clear();
    
    // get the contours as polylines
    auto contours = contourFinder.getPolylines();
    if (contours.size()>0){
        // loop through all the contours
        for (auto c : contours){
            auto edge = make_shared<ofxBox2dEdge>();
            
            // remove some points from the polyline
            c.simplify();
            
            // loop through all points in the polyline
            for (int i=0; i<c.size(); i++) {
                edge->addVertex(c[i]);
            }
            
            // add the edge
            edge->create(box2d.getWorld());
            edges.push_back(edge);
        }
    }
    
    
    // add some circles every so often
    if((int)ofRandom(0, 10) == 0) {
        auto c = make_shared<ofxBox2dCircle>();
        c->setPhysics(0.2, 0.2, 0.002);
        c->setup(box2d.getWorld(), ofRandom(300, 350), -20, ofRandom(3, 10));
        c->setVelocity(0, 15); // shoot them down!
        circles.push_back(c);
    }
    
    box2d.update();
}

void ofApp::draw() {
    // draw cam
    cam.draw(0, 0);
    
    // draw thresholded/background subtracted/contours found
    if(thresholded.isAllocated()) {
        thresholded.draw(640, 0);
        ofPushMatrix();
        ofTranslate(640,0);
        ofPushStyle();
        ofSetColor(255, 0, 0);
        ofSetLineWidth(3);
        for (auto & edge : edges) {
            edge->draw();
        }
        ofPopStyle();
        ofPopMatrix();
    }
    
    // draw circles
    for (auto &circle : circles) {
        ofFill();
        ofPushStyle();
        ofSetHexColor(0xc0dd3b);
        circle->draw();
        ofPopStyle();
    }
    
    gui.draw();
}
