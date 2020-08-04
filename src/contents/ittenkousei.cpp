

#include "ittenkousei.hpp"

//--------------------------------------------------------------
void Ittenkousei::setup(){
    shader.load("ittenkouseiSh/shader");
    
    gui.setup();
    gui.setName("ittenkousei");
    gui.add(g_play.setup("play", false));
    gui.add(g_state.setup("state", 1, 1, 3));
    gui.add(amp.setup("amp", 0.025, 0, 10));
    gui.add(speed.setup("speed", 1, 0, 4));
    gui.add(g_fade.setup("fade", 0, 0, 1));
    
    
    
}

//--------------------------------------------------------------
void Ittenkousei::update(){
    
    
}

//--------------------------------------------------------------
void Ittenkousei::draw(){
    
    if (g_play) {
        ofPushStyle();
        eTime += ofGetLastFrameTime()*speed;
        
        ofSetColor(255, g_fade*255);
        if(g_fade>0.01){
            shader.begin();
            shader.setUniform1f("u_time", eTime);
            shader.setUniform1f("u_time2", ofGetElapsedTimef()*0.8);
            shader.setUniform2f("u_windowSize", 800, 600);
            shader.setUniform1i("u_state", g_state);
            ofDrawRectangle(0,0, 800, 600);
            shader.end();
        }
        ofPopStyle();
    }
    
}


//--------------------------------------------------------------
void Ittenkousei::drawGui(){
    ofSetColor(255);
    gui.draw();
}

