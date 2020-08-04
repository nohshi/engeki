#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class Nazeikiru{
public:
    void setup();
    void update();
    void draw(const glm::vec2 &_pos, const float &_volume, const float &_volScale, const float &_alph);
    void drawGui();
    
    ofIcoSpherePrimitive sphere;
    ofShader shader;
    ofShader soshokuSh;
    
    ofxPanel gui;
    ofxFloatSlider g_volScale;
    ofxVec3Slider g_color;
    ofxFloatSlider g_alph;
    ofxToggle g_play;
    //glm::vec3 color(.68,1,1);
    
    
    void drawDistSphere(const float &_volume);
};

