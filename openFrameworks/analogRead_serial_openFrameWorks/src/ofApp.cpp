#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    bSendSerialMessage = true;
    ofBackground(255);
    
    font.load("DIN.otf", 24);
    
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    
    // this should be set to whatever com port your serial device is connected to.
    // (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
    // arduino users check in arduino app....
    int baud = 9600;
    serial.setup(0, baud); //open the first device
    //serial.setup("COM4", baud); // windows example
    //serial.setup("/dev/cu.usbmodem5442191", baud); // mac osx example teensy: /dev/cu.usbmodem5442191
    //serial.setup("/dev/ttyUSB0", baud); //linux example
    
    nTimesRead = 0;
    nBytesRead = 0;
    memset(bytesReadString, 0, 3);
    photocell = 0;
    smoothedPhotocell = 0;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    // (1) write the letter "!" to serial -
    // this will tell the arduino we ready to get data:
    if(bSendSerialMessage){
        serial.writeByte('!');
        bSendSerialMessage = false;
    }
    
    // (2) read
    // we try to read 2 bytes
    
    // clear our variables
    nBytesRead  = 0;
    nTimesRead  = 0;
    int nRead	= 0;  // a temp variable to keep count per read
    
    
    // set this temporary buffer
    memset(bytesRead, 0, 2);
    
    // we read as much as possible so we make sure we get the newest data
    while( (nRead = serial.readBytes( bytesRead, 2)) > 0){
        nTimesRead++;
        nBytesRead = nRead;
    };

    //if we have got everything
    if ( nBytesRead == 2){
        // copy the new info to our buffer
        memcpy(bytesReadString, bytesRead, 2);
        // turn our bytes back into an int
        photocell = ((unsigned char)bytesReadString[1] << 8) | (unsigned char)bytesReadString[0] ;
        // tell arduino we're ready for some more info
        bSendSerialMessage = true;
    }
    
    smoothedPhotocell += ( float(photocell) - smoothedPhotocell ) * .025;

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(0);
    
    string msg = "Photocell: " + ofToString(photocell) + "\n";
    msg += "Smoothed: " + ofToString(int(smoothedPhotocell));
    font.drawString(msg, 50, 100);
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
