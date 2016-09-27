//
//  TracingParticle.h
//
//
//  Created by Toshiya Momota on 1/6/16.
//
//

#include "TracingParticle.h"

TracingParticle::TracingParticle(){
    ofTrueTypeFont::setGlobalDpi(72);
    
    typeText.load("tracingParticles/font/Arial.ttf", 300);
    typeText.setLineHeight(20.0f);
    typeText.setLetterSpacing(1.05f);
    typeStr = "A";
    
    grid = new Grid(resolution, typeStr, &typeText);
    particles = new Particles(*grid);
    
    ofSetSmoothLighting(true);
    light.setPointLight();
    light2.setPointLight();
    //light.setSpotlight();
    //light2.setSpotlight();
    
    light.setAmbientColor(ofColor(0.f, 0.f, 0.f));    //Ambient
    light.setDiffuseColor(ofColor(255.f, 0.f, 0.f));    //Around high light
    light.setSpecularColor(ofColor(255.f, 255.f, 255.f));    //Highlight
    light2.setAmbientColor(ofColor(0.f, 0.f, 0.f));    //Ambient
    light2.setDiffuseColor(ofColor(255.f, 0.f, 0.f));    //Around high light
    light2.setSpecularColor(ofColor(255.f, 255.f, 255.f));    //Highlight
    
    colorHue = ofRandom(0, 250);
    lightColor.setBrightness(255.f);
    lightColor.setSaturation(255.f);
    
    /* GUI */
    gui.setup();
    gui.add(particleSpeed.setup("Particle speed", 50, 1, 100));
    gui.add(soundFlag.setup("Sound flag", false));
    gui.add(VOLUMETHRESHOLD.setup("Sound threthold", 1.0f, 0.1f, 10.0f));
    gui.add(lightEnable.setup("Light ON/OFF", true));
    gui.add(drawLight.setup("Draw Light ON/OFF", false));
    gui.add(lightDepth.setup("Light depth", 150, 0, 2000));
    gui.add(lightAutoMove.setup("Light auto move", true));
    gui.add(autoRot.setup("Auto rotation ON/OFF", false));
    particleSpeed.addListener(this, &TracingParticle::setSpeedByGui);
    
}
void TracingParticle::update(float soundL, float soundR){
    if (soundL > soundR) {
        scaleVal = soundL;
    }else{
        scaleVal = soundR;
    }
    
    auto w = typeText.stringWidth(typeStr);
    auto h = typeText.stringHeight(typeStr);
    
    auto baseScale = 1.0f;
    if(w > ofGetWidth()){
        auto diff = (float)ofGetWidth() / (float)w;
        baseScale = 1.0f * diff;
    }
    
    if(soundFlag){
        scaleVal = ofMap(scaleVal, 0.0f, VOLUMETHRESHOLD, baseScale, maxScale, true);
    }else{
        scaleVal = baseScale;
    }

    //if(autoRot) rotX++;
    if(autoRot) rotY++;
    //if(rotX > 360) rotX = 0;
    if(rotY > 360) rotY = 0;
    
    particles->update();

    if(lightEnable){
        if(lightAutoMove){
            lightX++;
            if(lightX > 360) lightX = 0;
            light.setPosition(ofGetWidth()*.5f + sin(ofDegToRad(lightX)) * (w *.5f) * scaleVal, ofGetHeight()*.5, lightDepth);
            light2.setPosition(ofGetWidth()*.5f + sin(ofDegToRad(-lightX)) * (w *.5f) * scaleVal, ofGetHeight()*.5, lightDepth);
        }else{
            light.setPosition(ofGetWidth()*.5f, ofGetHeight()*.5f, lightDepth);
            light2.setPosition(ofGetWidth()*.5f, ofGetHeight()*.5f, lightDepth);
        }
        
        colorHue += .1f;
        if(colorHue >= 255) colorHue = 0.f;
        lightColor.setHue(colorHue);
        light.setDiffuseColor(lightColor);
        lightColor.setHue(255-colorHue);
        light2.setDiffuseColor(lightColor);
        light.enable();
        light2.enable();
    }else{
        ofDisableLighting();
        light.disable();
        light2.disable();
    }
}
void TracingParticle::draw(){
    ofEnableDepthTest();

    ofPushMatrix();
    ofTranslate(ofGetWidth()*.5f, ofGetHeight()*.5f);
    ofRotateX(rotX);
    ofRotateY(rotY);
    ofTranslate(-ofGetWidth()*.5f, -ofGetHeight()*.5f);
    particles->draw();
    //grid->draw(); // -> For Debug
    ofPopMatrix();

    if(lightEnable) ofEnableLighting();
    if(drawLight) light.draw();
    if(drawLight) light2.draw();
    if(lightEnable) ofDisableLighting();
    ofDisableDepthTest();
    if(debugFlag) gui.draw();
    if(debugFlag) ofDrawBitmapString(ofToString(ofGetFrameRate())+ "fps" , ofGetWidth() - 40, 15);
}
void TracingParticle::setImage(int _key){
    ofAppendUTF8(typeStr, _key);
    grid->init(typeStr, &typeText);
    particles->setGoals(*grid);
}
void TracingParticle::setSpeed(bool flag){
    if(!flag){
        particleSpeed = stoi(particleSpeed.getParameter().toString()) + 1;
        particles->setSpeed(particleSpeed);

    }else{
        particleSpeed = stoi(particleSpeed.getParameter().toString()) - 1;
        particles->setSpeed(particleSpeed);
    }
}
void TracingParticle::setSpeedByGui(int &speed){
    particles->setSpeed(speed);
}
void TracingParticle::setMaxScale(bool direction){
    if (direction) {
        maxScale += 0.1;
    }else{
        maxScale -= 0.1;
        if (maxScale < 1.0) maxScale = 1.0;
    }
}
void TracingParticle::setRotY(bool flag){
    if(flag){
        rotY += 1;
    }else{
        rotY -= 1;
    }
}
void TracingParticle::setRotX(bool flag){
    if(flag){
        rotX += 1;
    }else{
        rotX -= 1;
    }
}
void TracingParticle::setAuto(){
    autoRot = !autoRot;
}
void TracingParticle::setVolThreshold(float _vol){
    VOLUMETHRESHOLD = _vol;
}
void TracingParticle::changeSoundEffect(){
    soundFlag = !soundFlag;
}
void TracingParticle::clearText(){
    if(typeStr.size() == 0) return;
    typeStr.pop_back();
    grid->init(typeStr, &typeText);
    particles->setGoals(*grid);
}
void TracingParticle::clearRot(){
    rotX = 0;
    rotY = 0;
}
void TracingParticle::toggleDebug(){
    debugFlag = !debugFlag;
}
int TracingParticle::getParticleNum(){
    return particles->getParticleNumber();
}
