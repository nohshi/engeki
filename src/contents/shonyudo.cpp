//
//  shonyudo.cpp
//  caribe-shonyudo
//
//  Created by 藤田　恭輔 on 2019/03/21.
//

#include "shonyudo.hpp"

//--------------------------------------------------------------
void Shonyudo::setup(){
    shader.load("shonyudoSh/shaderGraph1");
    gizaShader.load("shonyudoSh/giza");
    gui.setup();
    gui.setName("shonyudo");
    gui.add(g_play.setup("play", false));
    gui.add(g_speed.setup("speed", 1., 0, 4));
    gui.add(g_amplitude.setup("amplitude", .25, 0, 1));
    gui.add( g_fade.setup("fade", 0.0, 0,1) );
    gui.add(g_escape.setup("escape", false));
}

//--------------------------------------------------------------
void Shonyudo::update(){
    
    
    
}

//--------------------------------------------------------------
void Shonyudo::draw(float const &_midiEngine){
    ofPushStyle();
    
    if(g_fade>0.01 && g_play==true){
        eTime += ofGetLastFrameTime()*g_speed;
        
        array<float, 20> ballPos;
        int num = 10;
        for (int i=0; i<bp.size(); i++) {
            ofSetColor(255);
            float time = _midiEngine;
            float atime = ofWrap(time, 0, 1);
            //atime = 1. - pow(abs(atime-1.),4.);
            time = floor(time) + atime;
            time *= 0.5;
            
            if (!g_escape) {
                bp[i].x = ofSignedNoise(time+i*10., 100.) * 400 * g_amplitude;
                bp[i].y = ofSignedNoise(time+i*10., 800.) * 400 * g_amplitude;
                bp[i].x += width/2 * width/height;
                bp[i].y += height/2;
            }else{
                bp[i] += (bp[i]-ofPoint(width/2,height/2)).getNormalized() * 10.;
            }
            ballPos[2*i] = bp[i].x/width;
            ballPos[2*i+1] = bp[i].y/height;
        }
        
        
        ofSetColor(255, g_fade*255);
        shader.begin();
        shader.setUniform2f("u_windowSize", width,height);
        shader.setUniform1f("u_time", ofGetElapsedTimef());
        shader.setUniform2fv("u_bPos", ballPos.data(),10);
        ofDrawRectangle(0, 0, width, height);
        shader.end();
        
        if (!g_escape) {
            gizaShader.begin();
            gizaShader.setUniform2f("u_windowSize", width,height);
            gizaShader.setUniform1f("u_time", ofGetElapsedTimef());
            ofDrawRectangle(0, 0, width, height);
            gizaShader.end();
        }
        
    }
    
    
    ofPopStyle();
}



void Shonyudo::drawGui(){
    ofSetColor(255);
    gui.draw();
}







