#include "ofApp.h"

/*
 If you are struggling to get the device to connect ( especially Windows Users )
 please look at the ReadMe: in addons/ofxKinect/README.md
 */

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetVerticalSync(true);
    
    
#ifdef USE_KINECT
    // enable depth->video image calibration
    kinect.setRegistration(false);
    
    kinect.init();
    //kinect.init(true); // shows infrared instead of RGB video image
    //kinect.init(false, false); // disable video image (faster fps)
    
    kinect.open();		// opens first available kinect
    //kinect.open(1);	// open a kinect by id, starting with 0 (sorted by serial # lexicographically))
    //kinect.open("A00362A08602047A");	// open a kinect using it's unique serial #
    depthWidth = kinect.width;
    depthHeight = kinect.height;
#endif
    
#ifdef USE_REALSENSE
    // init realsense
    realSense = RSDevice::createUniquePtr();
    realSense->checkConnectedDialog();
    // depth frame size can be:
    // 1280x720, 848X480, 640x480, 640x360, 480x270, or 424x240
    int w = 640;
    int h = 480;
    realSense->setDepthSize(w, h);
    realSense->setVideoSize(w, h);
    realSense->capture();
    realSense->printDeviceInfo();
    realSense->setBlackWhiteDepth();
    depthWidth = w;
    depthHeight = h;
#endif
    
    colorImg.allocate(depthWidth, depthHeight);
    grayImage.allocate(depthWidth, depthHeight);

    nearThreshold = 255;
    farThreshold = 200;
    
    ofSetFrameRate(60);
    
    trackingMode = AVERAGE;
    debug = false;
    
    ofBackground(255);
    tileWidth = ofGetWidth() / tileCount;
    tileHeight = ofGetHeight() / tileCount;
    maxDist = sqrt(pow(ofGetWidth(), 2) + pow(ofGetHeight(), 2));
    
    ofBackground(255);
}

//--------------------------------------------------------------
void ofApp::update() {
    
    bool newFrame = false;
    
    // there is a new frame and we are connected
    #ifdef USE_KINECT
    kinect.update();
    newFrame = kinect.isFrameNew();
    #endif
    #ifdef USE_REALSENSE
    newFrame = realSense->update();
    #endif
    
    if(newFrame) {
        #ifdef USE_KINECT
        // load grayscale depth image from the kinect source
        grayImage.setFromPixels(kinect.getDepthPixels());
        #endif
    
        #ifdef USE_REALSENSE
        // load grayscale depth image from the realsense source
        ofPixels pix;
        pix = realSense->getDepthFrame();
        pix.setImageType(OF_IMAGE_GRAYSCALE);
        grayImage.setFromPixels(pix);
        #endif
        
        // either closest or average point or plain threshold
        switch (trackingMode){
            case THRESHOLD:
                threshold();
                break;
            case AVERAGE:
                averageDepth();
                break;
            case CLOSEST:
                closestPoint();
                break;
        }

        // update the cv images
        grayImage.flagImageChanged();
        
        // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
        // also, find holes is set to true so we will get interior contours as well....
        contourFinder.findContours(grayImage, 10, (depthWidth*depthHeight)/2, 20, false);
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    if (debug){
        ofSetColor(255, 255, 255);
        #ifdef USE_KINECT
        kinect.drawDepth(0,0, 640,480);
        kinect.draw(0, 480, 640,480);
        #endif
        #ifdef USE_REALSENSE
        realSense->drawDepthStream(ofRectangle(0,0, 640,480));
        realSense->drawVideoStream(ofRectangle(0, 480, 640,480));
        #endif
        grayImage.draw(640, 0, 640,480);
        contourFinder.draw(640, 0, 640,480);
        
        switch (trackingMode){
                case CLOSEST:
                case AVERAGE:
                    ofPushStyle();
                    ofPushMatrix();
                    ofTranslate(640,0);
                    ofSetHexColor(0xDD00CC);
                    ofFill();
                    ofDrawEllipse(trackingX, trackingY, 30, 30);
                    ofPopMatrix();
                    ofPopStyle();
                    break;
        }
    } else{
        drawLines();
    }
}

//--------------------------------------------------------------
void ofApp::drawLines(){
    for (int gridY = 0; gridY < tileCount; gridY++) {
        for (int gridX = 0; gridX < tileCount; gridX++) {
            
            float posX = tileWidth * gridX + tileWidth/2;
            float posY = tileHeight * gridY + tileHeight/2;
            
            float tx = ofMap(trackingX,0, depthWidth, 0, ofGetWidth());
            float ty = ofMap(trackingY,0, depthHeight, 0, ofGetHeight());
            // calculate angle between tracking position and actual position of the shape
            float angle = atan2(ty - posY, tx - posX) + (shapeAngle * (PI / 180));
            
            if (sizeMode == 0) newShapeSize = shapeSize;
            if (sizeMode == 1) newShapeSize = shapeSize * 1.5 - ofMap(ofDist(tx, ty, posX, posY), 0, 500, 5, shapeSize);
            if (sizeMode == 2) newShapeSize = ofMap(ofDist(tx, ty, posX, posY), 0, 500, 5, shapeSize);
            
            ofPushMatrix();
            ofTranslate(posX, posY);
            ofRotateRad(angle);
            ofSetColor(0);
            ofDrawLine(0,0,newShapeSize,0);
            
            ofPopMatrix();
        }
    }
}

//--------------------------------------------------------------
void ofApp::closestPoint(){
    int closest = 0;
    float closestX=0;
    float closestY=0;
    
    ofPixels & pix = grayImage.getPixels();
    int numPixels = pix.size();
    for (int y=0;y<depthHeight;y++){
        for (int x=0; x<depthWidth; x++) {
            int index = x+y*depthWidth;
            if(pix[index] < nearThreshold && pix[index] > farThreshold) {
                if (pix[index]>closest){
                    closest=pix[index];
                    closestX=x;
                    closestY=y;
                }
                pix[index] = 255;
            } else {
                pix[index] = 0;
            }
        }
    }
    
    if (closestX>0 || closestY>0){
        trackingX+=(closestX-trackingX)*.1;
        trackingY+=(closestY-trackingY)*.1;
    }
}

//--------------------------------------------------------------
void ofApp::averageDepth(){
    int amount = 0;
    float averageX = 0;
    float averageY = 0;
    
    ofPixels & pix = grayImage.getPixels();
    int numPixels = pix.size();
    for (int y=0;y< depthHeight;y++){
        for (int x=0; x<depthWidth; x++) {
            int index = x+y*depthWidth;
            if(pix[index] < nearThreshold && pix[index] > farThreshold) {
                averageX += x;
                averageY += y;
                amount ++;
                pix[index] = 255;
            } else {
                pix[index] = 0;
            }
        }
    }
    if (amount>0){
        averageX /= amount;
        averageY /= amount;
        trackingX=averageX;
        trackingY=averageY;
    }
}

void ofApp::threshold(){
    ofPixels & pix = grayImage.getPixels();
    int numPixels = pix.size();
    for(int i = 0; i < numPixels; i++) {
        if(pix[i] < nearThreshold && pix[i] > farThreshold) {
            pix[i] = 255;
        } else {
            pix[i] = 0;
        }
    }
}


//--------------------------------------------------------------
void ofApp::exit() {
    #ifdef USE_KINECT
    kinect.close();
    #endif
    #ifdef USE_REALSENSE
    realSense->stop();
    #endif
}

//--------------------------------------------------------------
void ofApp::keyPressed (int key) {
    switch (key) {
        case '>':
        case '.':
            farThreshold ++;
            if (farThreshold > 255) farThreshold = 255;
            break;
            
        case '<':
        case ',':
            farThreshold --;
            if (farThreshold < 0) farThreshold = 0;
            break;
            
        case '+':
        case '=':
            nearThreshold ++;
            if (nearThreshold > 255) nearThreshold = 255;
            break;
            
        case '-':
            nearThreshold --;
            if (nearThreshold < 0) nearThreshold = 0;
            break;
        case 'd':
            debug=!debug;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    
}
