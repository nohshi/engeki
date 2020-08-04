
#include "guiApp.hpp"


void GuiApp::setup(){
    ofSetWindowTitle("gui");
    displayFbo.allocate(800, 600, GL_RGB, 8);
    //displayFbo.getTextureReference().getTextureData().bFlipTexture = true;
    
    gui.setup();
    gui.setName("main");
    gui.add(g_fade.setup("fade", 0,0,1));
    gui.setPosition(640, 440);
    
    //------------------コンテンツの初期化
    funadenouta.setup();
    mogishiken.setup();
    shaderGraph.setup();
    nazeikiru.setup();
    caribe.setup();
    shonyudo.setup();
    hisui.setup();
    ittenkousei.setup();
    kaninote.setup();
    bokunokotae.setup();
    cloud.setup();
    
    funadenouta.gui.setPosition(10, 40);
    mogishiken.gui.setPosition(220, 40);
    shaderGraph.gui.setPosition(430, 40);
    caribe.gui.setPosition(640, 40);
    shonyudo.gui.setPosition(10, 240);
    kaninote.gui.setPosition(220, 240);
    nazeikiru.gui.setPosition(430, 240);
    hisui.gui.setPosition(640, 240);
    ittenkousei.gui.setPosition(10, 440);
    bokunokotae.gui.setPosition(220, 440);
    cloud.gui.setPosition(430, 440);
    
    //osc
    receiver.setup(8000);
    
    //以下音
    int bufferSize = 256;
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    smoothedVol     = 0.0;
    scaledVol        = 0.0;
    ofSoundStreamSettings settings;
    auto devices = soundStream.getMatchingDevices("default");
    if(!devices.empty()){
        settings.setInDevice(devices[0]);
    }
    settings.setInListener(this);
    settings.sampleRate = 44100;
    settings.numOutputChannels = 0;
    settings.numInputChannels = 2;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);
}

void GuiApp::update(){
    //OSC関連
    if(midi1front==1){
        midi1Engine = midi1/127. + lastMidi1E;
    }else if(midi1front==2){
        midi1Engine = (1-midi1/127.) + lastMidi1E;
    }
    //現在順番待ちのOSCメッセージがあるか確認
    while( receiver.hasWaitingMessages() ){
        //次のメッセージを取得
        ofxOscMessage m;
        receiver.getNextMessage( &m );
        if ( m.getAddress() == "/osc" ){
            midi1 = int(m.getArgAsInt(1));
            if(midi1==0){
                midi1front = 1; //front
                lastMidi1E = midi1Engine;
            }else if(midi1==127){
                midi1front = 2; //back
                lastMidi1E = midi1Engine;
            }
            midi2 = m.getArgAsFloat(2);
            midi3 = m.getArgAsFloat(3);
        }
    }
    
    //lets scale the vol up to a 0-1 range（音のスケーリング）
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    
    
    //--------------------------display用のFBOに書き込む
    displayFbo.begin();
    ofClear(0,255);
    
    funadenouta.draw();
    mogishiken.draw();
    shaderGraph.draw();
    nazeikiru.draw( glm::vec2(ofGetMouseX(),ofGetMouseY()), scaledVol, midi3, midi2 );
    caribe.draw(scaledVol);
    shonyudo.draw(midi1Engine);
    hisui.draw();
    ittenkousei.draw();
    kaninote.draw();
    bokunokotae.draw();
    cloud.draw();
    
    displayFbo.end();
}

void GuiApp::draw(){
    
    //--------------------------display用のFBOに書き込む
    ofSetColor(255);
    displayFbo.draw(0, 0, 800,600);
    
    funadenouta.drawGui();
    mogishiken.drawGui();
    shaderGraph.drawGui();
    nazeikiru.drawGui();
    caribe.drawGui();
    shonyudo.drawGui();
    hisui.drawGui();
    ittenkousei.drawGui();
    kaninote.drawGui();
    bokunokotae.drawGui();
    cloud.drawGui();
    
    gui.draw();
    
    ofDrawBitmapString("fps : " + ofToString(ofGetFrameRate()), 10, 20);
}

//--------------------------------------------------------------
void GuiApp::audioIn(ofSoundBuffer & input){
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (size_t i = 0; i < input.getNumFrames(); i++){
        left[i]        = input[i*2]*0.5;
        right[i]    = input[i*2+1]*0.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
    //this is how we get the mean of rms :)
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
}

//--------------------------------------------------------------
void GuiApp::exit(){
    soundStream.stop();
    receiver.stop();
}

//--------------------------------------------------------------
void GuiApp::keyPressed(int key){
    switch (key) {
        case OF_KEY_RIGHT:
            caribe.bShiftX = 1;
            break;
        case OF_KEY_UP:
            caribe.bShiftY = 1;
            break;
        case OF_KEY_LEFT:
            caribe.bShiftX = 2;
            break;
        case OF_KEY_DOWN:
            caribe.bShiftY = 2;
            break;
        case 'a':
            caribe.rowNum++;
            caribe.rowNum = ofWrap(caribe.rowNum, 0,5);
            break;
            
        case 'q':
            mogishiken.bPop[0] = !mogishiken.bPop[0];
            break;
        case 'w':
            mogishiken.bPop[1] = !mogishiken.bPop[1];
            break;
        case 'e':
            mogishiken.bPop[2] = !mogishiken.bPop[2];
            break;
        case 'r':
            mogishiken.bPop[3] = !mogishiken.bPop[3];
            break;
        case 't':
            mogishiken.bPop[4] = !mogishiken.bPop[4];
            break;
        case 'y':
            mogishiken.bPop[5] = !mogishiken.bPop[5];
            break;
        case 's':
            mogishiken.bPopUp = true;
            break;
            
        case '1':
            ittenkousei.g_state = 1;
            break;
        case '2':
            ittenkousei.g_state = 2;
            break;
        case '3':
            ittenkousei.g_state = 3;
            break;
            
        default:
            break;
    }
    
}

//--------------------------------------------------------------
void GuiApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void GuiApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void GuiApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void GuiApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void GuiApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void GuiApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void GuiApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void GuiApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void GuiApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void GuiApp::dragEvent(ofDragInfo dragInfo){
    
}



