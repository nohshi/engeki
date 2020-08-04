

#include "hisui.hpp"


//--------------------------------------------------------------
void Hisui::setup(){
    fbo.allocate(800,600, GL_RGB, 8);
    fbo.begin();
    ofClear(0,255);
    fbo.end();
    
    gui.setup();
    gui.setName("hisui");
    gui.add(g_play.setup("play", false));
    gui.add(g_fade.setup("fade", 0, 0,1));
    gui.add(g_speed.setup("speed", 0.2, 0,1));
    gui.add(g_color.setup("col", ofColor(66, 244, 155,0), ofColor(0,0), ofColor(255,255)));
    gui.add(g_alph.setup("aplh", 1, 0,1));
}

//--------------------------------------------------------------
void Hisui::update(){
    
    
}

//--------------------------------------------------------------
void Hisui::draw(){
    
    if(g_play){
        eTime += ofGetLastFrameTime() * g_speed;
        
        fbo.begin();
        ofSetColor(0,5);
        ofDrawRectangle(0, 0, fbo.getWidth(),fbo.getHeight());
        
        ofPushMatrix();
        for (int n=0; n<20; n++) {
            float inum = 10;
            ofPushMatrix();
            glm::vec2 t;
            t.x = ofNoise(eTime,  10, n*10) *fbo.getWidth();
            t.y = ofNoise(eTime, 500, n*10) *fbo.getHeight();
            ofTranslate(t);
            for (int i=0; i<inum; i++) {
                glm::vec2 p;
                float R = 100;
                p.x = sin(i/inum *PI*2 +eTime*5) *R;
                p.y = cos(i/inum *PI*2 +eTime*5) *R;
                float radius = 1 + ofNoise(n*100,100)*40;
                ofColor col = g_color;
                ofSetColor(col.r, col.g, col.b, g_fade*255);
                ofDrawCircle(p, radius);
            }
            ofPopMatrix();
        }
        ofPopMatrix();
        fbo.end();
        ofSetColor(255, g_alph*255);
        fbo.draw(0, 0);
    }

}

//--------------------------------------------------------------
void Hisui::drawGui(){
    ofSetColor(255);
    gui.draw();
}

