#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class Cloud {
public:
    void setup();
    void update();
    void draw();
    void setupGui();
    void drawGui();
    
    ofShader shader;
    
    ofxPanel gui;
    ofxToggle g_play;
    ofxColorSlider g_color;
    ofxFloatSlider g_fade, g_speed;
    float eTime = 0;
};
