#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class Shonyudo{
public:
    void setup();
    void update();
    void draw(float const &_midiEngine);
    void drawGui();
    
    ofShader shader;
    ofShader gizaShader;
    ofxPanel gui;
    ofxFloatSlider g_speed, g_amplitude; //時間のスピードと幅
    float eTime=0;
    
    array<ofPoint,10> bp;

    
    ofxFloatSlider g_fade;
    ofxToggle g_escape;
    ofxToggle g_play;
    
    float width = 800;
    float height = 600;
    
};

