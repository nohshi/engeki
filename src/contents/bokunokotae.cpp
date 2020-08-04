//
//  bokunokotae.cpp
//  honban
//
//  Created by 藤田　恭輔 on 2019/03/22.
//

#include "bokunokotae.hpp"


//--------------------------------------------------------------
void Bokunokotae::setup(){
    fbo.allocate(800,600, GL_RGB32F);
    fbo.begin();
    ofClear(0,255);
    fbo.end();
    fbo.getTextureReference().getTextureData().bFlipTexture = true;
    
    img.load("ore.jpg");
    img.resize(600*232./293, 600); //232/293
    img.setAnchorPercent(0.5, 0.);
    kaoFbo.allocate(800,600, GL_RGB);
    kaoFbo.begin();
    ofClear(0,255);
    img.draw(kaoFbo.getWidth()/2, 0);
    kaoFbo.end();
    kaoFbo.readToPixels(imgPix);
    
    melt.setup(fbo.getWidth(), fbo.getHeight());
    
    gui.setup();
    gui.setName("bokunokotae");
    gui.add(g_play.setup("play",false));
    gui.add(g_enog.setup("enog",false));
    gui.add(g_melt.setup("melt",false));
    gui.add(g_val.setup("meltVal",0,0,1));
    gui.add(g_freq.setup("freq", -30, -50, 8));
    gui.add(g_fade.setup("fade", 0, 0, 1));
    gui.add(g_clear.setup("clear"));
}

//--------------------------------------------------------------
void Bokunokotae::update(){
    
    
}

//--------------------------------------------------------------
void Bokunokotae::draw(){
    if (g_clear) {
        fbo.begin();
        ofClear(0,255);
        fbo.end();
    }
    
    if (g_play) {
    
        if (g_freq<=-1) {
            if (ofGetFrameNum()%int(-g_freq)==0 && g_enog){
                glm::vec2 p;
                p.x = ofGetWidth()/2-img.getWidth()/2 + ofRandom(img.getWidth()+10);
                p.y = ofRandom(img.getHeight());
                ofColor col = imgPix.getColor(int(p.x), int(p.y));
                stroke.emplace_back(p.x,p.y,col);
            }
        }else{
            if (g_enog){
                for (int i=0; i<g_freq; i++) {
                    glm::vec2 p;
                    p.x = ofGetWidth()/2-img.getWidth()/2 + ofRandom(img.getWidth()+10);
                    p.y = ofRandom(img.getHeight());
                    ofColor col = imgPix.getColor(int(p.x), int(p.y));
                    stroke.emplace_back(p.x,p.y,col);
                }
            }
        }
        
        for (int n=0; n<stroke.size(); n++) {
            if (stroke[n].lifeSpan<0) {
                stroke.pop_front();
            }
        }
    
        //draw
        ofSetColor(255);
        fbo.begin();
        for (int n=0; n<stroke.size(); n++) {
            for (int i=0; i<3; i++) {
                stroke[n].draw();
            }
        }
        fbo.end();
        if( !g_melt ){
            melt.begin();
            fbo.draw(0,0);
            melt.end();
            fbo.draw(0,0);
        }
        if( g_melt ){
            melt.draw(g_val);
        }
        ofSetColor(0, g_fade*255);
        ofDrawRectangle(0,0, 800, 600);
        
    }

}


void Bokunokotae::drawGui(){
    ofSetColor(255);
    gui.draw();
}
