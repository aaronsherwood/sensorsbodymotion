#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
    ofSetVerticalSync(true);
    cam.setup(320, 240);
    
    // thresholded image shold be same size as cam
    thresh.allocate(320, 240, OF_IMAGE_GRAYSCALE);
    
    // imitate() will set up previous and diff
    // so they have the same size and type as cam
    imitate(previous, cam);
    imitate(diff, cam);
    
    // set the threshold value
    thresholdValue = 128;
    
    // load sounds
    sound1.load("sounds/shortened/c.wav");
    sound2.load("sounds/shortened/e.wav");
    // makes it so the sounds won't overlap
    sound1.setMultiPlay(false);
    sound2.setMultiPlay(false);
    
    // set triggers to false
    section1Triggered = section2Triggered = false;
    
    //load the font
    font.load("DIN.otf", 12);
}

void ofApp::update() {
    cam.update();
    if(cam.isFrameNew()) {
        // take the absolute difference of prev and cam and save it inside diff
        absdiff(cam, previous, diff);
        diff.update();
        
        // like ofSetPixels, but more concise and cross-toolkit
        copy(cam, previous);
        
        // convert the differenced image to grayscale and threshold
        convertColor(diff, thresh, CV_RGB2GRAY);
        
        // press mouse to update threshold value
        if(ofGetMousePressed()) {
            thresholdValue = ofMap(mouseX, 0, ofGetWidth(), 0, 255);
        }
        
        // threshold the image
        threshold(thresh, thresholdValue);
        thresh.update();
        
        // this is the key line: get the average of each column
        columnMean = meanCols(thresh);
    }
    
    // update the sound playing system:
    ofSoundUpdate();
    
    // if sound is done playing, make it triggerable again
    if (!sound1.isPlaying())
        section1Triggered=false;
    if (!sound2.isPlaying())
        section2Triggered=false;
    
    // temp variables to keep track of if there is any movement in a region
    int section1=0;
    int section2=0;
    
    for(int i = 0; i < columnMean.rows; i++) {
        // since we're grayscale now we only need a byte
        uchar cur = columnMean.at<uchar>(i);
        
        // keep track of how much movement is happening in the various sections
        if (i>0 && i<50){
            section1+=cur;
        }
        if (i>270 && i<320){
            section2+=cur;
        }
    }
    
    // trigger the sounds if not already playing
    if (section1>0 && !sound1.isPlaying()){
        section1Triggered = true;
        sound1.play();
    }
    
    if (section2>0 && !sound2.isPlaying()){
        section2Triggered = true;
        sound2.play();
    }
}

void ofApp::draw() {
    ofSetColor(255);
    cam.draw(0, 0);
    string org = "Original Video";
    ofSetColor(255, 200);
    ofFill();
    font.drawString(org, 20, 20);
    
    ofTranslate(320, 0);
    ofSetColor(255);
    diff.draw(0, 0);
    string dif = "Differenced Video";
    ofSetColor(255, 200);
    ofFill();
    font.drawString(dif, 20, 20);
    
    ofTranslate(-320, 240);
    ofSetColor(255);
    thresh.draw(0, 0, 640, 480);
    
    ofSetColor(0,0,255);

    if (section1Triggered){
        ofFill();
        ofSetColor(0,0,255,200);
    } else
        ofNoFill();
    
    ofDrawRectangle(0, 0, 50*2, 240*2);
    
    
    if (section2Triggered){
        ofFill();
        ofSetColor(0,0,255,200);
    } else
        ofNoFill();
    
    ofDrawRectangle(270*2, 0, 50*2, 240*2);
    
    string msg = "Threshold: ";
    msg += ofToString(thresholdValue);
    msg += "\n(click and drag mouse left & right to change threshold)";
    ofSetColor(255, 200);
    ofFill();
    font.drawString(msg, 120, 450);
}
