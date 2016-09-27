//
//  PaneBase.h
//
//
//  Created by Toshiya Momota on 1/6/16.
//
//

#pragma once
#include "ofMain.h"
class PaneBase {
public:
    int _x;
    int _y;
    int _s;
    ofColor *_c;
    
    void init(int x, int y, int s, ofColor &c);
    void draw();
private:
};

