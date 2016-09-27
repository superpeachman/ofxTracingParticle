//
//  Pane.h
//
//
//  Created by Toshiya Momota on 1/6/16.
//
//

#pragma once
#include "ofMain.h"
#include "PaneBase.h"

class Pane : public PaneBase{
public:
    void init(int x, int y, int s, ofColor &c);
    void draw();
private:
};
