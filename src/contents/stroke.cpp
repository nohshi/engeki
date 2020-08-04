//
//  stroke.cpp
//  honban
//
//  Created by 藤田　恭輔 on 2019/03/22.
//

#include "stroke.hpp"

Stroke::Stroke(const float &_x, const float &_y, const ofColor &_col){
    
    pos.x = _x;
    pos.y = _y;
    sir = ofRandom(255);
    id = ofRandom(1);
    color = _col;
}



void Stroke::draw(){
    ofPushMatrix();
    
    glm::vec2 v;
    float amp = 0.001;
    v.x = ofSignedNoise(pos.x*amp, pos.y*amp, 900);
    v.y = ofSignedNoise(pos.x*amp, pos.y*amp, 9800);
    
    v = glm::normalize(v)*1;
    pos += v;
    
    ofTranslate(pos);
    
    ofPushStyle();
    ofPushMatrix();
    /*
     //でかい円の表示
     ofSetColor(0);
     ofNoFill();
     ofDrawCircle(0,0, R);
     */
    //ofSetColor( 200 + 55 * ofClamp(lifeSpan/float(maxLifeSpan),0,1) );
    ofSetColor(255);
    int inum = 25;
    ofFill();
    float range = this->myWave2(1-lifeSpan/float(maxLifeSpan)) * R;
    for (int i=0; i<inum; i++) {
        float l = ofSignedNoise(i*100, 600, id*500) * range;
        float theta = ofSignedNoise(i*100, 1990, id*500) * PI;
        glm::vec2 lpos; //local position
        lpos.x = sin(theta) * l;
        lpos.y = cos(theta) * l;
        float r = ofNoise(i*100, 6000, id*500) * 1;
        if (lifeSpan - ofNoise(i*100, 6700)*maxLifeSpan/1.5 > 0) {
            r *= 2;
            r *= sin(PI/2*(1-lifeSpan/float(maxLifeSpan))  + PI/2);
            //ofSetColor(ofColor::fromHsb(250,hue,225+30*ofNoise(i*100,68)));
            ofColor col = color;
            col.setBrightness(color.getBrightness()+30*ofSignedNoise(i*100,68));
            ofSetColor(col);
            ofDrawCircle(lpos, r);
        }
    }
    
    
    ofPopMatrix();
    ofPopStyle();
    lifeSpan -= 1;
    ofPopMatrix();
}

float Stroke::myWave(const float &_x){ //_x=0~1
    float x = (_x - 0.5) * 2;
    float y;
    if (x < 0) {
        y = 1 - pow( abs(sin(PI * x/2)), 2.5 );
    }else{
        y = pow( cos(PI * x/2), 2 );
    }
    return y;
}

float Stroke::myWave2(float _x){ //0~1
    float y;
    _x = ofClamp(_x, 0, 1);
    //float theta = PI * _x;
    float a = 0.2;
    if(_x < a){
        y = sin(PI/2 * _x/a)*1. + 0.;
    }else {
        y = sin(PI/2 * (_x-a)/(1-a)  +PI/2)*0.6 + 0.4;
    }
    return y;
}
