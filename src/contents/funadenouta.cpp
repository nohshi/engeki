//
//  cloud.cpp
//  honban
//
//  Created by 藤田　恭輔 on 2019/03/22.
//

#include "funadenouta.hpp"

//--------------------------------------------------------------
void Funade::setup(){
    shader.load("funadeSh/shader");
    
    
    gui.setup();
    gui.setName("funadenouta");
    gui.add(g_play.setup("play", false));
    gui.add(speed.setup("speed", .4, 0, 1));
    gui.add(asahiY.setup("asahiY", -0.3, -2, .7));
    gui.add(cartainEdge.setup("cartainEdge", 0, 0,1));
    
    plane.set(2000, 2000, 60, 60);

    
    asahiShader.load("funadeSh/asahi");
    blackCartainSh.load("funadeSh/cartain");
    
}

//--------------------------------------------------------------
void Funade::update(){
    
}

//--------------------------------------------------------------
void Funade::draw(){
    if (g_play) {
        eTime += ofGetLastFrameTime()*speed;
        
        ofSetColor(255);
        //ofDrawSphere(ofGetWidth()/2, ofGetHeight() - 100*asahiY, 150);
        asahiShader.begin();
        asahiShader.setUniform1f("u_time", eTime);
        asahiShader.setUniform2f("u_windowSize", ofGetWidth(),ofGetHeight());
        asahiShader.setUniform1f("u_asahiY", asahiY);
        ofDrawRectangle(0,0, ofGetWidth(), ofGetHeight());
        asahiShader.end();
        
        ofEnableDepthTest();
        shader.begin();
        shader.setUniform1f("u_time", eTime);
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2+150);
        ofRotateX(90);
        glm::vec3 blue(100,127,255);
        ofSetColor(blue.r,blue.g,blue.b);
        plane.drawFaces();
        glm::vec3 white(255);
        glm::vec3 col = glm::mix(white, blue, 0.5);
        ofSetColor(col.r,col.g,col.b);
        plane.drawWireframe();
        ofPopMatrix();
        shader.end();
        ofDisableDepthTest();
        
        blackCartainSh.begin();
        blackCartainSh.setUniform1f("u_edge", cartainEdge);
        blackCartainSh.setUniform2f("u_windowSize", ofGetWidth(),ofGetHeight());
        ofDrawRectangle(0,0, ofGetWidth(), ofGetHeight());
        blackCartainSh.end();
    }
}

//--------------------------------------------------------------
void Funade::drawGui(){
    gui.draw();
}


