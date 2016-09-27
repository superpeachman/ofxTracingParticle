//
//  ofApp.cpp
//
//
//  Created by Toshiya Momota on 1/6/16.
//
//

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    /*--------------------------------------------------------------
     
     
     BASE
     
     
     --------------------------------------------------------------*/
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofSetBackgroundAuto(true);
    ofBackground(0, 0, 0);
    ofEnableAlphaBlending();
        
    /*--------------------------------------------------------------
     
     
     FFT
     
     
     --------------------------------------------------------------*/
    bufferSize = 2048;
    
    gapTime = 0;
    curTime = 0;
    preTime = 0;
    
    //fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_BARTLETT);
    fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_BARTLETT, OF_FFT_FFTW);
    
    audioInputL = new float[bufferSize];
    audioInputR = new float[bufferSize];
    fftOutputL = new float[fft->getBinSize()];
    fftOutputR = new float[fft->getBinSize()];
    eqFunction = new float[fft->getBinSize()];
    eqOutputL = new float[fft->getBinSize()];
    eqOutputR = new float[fft->getBinSize()];
    
    for(int i = 0; i < fft->getBinSize(); i++){
        eqFunction[i] = (float) (fft->getBinSize() - i) / (float) fft->getBinSize();
    }
    
    ofSoundStreamSetup(0, 2, this, 44100, bufferSize, 4);
    
    /*--------------------------------------------------------------
     
     
     Tracing Particles
     
     
     --------------------------------------------------------------*/
    tp = new TracingParticle();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    /*--------------------------------------------------------------
     
     
     Tracing Particles
     
     
     --------------------------------------------------------------*/
    tp->update(eqOutputL[0], eqOutputR[0]);
}

//--------------------------------------------------------------
void ofApp::draw(){
    /*--------------------------------------------------------------
     
     
     Tracing Particles
     
     
     --------------------------------------------------------------*/
    tp->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //FULL SCREEN --------------------------------------------------------------
    if(key == OF_KEY_ALT){
        ofToggleFullscreen();
    }
    /*--------------------------------------------------------------
     
     
     Tracing Particles
     
     
     --------------------------------------------------------------*/
    if(key == 'q'){
        tp->clearRot();
    }else if(key == 'w'){
        tp->setAuto();
    }else if(key == 'e'){
        tp->toggleDebug();
    }else if(key == 'r'){
    }
    if(key == OF_KEY_LEFT){
        tp->setSpeed(true);
    }else if(key == OF_KEY_RIGHT){
        tp->setSpeed(false);
    }
    if(key == OF_KEY_UP){
        tp->setRotX(true);
    }else if(key == OF_KEY_DOWN){
        tp->setRotX(false);
    }
    if(key == 127/* DELETE KEY */){
        tp->clearText();
    }
    
    if( key == 33 ){ tp->setImage(33); }//1
    else if( key == 64){ tp->setImage(64); }//2
    else if( key == 35){ tp->setImage(35); }//3
    else if( key == 36){ tp->setImage(36); }//4
    else if( key == 37){ tp->setImage(37); }//5
    else if( key == 94){ tp->setImage(94); }//6
    else if( key == 38){ tp->setImage(38); }//7
    else if( key == 42){ tp->setImage(42); }//8
    else if( key == 40){ tp->setImage(40); }//9
    else if( key == 41){ tp->setImage(41); }//0
    
    if( key == 65 ){ tp->setImage(65); }//A
    else if( key == 66){ tp->setImage(66); }//B
    else if( key == 67){ tp->setImage(67); }//C
    else if( key == 68){ tp->setImage(68); }//D
    else if( key == 69){ tp->setImage(69); }//E
    else if( key == 70){ tp->setImage(70); }//F
    else if( key == 71){ tp->setImage(71); }//G
    else if( key == 72){ tp->setImage(72); }//H
    else if( key == 73){ tp->setImage(73); }//I
    else if( key == 74){ tp->setImage(74); }//J
    else if( key == 75){ tp->setImage(75); }//K
    else if( key == 76){ tp->setImage(76); }//L
    else if( key == 77){ tp->setImage(77); }//M
    else if( key == 78){ tp->setImage(78); }//N
    else if( key == 79){ tp->setImage(79); }//O
    else if( key == 80){ tp->setImage(80); }//P
    else if( key == 81){ tp->setImage(81); }//Q
    else if( key == 82){ tp->setImage(82); }//R
    else if( key == 83){ tp->setImage(83); }//S
    else if( key == 84){ tp->setImage(84); }//T
    else if( key == 85){ tp->setImage(85); }//U
    else if( key == 86){ tp->setImage(86); }//V
    else if( key == 87){ tp->setImage(87); }//W
    else if( key == 88){ tp->setImage(88); }//X
    else if( key == 89){ tp->setImage(89); }//Y
    else if( key == 90){ tp->setImage(90); }//Z
    else if( key == 32){ tp->setImage(32); }//SPACE
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
//--------------------------------------------------------------
void ofApp::audioReceived(float* input, int bufferSize, int nChannels) {
    
    //NOT NORMALIZED
    for(int i=0; i < bufferSize; i++){
        audioInputL[i] = input[i*2];
        audioInputR[i] = input[i*2+1];
    }
    
    fft->setSignal(audioInputL);
    memcpy(fftOutputL, fft->getAmplitude(), sizeof(float) * fft->getBinSize());
    
    fft->setSignal(audioInputR);
    memcpy(fftOutputR, fft->getAmplitude(), sizeof(float) * fft->getBinSize());
    
    
    for(int i = 0; i < fft->getBinSize(); i++){
        eqOutputL[i] = fftOutputL[i] * eqFunction[i];
        eqOutputR[i] = fftOutputR[i] * eqFunction[i];
    }
}
