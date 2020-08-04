//
//  kaninote.cpp
//  caribe-shonyudo
//
//  Created by 藤田　恭輔 on 2019/03/21.
//

#include "kaninote.hpp"

//--------------------------------------------------------------
void Kaninote::setup(){
    
    lineShader.load("kaninoteSh/lineDist");
    img.load("kaninote.png");
    img.resize(800, 600);
    
    this->setupGui();
}


//--------------------------------------------------------------
void Kaninote::setupGui(){
    gui.setup();
    gui.setName("kaninote");
    gui.add( g_play.setup("play", false) );
    gui.add( g_wind.setup("wind", 0.08, 0,1) );
    gui.add( g_fade.setup("fade", 0.0, 0,1) );
    gui.add( g_speed.setup("speed", 0.25, 0,1) );
}

//--------------------------------------------------------------
void Kaninote::update(){
    
}

//--------------------------------------------------------------
void Kaninote::draw(){
    ofPushStyle();
    
    ofSetColor(255,g_fade*255);
    if(g_fade>0.01 && g_play==true){
        eTime += ofGetLastFrameTime() * g_speed;
        lineShader.begin();
        lineShader.setUniform1f("u_time", eTime);
        lineShader.setUniform2f("u_resolution", 800, 600);
        lineShader.setUniformTexture("u_img", img.getTexture(), 1);
        lineShader.setUniform1f("u_wind", g_wind);
        ofDrawRectangle(0,0, 800, 600);
        lineShader.end();
    }
    
    ofPopStyle();
}

//--------------------------------------------------------------

void Kaninote::drawGui(){
    ofSetColor(255);
    gui.draw();
}


