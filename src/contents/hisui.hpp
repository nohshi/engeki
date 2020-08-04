#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class Hisui{
public:
    void setup();
    void update();
    void draw();
    void drawGui();
    
    
    ofxPanel gui;
    ofxFloatSlider g_fade, g_speed, g_alph;
    float eTime;
    ofxColorSlider g_color;
    ofxToggle g_play;
    
    ofFbo fbo;
};

