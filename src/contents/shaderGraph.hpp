#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ShaderGraph {
    
public:
    void setup();
    void update();
    void draw();
    void drawGui();
    
    
    
    ofShader shader;
    
    ofxPanel gui;
    ofxFloatSlider g_fade;
    ofxToggle g_play;
};
