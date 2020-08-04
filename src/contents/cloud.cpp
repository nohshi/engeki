//
//  cloud.cpp
//  honban
//
//  Created by 藤田　恭輔 on 2019/03/22.
//

#include "cloud.hpp"

//--------------------------------------------------------------
void Cloud::setup(){
    shader.load("cloudSh/cloud");
    
    this->setupGui();
}

//--------------------------------------------------------------
void Cloud::setupGui(){
    
    gui.setup();
    gui.setName("cloud");
    gui.add(g_play.setup("play", false));
    gui.add(g_fade.setup("fade", 0, 0, 1));
    gui.add(g_speed.setup("speed", 1, 0, 2));
    gui.add(g_color.setup("color", ofColor(0.925*255,0.193*255,0.237*255), ofColor(0), ofColor(255)));

}
//--------------------------------------------------------------
void Cloud::update(){
    
}

//--------------------------------------------------------------
void Cloud::draw(){
    if (g_play) {
        eTime += ofGetLastFrameTime() * g_speed;
        
        ofPushStyle();
        ofColor col = g_color;
        ofSetColor(col.r,col.g,col.b, g_fade*255);
        shader.begin();
        shader.setUniform1f("u_time", eTime);
        shader.setUniform2f("u_resolution", 800, 600);
        ofDrawRectangle(0,0, 800, 600);
        shader.end();
        ofPopStyle();
    }
}

//--------------------------------------------------------------
void Cloud::drawGui(){
    gui.draw();
}
    
    
    
    
    




