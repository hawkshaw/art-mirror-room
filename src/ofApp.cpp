#include "ofApp.h"

/* simple model space
     ^ tilt+
     |
     z+  y+
     |  /        . ->pan+
     | /     .
     |/  .
 *C  *--------x+
 cameraPos(0,-300,300), lookAt((0,0,0),up=(0,0,1))
   /
  /
 /
 y-
 */
//--------------------------------------------------------------
void ofApp::setup(){
    b_Render = false;
    i_Camera = 0;
    i_test = 0;
    
    b_TestLight = false;
    
	ofEnableLighting();
	ofEnableDepthTest();

    ofSetSmoothLighting(true);

    testLight.setup();
    testLight.disable();
    testLight.setPointLight();
    //testLight.setAreaLight(1000, 1000);
    //testLight.setSpotlight(100,10);
    
    ///testLight.setAmbientColor(ofFloatColor(1.0,0.2,0.2));
    //testLight.setAttenuation(1.0,1.0,1.0);
    //testLight.setDiffuseColor(ofFloatColor(0.5,0.5,0.5));
    testLight.setSpecularColor(ofFloatColor(1.0f, 0.0f, 0.0f));
    testLight.setPosition(RADIUS/sqrt(2.0), -RADIUS/sqrt(2.0),0);
    //testLight.lookAt(ofVec3f(0,0,0));
    
    
	areaLight.setup();
	areaLight.enable();
	//areaLight.setSpotlight(15,1000000);
    //areaLight.setSpotlight(5,0);
    areaLight.setSpotlight(180,1);
    
    areaLight.setAmbientColor(ofFloatColor(0,0,0));
	//areaLight.setAttenuation(1.0,1.0,1.0);
	areaLight.setDiffuseColor(ofFloatColor(0.01,0.01,0.01));
    //areaLight.setDiffuseColor(ofFloatColor(0.0,0.0,0.0));
    areaLight.setSpecularColor(ofFloatColor(1,1,1));
	areaLight.setPosition(0,-RADIUS,0);
    areaLight.lookAt(ofVec3f(0,0,0), ofVec3f(0,0,1));
	
    plane.set(400,400,2,2);
	plane.rotate(-90,ofVec3f(1,0,0));
	plane.move(ofVec3f(0,-300,0));
	
    materialPlane.setAmbientColor(ofFloatColor(0,0,0,1.0));
	materialPlane.setDiffuseColor(ofFloatColor(0.1,0.1,0.1,1.0));
	materialPlane.setSpecularColor(ofFloatColor(1.0,1.0,1.0,1.0));
	materialPlane.setShininess(100000);
    
    materialPlaneBlack.setAmbientColor(ofFloatColor(0.4,0.4,0.4,0.0));
    materialPlaneBlack.setDiffuseColor(ofFloatColor(0.0,0.0,0.0,0.0));
    materialPlaneBlack.setSpecularColor(ofFloatColor(0,0,0,0));
    materialPlaneBlack.setShininess(0);
    
    
    {
        ofxObjectCamera camBuf;
        camBuf.setFarClip(20000);
        camBuf.setPosition(0, 0,0);
        camBuf.setDistance(1.0);
        camBuf.move(-200, -300, 0);
        camBuf.lookAt(ofVec3f(0,RADIUS,0), ofVec3f(0,0,1));
        camBuf.setFov(70);
        v_Camera.push_back(camBuf);
    }
    {
        ofxObjectCamera camBuf;
        camBuf.setFarClip(20000);
        camBuf.setPosition(RADIUS/sqrt(2.0), -RADIUS/sqrt(2.0),0);
        camBuf.lookAt(ofVec3f(0,RADIUS,0), ofVec3f(0,0,1));
        camBuf.setFov(50);
        v_Camera.push_back(camBuf);
    }
    {
        ofxObjectCamera camBuf;
        //camBuf.enableOrtho();
        camBuf.setPosition(RADIUS/sqrt(2.0), -RADIUS/sqrt(2.0),0);
        camBuf.lookAt(ofVec3f(0,RADIUS,0), ofVec3f(0,0,1));
        camBuf.setFov(50);
        //camBuf.setNearClip(0);
        camBuf.setFarClip(20000);
        camBuf.setAutoMove();
        v_Camera.push_back(camBuf);
    }

    
    for(int i = -MIR_X_NUM ;i<=MIR_X_NUM ;i++){
        for(int j = 0 ;j<=MIR_Y_NUM ;j++){
            ofxObjectMirror bufMirror;
            bufMirror.setPos(i*MIR_X_ANG, j*MIR_Y_ANG, RADIUS);
            v_ObjectMirror.push_back(bufMirror);
        }
    }
    
    for(int i = -(MIR_X_NUM/2) ;i<=(MIR_X_NUM/2) ;i++){
        for(int j = 1 ;j<=(MIR_Y_NUM/2) ;j++){
            ofxObjectHuman bufHuman;
            bufHuman.setPos(180+i*MIR_X_ANG, -j*MIR_Y_ANG, RADIUS);
            v_ObjectHuman.push_back(bufHuman);
        }
    }

    for(int i = -(MIR_X_NUM/2) ;i<=(MIR_X_NUM/2) ;i++){
        for(int j = 0 ;j<=(MIR_Y_NUM/2) ;j++){
            ofxObjectLight bufLight;
            bufLight.setPos(180+i*MIR_X_ANG, j*MIR_Y_ANG, RADIUS);
            v_ObjectLight.push_back(bufLight);
        }
    }
    for(int i = 0; i<v_ObjectMirror.size(); i++){
        v_ObjectMirror[i].setAngleBetween(v_ObjectLight[4].getPos(), v_Camera[0].getPosition());
    }
    
    ofSetCylinderResolution(24, 1);
    
    
    //FboBlur
    ofFbo::Settings s;
    s.width = ofGetWidth();
    s.height = ofGetHeight();
    s.internalformat = GL_RGBA;
    s.textureTarget = GL_TEXTURE_RECTANGLE_ARB;
    s.maxFilter = GL_LINEAR; GL_NEAREST;
    s.numSamples = 0;
    s.numColorbuffers = 1;
    s.useDepth = false;
    s.useStencil = false;
    gpuBlur.setup(s, false);

    gui.setup();
    gui.add(pi_AngleSpeed.setup("Angle Speed", 5, 1, 10));
    b_GuiDraw = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	//areaLight.setPosition(0,-200,0);
    for(int i = 0; i<v_ObjectMirror.size(); i++){
        //cout << i << endl;
        v_ObjectMirror[i].update(pi_AngleSpeed);
        //v_ObjectMirror[i].setAngleBetween(testLight.getPosition(), camera.getPosition());
        //v_ObjectMirror[i].setAngleBetween(areaLight.getPosition(), testLight.getPosition() );
        
        //v_ObjectMirror[i].setAngleBetween(areaLight.getPosition(), camera.getPosition());
        //v_ObjectMirror[i].setAngleBetween(areaLight.getPosition(), v_ObjectMirror[i].getPos()+ofVec3f(0,-200,0));
        
        
        /*
        if(b_Render){
            v_ObjectMirror[i].setAngleBetween(areaLight.getPosition(), v_ObjectMirror[i].getPos()-v_Camera[i_Camera].getLookAtDir());
        }else{
            //v_ObjectMirror[i].setAngleBetween(areaLight.getPosition(), v_Camera[i_Camera].getPosition());
            //v_ObjectMirror[i].setAngleBetween(areaLight.getPosition(), v_Camera[0].getPosition());
            v_ObjectMirror[i].setAngleBetween(v_ObjectHuman[4].getPos(), v_ObjectLight[7].getPos());
        }*/
        
        
        //v_ObjectMirror[i].setAngleBetween(areaLight.getPosition(), ofVec3f(-1000, -00, 700));
        //v_ObjectMirror[i].setAngleBetween(testLight.getPosition(), areaLight.getPosition());
    }
    for(int i = 0; i<v_ObjectHuman.size(); i++){
        v_ObjectHuman[i].update(pi_AngleSpeed);
    }
    for(int i = 0; i<v_ObjectLight.size(); i++){
        v_ObjectLight[i].update(pi_AngleSpeed);
    }
    for(int i = 0; i<v_Camera.size(); i++){
        v_Camera[i].update();
    }

    
    if(b_UpdateFbo){
        b_UpdateFbo = false;
        ofFbo::Settings s;
        s.width = ofGetWidth();
        s.height = ofGetHeight();
        s.internalformat = GL_RGBA;
        s.textureTarget = GL_TEXTURE_RECTANGLE_ARB;
        s.maxFilter = GL_LINEAR; GL_NEAREST;
        s.numSamples = 0;
        s.numColorbuffers = 1;
        s.useDepth = false;
        s.useStencil = false;
        gpuBlur.setup(s, false);
    }

    gpuBlur.blurOffset = 130 * ofMap(mouseY, 0, ofGetHeight(), 1, 0, true);
    gpuBlur.blurOffset = 4;
    gpuBlur.blurPasses = 10 * ofMap(mouseX, 0, ofGetWidth(), 0, 1, true);
    gpuBlur.blurPasses = 9.5;
    gpuBlur.numBlurOverlays = 1;
    gpuBlur.blurOverlayGain = 255;
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableAlphaBlending();
    
    float blur = ofMap(mouseX, 0, ofGetWidth(), 0, 10, true);

    ofBackground(0,0,0);
    v_Camera[i_Camera].begin();
    
    
    if(b_TestLight){
        testLight.enable();
        areaLight.disable();
    }else{
        testLight.disable();
        areaLight.enable();
    }
    
    if(b_Render){
        materialPlane.begin();
    }else{
        materialPlaneBlack.begin();
    }
    
    for(int i = 0; i<v_ObjectMirror.size(); i++){
        v_ObjectMirror[i].draw(b_Render,v_Camera[i_Camera].getPosition(),v_Camera[i_Camera].getLookAtDir());
    }
    for(int i = 0; i<v_ObjectHuman.size(); i++){
        v_ObjectHuman[i].draw();
    }
    
    if(b_Render){
        materialPlane.end();
    }else{
        materialPlaneBlack.end();
    }
    
    for(int i = 0; i<v_ObjectLight.size(); i++){
        v_ObjectLight[i].draw();
    }
	if(!b_TestLight)areaLight.draw();
    if(b_TestLight)testLight.draw();

    
    for(int i = 0; i<v_ObjectMirror.size(); i++){
        //v_ObjectMirror[i].drawLineTo(testLight.getPosition());
        //v_ObjectMirror[i].drawLineTo(testLight.getPosition());
        //v_ObjectMirror[i].drawLineTo(v_Camera[0].getPosition());
        if(!b_Render){
            ofSetColor(10, 0, 200,200);
            ofVec3f MirrorPos;
            //MirrorPos = v_ObjectMirror[i].getMirrorPos(areaLight.getPosition());
            MirrorPos = v_ObjectMirror[i].getMirrorPos(v_ObjectLight[4].getPos());
            v_ObjectMirror[i].drawLineTo(MirrorPos);
            ofSetColor(255);
            ofDrawSphere(MirrorPos, 10);
        }
        ofSetColor(200,200,200,150);
        v_ObjectMirror[i].drawNorm();
        ofVec3f test;
        test =v_ObjectMirror[i].getNorm();
        v_ObjectMirror[i].drawLineDir(ofVec3f(test.y*MIRROR_RADIUS*1.5,-test.x*MIRROR_RADIUS*1.5,0));
        v_ObjectMirror[i].drawLineDir(ofVec3f(0,-test.z*MIRROR_RADIUS*1.5,test.y*MIRROR_RADIUS*1.5));
        ofSetColor(0, 0, 255,90);
        v_ObjectMirror[i].drawLineDir(v_ObjectMirror[i].getReflectDir(v_ObjectLight[4].getPos())*RADIUS*2);
    }

 
#if 0
    for(int i=0;i<v_Camera.size();i++){
        ofSetColor(255,0,0);
        ofPushStyle();
        ofPushMatrix();
        ofDisableLighting();
        ofMatrix4x4 inverseCameraMatrix;
        inverseCameraMatrix.makeInvertOf(v_Camera[i].getModelViewProjectionMatrix());
        ofMultMatrix( inverseCameraMatrix );
        ofPoint scale2(0.9,0.9,0.9);
        ofScale(scale2);
        ofNoFill();
        ofDrawBox(0, 0, 0, 2.0f);
        ofEnableLighting();
        ofPopMatrix();
        ofPopStyle();
    }
#endif

    v_Camera[i_Camera].end();
    
    
    ofSetColor(255, 255, 255,255);//this color is applied to gpuBlur.beginDrawScene();
    gpuBlur.beginDrawScene();
    ofClear(0, 0, 0, 0);

    v_Camera[i_Camera].begin();
    ofSetColor(255, 255, 255,255);
    for(int i = 0; i<v_ObjectMirror.size(); i++){
        v_ObjectMirror[i].drawLineTo(v_ObjectLight[4].getPos());
        //v_ObjectMirror[i].drawLineTo(v_ObjectLight[7].getPos());
    }
    v_Camera[i_Camera].end();
    
    gpuBlur.endDrawScene();
    gpuBlur.performBlur();
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); //pre-multiplied alpha
    gpuBlur.drawBlurFbo();
    
    if(b_GuiDraw){
        gui.draw();
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key){
        case 't':
            b_TestLight = !b_TestLight;
            break;
        case 'r':
            b_Render = !b_Render;
            break;
        case 'f':
            ofToggleFullscreen();
            b_UpdateFbo = true;
            break;
        case 'g':
            b_GuiDraw = !b_GuiDraw;
            break;
        case OF_KEY_UP:
            for(int i = 0; i<v_ObjectMirror.size(); i++){
                v_ObjectMirror[i].setRandomAngle();
            }
            break;
        case OF_KEY_DOWN:
            break;
        case OF_KEY_LEFT:
            break;
        case OF_KEY_RIGHT:
            break;
        case '2':
            i_test += 1;
            break;
        case '1':
            i_test -= 1;
            break;
        case 'c':
            //b_Camera = !b_Camera;
            i_Camera = (i_Camera +1)%3;
            for(int i = 0;i<v_Camera.size();i++){
                if(i_Camera == i){
                    v_Camera[i].enableMouseInput();
                }else{
                    v_Camera[i].disableMouseInput();
                }
            }
            break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
