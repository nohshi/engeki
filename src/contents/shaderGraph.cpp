#include "shaderGraph.hpp"

//--------------------------------------------------------------
void ShaderGraph::setup(){
    shader.load("shaderGraph/shaderGraph1");
    gui.setup();
    gui.setName("shaderGraph");
    gui.add(g_play.setup("play",false));
    gui.add(g_fade.setup("fade", 0, 0,1));
}

//--------------------------------------------------------------
void ShaderGraph::update(){
    
}

//--------------------------------------------------------------
void ShaderGraph::draw(){
    if (g_play) {
        ofSetColor(255, g_fade*255);
        shader.begin();
        shader.setUniform1f("u_time", ofGetElapsedTimef());
        shader.setUniform2f("u_resolution", 800,600);
        ofDrawRectangle(0,0, 800,600);
        shader.end();
    }
    
}

//--------------------------------------------------------------
void ShaderGraph::drawGui(){
    gui.draw();
}


