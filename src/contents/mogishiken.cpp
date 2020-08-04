
#include "mogishiken.hpp"


//--------------------------------------------------------------
void Mogishiken::setup(){
    //  for Japanese Text
    ofTrueTypeFontSettings settings("SourceHanSans-Medium.otf", 30);
    settings.contours = true;
    settings.addRanges(ofAlphabet::Latin);
    settings.addRanges(ofAlphabet::Japanese);//日本語
    settings.addRange(ofUnicode::Latin1Supplement);//記号、アクサン付き文字など
    settings.addRange(ofUnicode::NumberForms);//数字？
    settings.addRange(ofUnicode::MathOperators);//数式記号
    settings.addRange(ofUnicode::Katakana);//カタカナ
    settings.addRange(ofUnicode::Arrows);//矢印
    font.load(settings);
    
    buffer = ofBufferFromFile("uuu.txt");
    
    words = buffer.getText();
    splitedWords = separateUTF8String(words);
    
    gui.setup();
    gui.setName("mogishiken");
    gui.add(g_play.setup("play", false));
    gui.add(g_scene.setup("scene", false));
    gui.add(g_slide.setup("slide", 0, 0, 1.));
    gui.add(g_fade.setup("fade", .0, 0, 1.));
    gui.add(g_speed.setup("speed", 1., 0., 4.));
    gui.add(g_size.setup("size", 1, 0, 1));
    gui.add(g_PI.setup("PI", 0.1, 0, 1));
    
    cam[0].setPosition(-56, 178, 509);
    cam[0].lookAt(glm::vec3(0.1, 0.67, -0.73)*1000);
    cam[0].setFarClip(5000);
    
    cam[1].setPosition(-56, 178, 609);
    cam[1].lookAt(glm::vec3(0.1, 0.67, -0.73)*1000);
    cam[1].setFarClip(5000);
    
    
    //adventureのやつ
    ofxAssimpModelLoader model;
    model.loadModel("3dmodels/adventure1.obj");
    mesh[0] = model.getMesh(0);
    model.loadModel("3dmodels/adventure2.obj");
    mesh[1] = model.getMesh(0);
    model.loadModel("3dmodels/adventure3.obj");
    mesh[2] = model.getMesh(0);
    model.loadModel("3dmodels/what.obj");
    mesh[3] = model.getMesh(0);
    model.loadModel("3dmodels/which.obj");
    mesh[4] = model.getMesh(0);
    model.loadModel("3dmodels/how.obj");
    mesh[5] = model.getMesh(0);
    for (int i=0; i<6; i++) {
        bPop[i] = false;
        popEngine[i] = 0;
    }
    light.setDirectional();
    light.rotateDeg(180, 1, 0, 0);
}

//--------------------------------------------------------------
void Mogishiken::update(){
    
}

//--------------------------------------------------------------
void Mogishiken::draw(){
    if (g_play) {
        ofEnableDepthTest();
        
        timeMultDelt += ofGetLastFrameTime()*g_speed;// * g_slide*2;
        if (g_scene==0) {
            cam[1].begin();
            //float
            float nNUM = 40;
            float time0 = ofGetElapsedTimef();
            for (int n=0; n<nNUM; n++){
                int iNUM = 20;//10 * ((n*2+1)/10.+0.4);
                for (int i=0; i<iNUM; i++) {
                    ofPushMatrix();
                    //float r = 400 * ((1+(n+i/float(iNUM)))/nNUM*0.7+0.4);
                    float r = 400*g_size;
                    //glm::vec3 t = glm::mix(transform1(eTime,r,iNUM,i,n), transform2(eTime,r,iNUM,i,n), float(g_slide));
                    glm::vec3 t = transform2(timeMultDelt*-0.5,r,iNUM,i,n);
                    ofTranslate(t);
                    ofRotateY(ofNoise(i*10,n*10,time0*.7)*180);
                    ofTranslate(-font.getSize()/2,font.getSize()/2);
                    float localFade = ofClamp((sin(iNUM/30. * i *PI*g_PI  +time0*10.)+1.) *0.5 +0.3, 0,1);
                    ofSetColor(ofColor::fromHsb(ofNoise(100*n, 90*i)*255, 100, ofClamp(255*(1.3-(t.z+400)/800), 0, 255)*g_fade*localFade ));
                    //ofSetColor( ofClamp(255*((t.z+400)/800)+20, 0, 255) );
                    //ofSetColor(ofColor::fromHsb(ofNoise(100*n, 90*i)*255, 0, 255));
                    font.drawStringAsShapes(splitedWords[int(ofWrap(i+n*iNUM, 0, splitedWords.size()))], 0, 0);
                    ofPopMatrix();
                }
            }
            cam[1].end();
        }
        
        float eTime = -timeMultDelt*0.2;
        if (g_scene == 1) {
            float noizeScaleZ = 0.0005;
            float poleWidth = 600;
            glm::vec3 camPos(0);
            camPos.x = ofSignedNoise(0, 100, eTime*0.2) *poleWidth;
            camPos.y = ofSignedNoise(0, 8800, eTime*0.2) *poleWidth;
            cam[0].setPosition(camPos);
            glm::vec3 lookAt;
            lookAt.z = -100;
            lookAt.x = ofSignedNoise(lookAt.z*noizeScaleZ, 100, eTime*0.2) *poleWidth;
            lookAt.y = ofSignedNoise(lookAt.z*noizeScaleZ, 8800, eTime*0.2) *poleWidth;
            cam[0].lookAt(lookAt);
            cam[0].begin();
            float nNUM = 40;
            for (int n=0; n<nNUM; n++){
                float iNUM = 20;
                for (int i=0; i<iNUM; i++) {
                    glm::vec3 pole(0,0,0); //軸の中心の座標
                    pole.z = (glm::fract(-eTime*0.4+n/nNUM)-1.)*1500 + 100;
                    pole.x = ofSignedNoise(pole.z*noizeScaleZ,  100, eTime*0.2) *poleWidth;
                    pole.y = ofSignedNoise(pole.z*noizeScaleZ, 8800, eTime*0.2) *poleWidth;
                    glm::vec3 nextPole(0,0,0); //次の軸の中心の座標
                    nextPole.z = pole.z - 125; //次のp.z
                    nextPole.x = ofSignedNoise(nextPole.z*noizeScaleZ,  100, eTime*0.2) *poleWidth;
                    nextPole.y = ofSignedNoise(nextPole.z*noizeScaleZ, 8800, eTime*0.2) *poleWidth;
                    glm::vec3 p(0,0,0); //それぞれ一つ一つの文字の座標
                    p.x = sin(1/iNUM*i*PI*2) * 100  + pole.x;
                    p.y = cos(1/iNUM*i*PI*2) * 100  + pole.y;
                    p.z = pole.z;
                    
                    ofPushMatrix();
                    ofTranslate(p);
                    ofRotateYDeg(ofNoise(i+n,eTime)*360);
                    ofRotateZDeg(eTime*20+360/nNUM*n);
                    ofTranslate(-font.getSize()/2,font.getSize()/2);
                    ofSetColor(ofColor::fromHsb(ofNoise(100*n, 90*i)*255, 100, 255*(1-p.z/-1500)*g_fade));
                    font.drawStringAsShapes(splitedWords[int(ofWrap(i+n*nNUM, 0, splitedWords.size()))], 0, 0);
                    ofPopMatrix();
                }
            }
            ofSetColor(255);
            cam[0].end();
        }
        ofDisableDepthTest();
        
        float speed = 3.;
        for (int i=0; i<6; i++) {
            if (bPop[i]) {
                if (popEngine[i]<1) {
                    popEngine[i] += ofGetLastFrameTime() *speed;
                }
            }else{
                if (popEngine[i]>0) {
                    popEngine[i] -= ofGetLastFrameTime() *speed;
                }
            }
        }
        if(bPopUp){
            if ( popUpEngine < 0.6 ){
                popUpEngine += ofGetLastFrameTime();
            }else{
                bPopUp = false;
                popUpEngine = 0;
            }
        }
        //adventureのやつ
        ofEnableDepthTest();
        light.enable();
        for (int i=0; i<3; i++) {
            ofPushMatrix();
            float pX;
            if (i != 1) {
                pX = cos((1-popEngine[i])*PI) * 400;
            }else{
                pX = cos(popEngine[i]*PI) * 400 + 800;
            }
            ofTranslate(pX, 0);
            ofTranslate(0, 100 + 200*i);
            ofScale(250);
            if(i==1) ofScale(1+sin(popUpEngine*30)*0.1); //
            ofRotateDeg(180, 1, 0, 0);
            if(i==0) ofSetColor(255, 0, 0);
            if(i==1) ofSetColor(0, 255, 0);
            if(i==2) ofSetColor(0, 0, 255);
            mesh[i].draw();
            ofPopMatrix();
        }
        
        for (int i=3; i<6; i++) {
            ofPushMatrix();
            float pX;
            if (i != 4) {
                pX = cos((1-popEngine[i])*PI) * 400;
            }else{
                pX = cos(popEngine[i]*PI) * 400 + 800;
            }
            ofTranslate(pX, 0);
            ofTranslate(0, 100 + 200*(i-3));
            ofScale(250);
            ofRotateDeg(180, 1, 0, 0);
            if(i==3) ofSetColor(255, 0, 0);
            if(i==4) ofSetColor(0, 255, 0);
            if(i==5) ofSetColor(0, 0, 255);
            mesh[i].draw();
            ofPopMatrix();
        }
        light.disable();
        ofDisableDepthTest();
        
        
        
        
    }
}

//--------------------------------------------------------------
glm::vec3 Mogishiken::transform2(const float &_time, const float &_radius, const int &_num, const int &_i, const int &_n){
    glm::vec3 pole(0,0,0);
    //pole.y = (_n + _i/float(_num))*30;
    pole.y = _n*30*g_size;
    /*
     pole.x = ofSignedNoise(pole.y*0.005,  100) *100;
     pole.z = ofSignedNoise(pole.y*0.005, 8000) *100;
     */
    
    glm::vec3 p;
    float noise = 2*PI/30*_n;
    p.x = sin( 2*PI/_num*_i + _time*1.5 +noise)*_radius    + pole.x;
    p.z = cos( 2*PI/_num*_i + _time*1.5 +noise)*_radius    + pole.z;
    p.y = pole.y;
    p.x += ofNoise(_time*1., _i*100,_n*60, 100)*100;
    p.z += ofNoise(_time*1., _i*100,_n*60,   4)*100;
    
    return p;
}

//--------------------------------------------------------------
// https://qiita.com/watabo_shi/items/e1217a4e2cd60502bba0
vector< string > Mogishiken::separateUTF8String( string _srcStr ){
    vector< string > letters;
    
    for( int i = 0; i < _srcStr.length(); ++i ) {
        string bin_str = ofToBinary( _srcStr.at( i ) );
        
        // 1 byte character
        if( bin_str.find( "0" ) ==  0 ){
            letters.push_back( ofToString( _srcStr.at( i ) ) );
        }
        // 2 byte character
        else if( bin_str.find( "110" ) == 0 ){
            letters.push_back( ofToString( _srcStr.at( i ) ) + ofToString( _srcStr.at( i + 1 ) ) );
        }
        // 3 byte character
        else if( bin_str.find( "1110" ) == 0 ){
            letters.push_back( ofToString( _srcStr.at( i ) ) + ofToString( _srcStr.at( i + 1 ) ) + ofToString( _srcStr.at( i + 2 ) ) );
        }
        // continue byte ( second or later byte )
        else if( bin_str.find( "10" ) == 0  ){
            
        }
    }
    
    return letters;
}


//--------------------------------------------------------------
void Mogishiken::drawGui(){
    gui.draw();
}



