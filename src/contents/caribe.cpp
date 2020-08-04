
#include "caribe.hpp"

//--------------------------------------------------------------
void Caribe::setup(){
    
    fbo.allocate(800, 600, GL_RGB);
    convergenceSh.load("caribeSh/convergence");
    rectCol.load("caribeSh/rectCol");
    boxCol.load("caribeSh/boxCol");
    
    rect.set(1, 1, 2, 2);
    box.set(1, 1, 1, 2, 2, 2);
    
    cam.setFarClip(5000);
    camPos = glm::vec3(400);
    cam.setPosition(camPos);
    cam.lookAt(glm::vec3(0));
    
    
    this->setupGui();
}

//--------------------------------------------------------------
void Caribe::setupGui(){
    
    gui.setup();
    gui.setName("caribe");
    gui.add( g_play.setup("play", false) );
    gui.add(g_scale.setup("caribe/volScale", 1., 0,40));
    gui.add( g_fade.setup("fade", 0.0, 0,1) );
    gui.add( g_scene2.setup("scene2", false) );
}

//--------------------------------------------------------------
void Caribe::update(){
    
}

//--------------------------------------------------------------
void Caribe::draw(const float &_vol){
    
    ofPushStyle();
    
    glm::vec2 shift;
    shift.x = ofWrap(shiftEngine.x*100, 0,200);
    shift.y = ofWrap(shiftEngine.y*100, 0,200);
    
    if(g_fade>0.01 && g_play==true){
        eTime = ofGetElapsedTimef();
        if ( bShiftX==1 ) shiftEngine.x += ofGetLastFrameTime();
        if ( bShiftY==1 ) shiftEngine.y += ofGetLastFrameTime();
        if ( bShiftX==2 ) shiftEngine.x -= ofGetLastFrameTime();
        if ( bShiftY==2 ) shiftEngine.y -= ofGetLastFrameTime();
        
        fbo.begin();
        ofClear(0);
        if (!g_scene2) {
            ofPushMatrix();
            ofSetRectMode(OF_RECTMODE_CENTER);
            float nnum = rowNum;
            for (int n=0; n<nnum; n++) {
                float inum = 5;
                for (int i=0; i<inum; i++) {
                    ofPushMatrix();
                    ofSetColor(255, 255, 255);
                    glm::vec2 p(0,0);
                    p.x = -100 + 200 * i +shift.x;
                    p.y = -100 + 200 * n +shift.y;
                    ofTranslate(p);
                    float eTimeR = ofWrap(eTime, 0, PI/2);
                    float deg = sin(eTimeR)*sin(eTimeR)*180;
                    ofRotateDeg(deg);
                    float ookisaFase = 0 * PI*2;
                    float ookisa = sin(eTime+ookisaFase)*sin(eTime+ookisaFase)*200;
                    ofScale(ookisa);
                    this->drawRect();
                    ofPopMatrix();
                }
            }
            nnum = rowNum+1;
            for (int n=0; n<nnum; n++) {
                float inum = 6;
                for (int i=0; i<inum; i++) {
                    ofPushMatrix();
                    ofSetColor(255, 255, 255);
                    glm::vec2 p(0,0);
                    p.x =  200 * (i-1) +shift.x;
                    p.y =  200 * (n-1) +shift.y;
                    ofTranslate(p);
                    float eTimeR = ofWrap(eTime, 0, PI/2);
                    float deg = sin(eTimeR)*sin(eTimeR)*180;
                    ofRotateDeg(deg);
                    float ookisaFase = PI/2;
                    float ookisa = sin(eTime+ookisaFase)*sin(eTime+ookisaFase)*200;
                    ofScale(ookisa);
                    this->drawRect();
                    ofPopMatrix();
                }
            }
            ofPopMatrix();
        }else{
            
            ofEnableDepthTest();
            ofPushMatrix();
            cam.begin();
            ofRotateDeg(eTime*30, 1, 1, 0);
            ofRotateDeg(eTime*10, 0, 0, 1);
            
            float row = 7;
            for (int i=0; i<row; i++) {
                for (int n=0; n<row; n++) {
                    for (int m=0; m<row; m++) {
                        ofPushMatrix();
                        ofSetColor(255, 255, 255);
                        glm::vec3 p(0);
                        p.x =  200 * i -700;
                        p.y =  200 * n -700;
                        p.z =  200 * m -700;
                        ofTranslate(p);
                        float eTimeR = ofWrap(eTime*1.2, 0, PI/2);
                        float radian = sin(eTimeR)*sin(eTimeR);
                        ofRotateDeg(radian*180, 0, 1, radian);
                        float ookisaFase = 0;
                        float ookisa = sin(eTime*1.2+ookisaFase)*sin(eTime*1.2+ookisaFase)*100;
                        ofScale(ookisa);
                        this->drawBox();
                        ofPopMatrix();
                    }
                }
            }
            row = 6;
            for (int i=0; i<row; i++) {
                for (int n=0; n<row; n++) {
                    for (int m=0; m<row; m++) {
                        ofPushMatrix();
                        ofSetColor(255, 255, 255);
                        glm::vec3 p(0);
                        p.x =  200 * i -700 + 100;
                        p.y =  200 * n -700 + 100;;
                        p.z =  200 * m -700 + 100;;
                        ofTranslate(p);
                        float eTimeR = ofWrap(eTime*1.2, 0, PI/2);
                        float radian = sin(eTimeR)*sin(eTimeR);
                        ofRotateDeg(radian*180, 0, 1, radian);
                        float ookisaFase = PI/2;
                        float ookisa = sin(eTime*1.2+ookisaFase)*sin(eTime*1.2+ookisaFase)*100;
                        ofScale(ookisa);
                        this->drawBox();
                        ofPopMatrix();
                    }
                }
            }
            
            cam.end();
            ofPopMatrix();
            ofDisableDepthTest();
        }
        
        fbo.end();
        
        ofSetColor(255,g_fade*255);
        convergenceSh.begin();
        convergenceSh.setUniform1f("u_audioVol", _vol*g_scale);
        fbo.draw(0,0);
        convergenceSh.end();
    }
    
    ofPopStyle();
}

void Caribe::drawRect(){
    rectCol.begin();
    rectCol.setUniform1f("u_time", eTime);
    rectCol.setUniform2f("u_resolution", 800,600);
    rect.draw();
    rectCol.end();
}

void Caribe::drawBox(){
    boxCol.begin();
    boxCol.setUniform1f("u_time", eTime);
    boxCol.setUniform2f("u_resolution", 800,600);
    box.draw();
    boxCol.end();
}

glm::vec3 Caribe::myGrad(float p){
    glm::vec3 orange = glm::vec3(0.980,0.464,0.167);
    glm::vec3 yellow = glm::vec3(1.,1.,0.);
    glm::vec3 green = glm::vec3(.2, 1., 0.);
    glm::vec3 blue = glm::vec3(0, .22, 1.);
    
    p = glm::fract(p);
    p = p * 3.;
    glm::vec3 col;
    if(0.<=p && p<.5){
        col = mix(orange, yellow ,glm::fract(p)*2.);
    }else if(.5<=p && p<1.5){
        col = mix(yellow, green ,glm::fract(p-.5));
    }else if(1.5<=p && p<2.5){
        col = mix(green, blue ,glm::fract(p-.5));
    }else if(2.5<=p && p<=3.){
        col = mix(blue, orange ,(glm::fract(p)-0.5)*2.);
    }
    return col*255;
}


void Caribe::drawGui(){
    ofSetColor(255);
    gui.draw();
}


