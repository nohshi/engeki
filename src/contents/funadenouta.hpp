#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class Funade {
public:
    void setup();
    void update();
    void draw();
    void drawGui();
    
    ofVboMesh mesh;
    ofPlanePrimitive plane;
    ofShader shader;
    
    ofxPanel gui;
    ofxFloatSlider  speed, asahiY;
    
    float eTime;
    
    ofShader asahiShader;
    
    ofShader blackCartainSh; //black out cartain
    ofxFloatSlider cartainEdge;
    ofxToggle g_play;
};

