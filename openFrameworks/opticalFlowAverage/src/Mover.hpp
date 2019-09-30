//
//  Mover.hpp
//  opticalFlow_squares
//
//  Created by aaron sherwood on 9/17/19.
//
//

#ifndef Mover_hpp
#define Mover_hpp

#include <stdio.h>
#include "ofMain.h"

class Mover {
public:
    Mover();
    Mover(float x, float y, float mass);
    void applyForces(ofVec2f & force);
    void update();
    void display();
    void checkedges();
    
    ofVec2f position;
    
private:
    float angle;
    float angularAcceleration;
    float angularVelocity;
    ofVec2f velocity;
    ofVec2f acceleration;
    float mass;
    
};

#endif /* Mover_hpp */
