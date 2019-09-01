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
    

    nBytesRead = 0;
    inByte = 0;
    
    rectSize = ofGetWidth()/8;
    memset(onOff, 0, 8);
    
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
    // we try to read 16 bytes
    
    // clear our variables
    nBytesRead  = 0;
    int nRead	= 0;  // a temp variable to keep count per read
    inByte = 0;
    
    // we read as much as possible so we make sure we get the newest data
    while( (nRead = serial.readBytes( &inByte, 1)) > 0){
        nBytesRead = nRead;
    };
    
    //if we have got everything
    if ( nBytesRead == 1){
        // separate our byte back out
        for (int i=0; i<8; i++){
            if (i<7)
                onOff[i] = (inByte >> (7-i)) & 0x01; // first trigger is our left most bit, so rightshift the inverse of i, mask for one bit
            else
                onOff[i] = inByte & 0x01; // last bit is right most, so just mask for 1 bit
        }

        // tell arduino we're ready for another set of info
        bSendSerialMessage = true;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(0);
    
    string msg;
    
    for (int i = 0; i < 8; i++){

        if (onOff[i]==1)
            ofDrawRectangle((i)*rectSize,450,rectSize,20);
        msg += "Pin: " + ofToString(i+1);
        msg += "\tReading: " + ofToString(onOff[i]) + "\n";
    }
    
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
