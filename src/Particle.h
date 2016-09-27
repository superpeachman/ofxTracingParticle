//
//  Particle.h
//
//
//  Created by Toshiya Momota on 1/6/16.
//
//

#pragma once
#include "ofMain.h"

class Particle {
public:
    Particle(float speed, int screenW, int screenH);
    ~Particle(){
        //cout << "call destructor" << endl;
    }
    void setGoal(ofVec3f pos, ofColor c, float initTime);
    void setSpeed(float speed);
    ofVec3f getLocation();
    void update();
    void draw();
    
private:
    
    float _x, _y, _z;
    float _px, _py, _pz;
    float _r,_g,_b;
    ofVec3f initPos = ofVec3f(0, 0, 0);
    ofVec3f targetPos = ofVec3f(0, 0, 0);
    
    float speed = 5;
    float initTime = 0;
    
    std::vector<std::string> easingNames;
};