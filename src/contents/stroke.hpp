#pragma once

#include "ofMain.h"

class Stroke {
public:
    Stroke(const float &_x, const float &_y, const ofColor &_col);
    void draw();
    float myWave(const float &_x);
    float myWave2(float _x);
    
    float R = 7; //でかい円の半径（総体の大きさ）
    glm::vec2 pos; //でかい円の位置
    int lifeSpan = 40; //でかい円の寿命（小さい円それぞれの寿命の平均？？）
    int maxLifeSpan = lifeSpan;
    float sir;
    float id;
    ofColor color;
};
