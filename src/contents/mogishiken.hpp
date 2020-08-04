#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"

class Mogishiken {
public:
    void setup();
    void update();
    void draw();
    void drawGui();
    
    vector< string > separateUTF8String( string _srcStr );
    glm::vec3 transform1(const float &_time, const float &_radius, const int &_num, const int &_i, const int &_n);
    glm::vec3 transform2(const float &_time, const float &_radius, const int &_num, const int &_i, const int &_n);
    
    ofTrueTypeFont font;
    ofBuffer buffer;
    float timeMultDelt = 0;
    
    string words;
    vector< string > splitedWords;
    
    ofEasyCam easyCam;
    ofCamera cam[2];
    
    ofxPanel gui;
    ofxFloatSlider g_slide, g_fade, g_speed;
    ofxFloatSlider g_size, g_PI;
    ofxToggle g_play, g_scene;
    
    
    ofLight light;
    ofVboMesh mesh[6];
    bool bPop[6];
    float popEngine[6];
    bool bPopUp = false;
    float popUpEngine = 0;
};
