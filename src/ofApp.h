#pragma once

#include "ofMain.h"
#include "guiApp.hpp"

class ofApp : public ofBaseApp{

	public:
        void setup(); //初期化
        void update(); //毎フレーム呼ばれるやつ
        void draw(); //毎フレーム呼ばれるやつ、メインディスプレイへの描画用

        //以下マウス、キーイベント関数
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    //guiオブジェクトのポインタ
    shared_ptr<GuiApp> guiObj;
    
};
