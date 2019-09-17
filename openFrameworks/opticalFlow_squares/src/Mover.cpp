//
//  Mover.cpp
//  opticalFlow_squares
//
//  Created by aaron sherwood on 9/17/19.
//
//

#include "Mover.hpp"

Mover::Mover(){}

Mover::Mover(float x, float y, float _mass){
    angle = 0;
    angularAcceleration = 0;
    angularVelocity = 0;
    position.set(x, y);
    velocity.set(ofRandom(-10,10), ofRandom(-10,10));
    acceleration.set(0, 0);
    mass = _mass;
}

void Mover::applyForces(ofVec2f & force){
    auto f = force / mass;
    acceleration += f;
}

void Mover::update(){
    velocity += acceleration;
    position += velocity;
    
    checkedges();
    
    angularAcceleration = acceleration.x / 50.;
    angularVelocity += angularAcceleration;
    angularVelocity = ofClamp(angularVelocity,-1.,.1);
    angle += angularVelocity;
    velocity *= .9;
    angularVelocity *= .9;
    acceleration *= 0;
}

void Mover::display(){
    ofPushStyle();
    ofSetLineWidth(0);
    ofRectMode(CENTER);
    ofPushMatrix();
    ofSetColor(255,100);
    ofTranslate(position.x, position.y);
    ofRotateRad(angle);
    ofDrawRectRounded(0,0, mass*16, mass*16,5);
    ofPopMatrix();
    ofPopStyle();
}

void Mover::checkedges(){
    if (position.x >= ofGetWidth()) {
        position.x = ofGetWidth();
        velocity.x *= -1;
    } else if (position.x <= 0) {
        velocity.x *= -1;
        position.x = 0;
    }
    if (position.y >= ofGetHeight()) {
        velocity.y *= -1;
        position.y = ofGetHeight();
    }
    if (position.y <= 0) {
        velocity.y *= -1;
        position.y = 0;
    }
}
