//
//  TracingParticle.h
//
//
//  Created by Toshiya Momota on 1/6/16.
//
//

#pragma once
#include "ofMain.h"
#include "Grid.h"
#include "Particles.h"
#include "ofxGui.h"

class TracingParticle : public PaneBase{
public:
    TracingParticle();
    void update(float soundL, float soundR);
    void draw();
    void setImage(int key);
    void setSpeed(bool direction);
    void setSpeedByGui(int &speed);
    void setMaxScale(bool direction);
    void setVolThreshold(float vol);
    void changeSoundEffect();
    void clearText();
    void clearRot();
    void setRotY(bool flag);
    void setRotX(bool flag);
    void setAuto();
    void toggleDebug();
    int getParticleNum();

private:
    /*--------------------------------------------------------------
     
     
     GUI
     
     
     --------------------------------------------------------------*/
    ofxPanel gui;
    ofxIntSlider particleSpeed;
    ofxToggle soundFlag;
    ofxFloatSlider VOLUMETHRESHOLD;
    ofxToggle lightEnable;
    ofxToggle drawLight;
    ofxIntSlider lightDepth;
    ofxToggle lightAutoMove;
    ofxToggle autoRot;

    /*--------------------------------------------------------------
     
     
     OTHERS
     
     
     --------------------------------------------------------------*/
    Grid *grid;
    Particles *particles;
    
    int currentImg = 0;
    int resolution = 10;// Image Pixel Size
    int rangeVal = 0;
    int imageWidth = 0;
    int imageHeight = 0;
    float scaleVal = 0.f;
    float maxScale = 10.f;
    
    float rotX = ofDegToRad(0);
    float rotY = ofDegToRad(0);

    float lightX = ofDegToRad(0);
    
    ofTrueTypeFont typeText;
    string typeStr;
    
    ofLight light, light2;
    float colorHue;
    ofColor lightColor;
    
    bool debugFlag = true;
};