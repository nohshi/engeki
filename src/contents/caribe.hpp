#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class Caribe{
public:
    void setup();
    void update();
    void draw(const float &_vol);
    void setupGui();
    void drawGui();
    
    glm::vec3 myGrad(float p);
    void drawRect();
    void drawBox();
    float eTime;
    glm::vec2 shiftEngine;
    int bShiftX = 0;
    int bShiftY = 0;
    int rowNum = 0;
    
    ofFbo fbo;
    ofShader convergenceSh;
    
    ofShader rectCol;
    ofPlanePrimitive rect;
    ofShader boxCol;
    ofBoxPrimitive box;
    ofCamera cam;
    glm::vec3 camPos;
    
    ofxPanel gui;
    ofxFloatSlider g_scale;
    ofxFloatSlider g_fade;
    ofxToggle g_play, g_scene2;
    
};

