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
        unsigned char		bytesRead[2];				// data from serial, we will be trying to read 2
        unsigned char		bytesReadString[3];         // a string needs a null terminator, so we need 2 + 1 bytes
        int                 nBytesRead;					// how much did we read?
        int                 nTimesRead;					// how many times did we read?
        int                 photocell;                  
        float               smoothedPhotocell;
    
        ofSerial            serial;
		
};
