#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class Melt {
public:
    
    
    void begin();
    void end();
    void setup(const int &_width, const int &_height);
    void draw(const float &_val);
    void drawGui();
    
    ofShader shader;
    ofFbo fbFbo[2];
    
    ofxPanel gui;
    ofxFloatSlider g_val;
};
