#include "ofMain.h"
#include "ofApp.h"
#include "guiApp.hpp"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3,2);
    
    //外部モニターに表示するためのウィンドウ
    settings.setSize(800, 600);
    settings.setPosition(ofVec2f(300,0));
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    
    //GUIなどを表示するウィンドウ
    settings.setSize(850, 690);
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = true;
    settings.shareContextWith = mainWindow;
    shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);
    
    //両者のオブジェクトを共有するためのポインタ
    shared_ptr<ofApp> mainApp(new ofApp);
    shared_ptr<GuiApp> guiApp(new GuiApp);
    mainApp->guiObj = guiApp;
    
    //ループスタート
    ofRunApp(guiWindow, guiApp);
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
    
}
