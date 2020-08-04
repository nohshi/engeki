#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class Kaninote{
public:
    void setup();
    void update();
    void draw();
    void setupGui();
    void drawGui();
    
    ofShader lineShader;
    ofImage img;
    
    ofxPanel gui;
    ofxFloatSlider g_wind;
    ofxFloatSlider g_fade;
    ofxFloatSlider g_speed;
    ofxToggle g_play;
    
    float eTime=0;
};


