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
    memset(bytesReadString, 0, 17);
    
    rectSize = ofGetWidth()/8;
    
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
    
    // we are going to read 16 bytes, 8 for which are the pin num, and another 8 for if the pin is touched or not
    // we need a buffer to store 16 bytes
    unsigned char bytesReturned[16];
    
    // set this temporary buffer
    memset(bytesReturned, 0, 16);
    
    // we read as much as possible so we make sure we get the newest data
    while( (nRead = serial.readBytes( bytesReturned, 16)) > 0){
        nBytesRead = nRead;
    };
    
    //if we have got everything
    if ( nBytesRead == 16){
        // copy the new info to our buffer
        memcpy(bytesReadString, bytesReturned, 16);
        // tell arduino we're ready for another set of info
        bSendSerialMessage = true;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(0);
    
    string msg;
    
    for (int i = 0; i < 16; i+=2){
        // convert from char to int, the minus '0' converts it from ascii.
        // see https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c for more info
        int on = int(bytesReadString[i+1]-'0');
        if (on==1)
            ofDrawRectangle((i/2)*rectSize,450,rectSize,20);
        msg += "Pin: " + ofToString(bytesReadString[i]);
        msg += "\tReading: " + ofToString(on) + "\n";
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
