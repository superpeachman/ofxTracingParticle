//
//  PaneBase
//
//
//  Created by Toshiya Momota on 1/6/16.
//
//

#include "PaneBase.h"
void PaneBase::init(int x, int y, int s, ofColor &c){
    _x = x;
    _y = y;
    _s = s;
    _c = &c;
}
void PaneBase::draw(){
    ofFill();
    ofSetColor(ofRandom(255),ofRandom(255),ofRandom(255),200);
    ofDrawRectangle(_x,_y,_s,_s);
}