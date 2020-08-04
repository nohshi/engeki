//
//  melt.cpp
//  boku-no-kotae2
//
//  Created by 藤田　恭輔 on 2019/03/10.
//

#include "melt.hpp"

void Melt::setup(const int &_width, const int &_height){
    for (int i=0; i<2; i++) {
        fbFbo[i].allocate(_width, _height, GL_RGB32F);
        fbFbo[i].begin();
        ofClear(0,0,0,255);
        fbFbo[i].end();
    }
    shader.load("meltShaders/melt");
    
}

void Melt::begin(){
    fbFbo[0].begin();
}

void Melt::end(){
    fbFbo[0].end();
}

void Melt::draw(const float &_val){
    fbFbo[1].begin();
    shader.begin();
    // here is where the fbo is passed to the shader
    shader.setUniformTexture("fbtex1", fbFbo[0].getTexture(), 1 );
    shader.setUniformTexture("fbtex2", fbFbo[1].getTexture(), 2 );
    shader.setUniform1f("time", ofGetElapsedTimef()*3);
    shader.setUniform1f("u_val", _val);
    //ofDrawRectangle(0,0, ofGetWidth(),ofGetHeight());
    fbFbo[0].draw(0,0);
    shader.end();
    fbFbo[1].end();
    
    fbFbo[1].draw(0,0);
    swap(fbFbo[0], fbFbo[1]); //二つのfboの中身を入れ替える
}

void Melt::drawGui(){
    ofPushStyle();
    gui.draw();
    ofPopStyle();
}

