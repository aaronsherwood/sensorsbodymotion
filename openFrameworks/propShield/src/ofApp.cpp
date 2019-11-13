#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    bSendSerialMessage = true;
    ofBackground(255);
    
    font.load("DIN.otf", 24);
    
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    
    // this should be set to whatever com port your serial device is connected to.
    // (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
    // arduino users check in arduino app....
    int baud = 9600;
    serial.setup(1, baud); //open the first device
    //serial.setup("COM4", baud); // windows example
    //serial.setup("/dev/cu.usbmodem5442191", baud); // mac osx example teensy: /dev/cu.usbmodem5442191
    //serial.setup("/dev/ttyUSB0", baud); //linux example
    
    heading = pitch = roll = 0;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // (1) write the letter "!" to serial -
    // this will tell the arduino we ready to get data:
    if (bSendSerialMessage){
        serial.writeByte('!');
        bSendSerialMessage = false;
    }
    serialString = "";
    serialString = ofxGetSerialString(serial, '\n');
    if (serialString != ""){
        auto strings = split(serialString, ' ');
        heading = ofToFloat(strings[0]);
        pitch = ofToFloat(strings[1]);
        roll = ofToFloat(strings[2]);
        bSendSerialMessage=true;
        msg = "Heading: ";
        msg += strings[0];
        msg += "\n";
        msg += "Pitch: ";
        msg += strings[1];
        msg += "\n";
        msg += "Roll: ";
        msg += strings[2];
        //cout<<serialString<<endl;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0);
    font.drawString(msg, 50, 100);
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, (ofGetHeight()/3)*2);
 
    float c1 = cos(ofDegToRad(roll));
    float s1 = sin(ofDegToRad(roll));
    float c2 = cos(ofDegToRad(-pitch));
    float s2 = sin(ofDegToRad(-pitch));
    float c3 = cos(ofDegToRad(heading));
    float s3 = sin(ofDegToRad(heading));
    auto matrix = glm::mat4( c2*c3, s1*s3+c1*c3*s2, c3*s1*s2-c1*s3, 0,
                -s2, c1*c2, c2*s1, 0,
                c2*s3, c1*s2*s3-c3*s1, c1*c3+s1*s2*s3, 0,
                0, 0, 0, 1);
    ofMultMatrix(matrix);
    ofDrawBox(100);
    ofPopMatrix();
}

//--------------------------------------------------------------
string ofApp::ofxTrimStringRight(string str) {
    // trim trailing spaces
    size_t endpos = str.find_last_not_of(" \t\r\n");
    return (string::npos != endpos) ? str.substr( 0, endpos+1) : str;
}

//--------------------------------------------------------------
string ofApp::ofxTrimStringLeft(string str) {
    // trim trailing spaces
    size_t startpos = str.find_first_not_of(" \t\r\n");
    return (string::npos != startpos) ? str.substr(startpos) : str;
}

//--------------------------------------------------------------
string ofApp::ofxTrimString(string str) {
    // trim trailing spaces
    return ofxTrimStringLeft(ofxTrimStringRight(str));
}

//--------------------------------------------------------------
string ofApp::ofxGetSerialString(ofSerial &serial, char until) {
    static string str;
    stringstream ss;
    char ch;
    int ttl=1000;
    while ((ch=serial.readByte())>0 && ttl-->0 && ch!=until) {
        ss << ch;
    }
    str+=ss.str();
    if (ch==until) {
        string tmp=str;
        str="";
        return ofxTrimString(tmp);
    } else {
        return "";
    }
    
}

//--------------------------------------------------------------
std::vector<std::string> ofApp::split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
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
