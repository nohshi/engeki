
#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"


#include "funadenouta.hpp"
#include "mogishiken.hpp"
#include "shaderGraph.hpp"
#include "nazeikiru.hpp"
#include "caribe.hpp"
#include "shonyudo.hpp"
#include "hisui.hpp"
#include "ittenkousei.hpp"
#include "kaninote.hpp"
#include "bokunokotae.hpp"
#include "cloud.hpp"

class GuiApp: public ofBaseApp {
public:
    void setup(); //初期化
    void update(); //毎フレーム呼ばれるやつ
    void draw(); //毎フレーム呼ばれるやつ、メインディスプレイへの描画用
    void exit(); //終了時に呼ばれるやつ
    
    //以下マウス、キーイベント関数
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    //OSC
    ofxOscReceiver  receiver;
    int midi1 = 0;
    int midi1front = 1;
    float midi1Engine = 0;
    float lastMidi1E = 0; //lastmidi1Engine
    float midi2 = 0;
    float midi3 = 0;
    
    //音
    void audioIn(ofSoundBuffer & input); //音の処理
    vector <float> left;
    vector <float> right;
    float smoothedVol;
    float scaledVol;
    ofSoundStream soundStream;
    
    //display用のFBO
    ofFbo displayFbo;
    
    //コンテンツ
    Funade funadenouta;
    Mogishiken mogishiken;
    ShaderGraph shaderGraph;
    Nazeikiru nazeikiru;
    Caribe caribe;
    Shonyudo shonyudo;
    Hisui hisui;
    Ittenkousei ittenkousei;
    Kaninote kaninote;
    Bokunokotae bokunokotae;
    Cloud cloud;
    
    //gui
    ofxPanel gui;
    ofxFloatSlider g_fade;
    
};


