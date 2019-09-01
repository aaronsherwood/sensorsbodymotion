#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofTrueTypeFont		font;
    
    bool                bSendSerialMessage;			// a flag for sending serial
    unsigned char		inByte;                     // data from serial
    int                 nBytesRead;					// how much did we read?
    int                 rectSize;                   // size to draw rects
    int                 onOff[8];                   // array to store our touch states
    
    ofSerial            serial;
    
};
