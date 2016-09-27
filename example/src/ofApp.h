//
//  ofApp.h
//
//
//  Created by Toshiya Momota on 1/6/16.
//
//

#pragma once

#include "ofMain.h"
#include "ofxFft.h"
#include "TracingParticle.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void audioReceived(float* input, int bufferSize, int nChannels);

    /*--------------------------------------------------------------
     
     
     FFT
     
     
     --------------------------------------------------------------*/
    ofSoundStream soundStream;
    
    ofxFft* fft;
    
    float max_tempL, max_tempR, avg_powerL, avg_powerR;
    float preTime, curTime, gapTime;
    
    int plotHeight;
    int bufferSize;
    
    float* audioInputL;
    float* audioInputR;
    float* fftOutputL;
    float* fftOutputR;
    float* eqFunction;
    float* eqOutputL;
    float* eqOutputR;
    
    /*--------------------------------------------------------------
     
     
     Tracing Particles
     
     
     --------------------------------------------------------------*/
    TracingParticle *tp;
};
