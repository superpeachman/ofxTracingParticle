//
//  Grid.cpp
//
//
//  Created by Toshiya Momota on 1/6/16.
//
//

#include "Grid.h"

Grid::Grid(int _paneSize, string &_textData, ofTrueTypeFont *_typeText){
    panes.clear();
    fontPix.clear();
    paneSize = _paneSize;
    typeText = _typeText;
    
    auto textWidth = typeText->stringWidth(_textData);
    auto textHeight = typeText->stringHeight(_textData);
    
    auto baseScale = 1.0f;
    if(textWidth > ofGetWidth()){
        auto diff = (float)ofGetWidth() / (float)textWidth;
        baseScale = 1.0f * diff;
    }
    
    fontFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
    fontFbo.begin();
    ofClear(0,0,0,0);
    ofPushMatrix();
    ofScale(baseScale, baseScale);
    ofTranslate(ofGetWidth() / baseScale * .5f, ofGetHeight() / baseScale * .5f);
    typeText->drawString(_textData, textWidth * -.5f, textHeight * .5f);
    ofPopMatrix();
    fontFbo.end();
    
    fontFbo.readToPixels(fontPix);

    ofColor c;
    auto paneSizeScaled = paneSize * baseScale;
    auto resoWindowHeight = (float)ofGetHeight()/(float)paneSizeScaled;
    auto resoWindowWidth = (float)ofGetWidth()/(float)paneSizeScaled;
    
    for(int h=0;h<resoWindowHeight;h++){
        for(int w=0;w<resoWindowWidth;w++){
            c = fontPix.getColor(w*paneSizeScaled, h*paneSizeScaled);
            
            if(c.r != 0){
                //printf("c.r:%i, c.g:%i, c.b:%i, c.a:%i \n",c.r,c.g,c.b,c.a);
                //cout << "w:" << w << " h:" << h << " c.r:"<< c.r << " c.g:" << c.g << " c.b:"<< c.b << "\n";
                pane.init(w*paneSizeScaled, h*paneSizeScaled, paneSizeScaled, c);
                panes.push_back(pane);
            }
        }
    }    
    random_shuffle(panes.begin(), panes.end());
}

void Grid::init(string &_textData, ofTrueTypeFont *_typeText){
    panes.clear();
    fontPix.clear();
    typeText = _typeText;

    auto textWidth = typeText->stringWidth(_textData);
    auto textHeight = typeText->stringHeight(_textData);
    
    auto baseScale = 1.0f;
    if(textWidth > ofGetWidth()){
        auto diff = (float)ofGetWidth() / ((float)textWidth + 200.0f);
        baseScale = 1.0f * diff;
    }
    
    fontFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
    fontFbo.begin();
    ofClear(0,0,0,0);
    ofPushMatrix();
    ofScale(baseScale, baseScale);
    ofTranslate(ofGetWidth() / baseScale * .5f, ofGetHeight() / baseScale * .5f);
    typeText->drawString(_textData, textWidth * -.5f, textHeight * .5f);
    ofPopMatrix();
    fontFbo.end();
    
    fontFbo.readToPixels(fontPix);
    
    ofColor c;
    auto paneSizeScaled = paneSize * baseScale;
    auto resoWindowHeight = (float)ofGetHeight()/(float)paneSizeScaled;
    auto resoWindowWidth = (float)ofGetWidth()/(float)paneSizeScaled;
    
    for(int h=0;h<resoWindowHeight;h++){
        for(int w=0;w<resoWindowWidth;w++){
            c = fontPix.getColor(w*paneSizeScaled, h*paneSizeScaled);
            
            if(c.r != 0){
                //printf("c.r:%i, c.g:%i, c.b:%i, c.a:%i \n",c.r,c.g,c.b,c.a);
                //cout << "w:" << w << " h:" << h << " c.r:"<< c.r << " c.g:" << c.g << " c.b:"<< c.b << "\n";
                pane.init(w*paneSizeScaled, h*paneSizeScaled, paneSizeScaled, c);
                panes.push_back(pane);
            }
        }
    }
    random_shuffle(panes.begin(), panes.end());
}

void Grid::draw(){
    for(int i=0;i<panes.size();i++){
        panes[i].draw();
    }
    
    //ofImage image;
    //image.setFromPixels(fontPix);
    //image.draw(0, 0);
}
ofVec2f Grid::getByIndex(int index){
    return ofVec2f(panes[index]._x, panes[index]._y);
}
ofColor Grid::getPanelColor(int index){
    return *panes[index]._c;
}
int Grid::getPanelNumber(){
    return panes.size();
}
int Grid::getPanelSize(){
    return paneSize;
}