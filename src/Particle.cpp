//
//  Particle.cpp
//
//
//  Created by Toshiya Momota on 1/6/16.
//
//

#include "Particle.h"
#include "ofxEasing.h"

Particle::Particle(float _speed, int screenW, int screenH){
    _x = ofRandom(-screenW,screenW);
    _y = ofRandom(-screenH,screenH);
    _z = ofRandom(-1000,1000);
    
    speed = _speed;
    
    easingNames = {
        "linear",
        "quad",
        "cubic",
        "bounce",
        "back",
        "quart",
        "quint",
        "sine",
        "elastic",
        "circ"
    };
}

void Particle::update(){
    _px = _x;
    _py = _y;
    _pz = _z;
    
    auto endTime = initTime + speed * .1f;
    auto now = ofGetElapsedTimef();
    
    if(now < initTime+speed){
        _x = ofxeasing::map_clamp(now, initTime, endTime, initPos.x, targetPos.x, &ofxeasing::linear::easeIn);
        _y = ofxeasing::map_clamp(now, initTime, endTime, initPos.y, targetPos.y, &ofxeasing::linear::easeIn);
        _z = ofxeasing::map_clamp(now, initTime, endTime, initPos.z, targetPos.z, &ofxeasing::linear::easeIn);
    }
}
void Particle::draw(){
}
void Particle::setGoal(ofVec3f pos, ofColor c, float _initTime){
    initTime = _initTime;
    initPos = ofVec3f(_x, _y, _z);
    targetPos = pos;
}
void Particle::setSpeed(float _speed){
    speed = _speed;
}
ofVec3f Particle::getLocation(){
    return ofVec3f(_x, _y, _z);
}
