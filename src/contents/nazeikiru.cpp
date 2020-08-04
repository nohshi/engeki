
#include "nazeikiru.hpp"


//--------------------------------------------------------------
void Nazeikiru::setup(){
    sphere.set(80, 3);
    
    shader.load("nazeikiruSh/dShader");
    soshokuSh.load("nazeikiruSh/soushoku");
    
    gui.setup();
    gui.setName("nazeikiru");
    gui.add(g_play.setup("play", false));
    gui.add(g_volScale.setup("volScale", 0.01, 0.,1.));
    gui.add(g_color.setup("color", glm::vec3(.68,1,1), glm::vec3(0,0,0), glm::vec3(1,1,1)));
    gui.add(g_alph.setup("alph", 1., 0.,1.));
}

//--------------------------------------------------------------
void Nazeikiru::update(){
    
}

//--------------------------------------------------------------
void Nazeikiru::draw(const glm::vec2 &_pos, const float &_volume, const float &_volScale,const float &_alph){
    if (g_play) {
        ofEnableDepthTest();
        
        ofPushMatrix();
        ofTranslate(_pos);
        g_volScale = _volScale;
        this->drawDistSphere(_volume*0.6);
        ofPopMatrix();
        
        ofDisableDepthTest();
        g_alph = _alph;
        ofSetColor(0,(1.-g_alph)*255);
        ofDrawRectangle(0, 0, 800,600);
        
        ofSetColor(255);
    }
}

void Nazeikiru::drawDistSphere(const float &_volume){
    float t = ofGetElapsedTimef();
    ofPushMatrix();
    ofPushStyle();
    shader.begin();
    shader.setUniform1f("u_time", t);
    shader.setUniform1f("u_scale", _volume *g_volScale*200);
    ofSetColor(255);
    sphere.draw();
    shader.end();
    
    ofScale(1.3);
    soshokuSh.begin();
    soshokuSh.setUniform1f("u_time", t);
    soshokuSh.setUniform1f("u_scale", _volume *g_volScale*200);
    ofSetColor(ofColor::fromHsb(ofWrap(t*0.5, 0, 1)*255, g_color->y*255, g_color->z*255));
    sphere.draw();
    soshokuSh.end();
    
    
    ofPopStyle();
    ofPopMatrix();
}

//--------------------------------------------------------------
void Nazeikiru::drawGui(){
    gui.draw();
}


