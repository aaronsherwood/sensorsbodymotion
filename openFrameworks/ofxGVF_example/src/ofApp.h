#pragma once

#include "ofMain.h"
#include "ofxGVF.h"
#include "ofxOsc.h"

#define OSC_DESTINATION_DEFAULT "localhost"
#define OSC_ADDRESS_ROOT_DEFAULT "/wek/outputs"
#define OSC_PORT_DEFAULT 6448

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void displayParticlesOnGesture(GVFGesture currentGesture);
    float oscX, oscY;
    bool listenOSC;
    
private:
    std::vector<float> theSample;
    ofxGVF * mygvf;
    GVFGesture gesture;
    ofRectangle drawArea;

    bool isMouseDrawing;
    bool displayParticles;
    
    ofxOscSender osc;
    ofxOscReceiver receiver;
    string oscDestination;
    string oscAddress;
    string oscIncomingAddress;
    int oscPort;
    int oscIncomingPort;
    string oscMessageString;
};
