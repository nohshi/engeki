#pragma once

#include "ofMain.h"
#include "ofxGui.h"


class Ittenkousei {
public:
    void setup();
    void update();
    void draw();
    void drawGui();
    
    ofPlanePrimitive plane;
    ofShader shader;
    
    ofxPanel gui;
    ofxFloatSlider amp, speed, g_fade;
    ofxToggle g_play;
    ofxIntSlider g_state;
    float eTime=0;
    
};


