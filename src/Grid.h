//
//  Grid.h
//
//
//  Created by Toshiya Momota on 1/6/16.
//
//

#pragma once
#include "ofMain.h"
#include "Pane.h"

class Grid {
public:
    Grid(int paneSize, string &_textData, ofTrueTypeFont *_typeText);
    void init(string &_textData, ofTrueTypeFont *_typeText);
    
    void draw();
    ofVec2f getByIndex(int index);
    ofColor getPanelColor(int index);
    int getPanelNumber();
    int getPanelSize();
    
    vector<Pane> panes;
    Pane pane;
private:
    ofFbo fontFbo;
    ofPixels fontPix;
    ofTrueTypeFont	*typeText;
    int paneSize = 0;
};