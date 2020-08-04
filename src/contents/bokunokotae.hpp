#pragma once

#include "ofMain.h"
#include "stroke.hpp"
#include "melt.hpp"
#include "ofxGui.h"

class Bokunokotae {
    
public:
    void setup();
    void update();
    void draw();
    void drawGui();
    
    
    
    deque<Stroke> stroke;
    ofImage img;
    ofPixels imgPix;
    
    ofFbo fbo;
    ofFbo kaoFbo;
    
    Melt melt;
    
    ofxPanel gui;
    ofxFloatSlider g_freq; //点を打つ頻度
    ofxFloatSlider g_fade, g_val;//valは溶ける速さ
    
    ofxToggle g_play, g_enog, g_melt;
    ofxButton g_clear;
};
