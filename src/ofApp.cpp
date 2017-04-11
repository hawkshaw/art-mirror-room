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
    //b_Camera = false;
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
	
    //materialPlane.setAmbientColor(ofFloatColor(0,0,0,1.0));
	//materialPlane.setDiffuseColor(ofFloatColor(0.8,0.8,0.8,1.0));
	materialPlane.setSpecularColor(ofFloatColor(1.0,1.0,1.0,1.0));
	materialPlane.setShininess(100000);
    
    {
        ofEasyCam camBuf;
        camBuf.setFarClip(20000);
        camBuf.setPosition(0, 0,0);
        camBuf.setDistance(1.0);
        camBuf.move(-100, 100, 0);
        camBuf.lookAt(ofVec3f(0,RADIUS,0), ofVec3f(0,0,1));
        camBuf.setFov(70);
        v_Camera.push_back(camBuf);
    }
    {
        ofEasyCam camBuf;
        camBuf.setFarClip(20000);
        camBuf.setPosition(RADIUS/sqrt(2.0), -RADIUS/sqrt(2.0),0);
        camBuf.lookAt(ofVec3f(0,RADIUS,0), ofVec3f(0,0,1));
        camBuf.setFov(50);
        v_Camera.push_back(camBuf);
    }
    {
        ofEasyCam camBuf;
        camBuf.enableOrtho();
        camBuf.setPosition(RADIUS/sqrt(2.0), -RADIUS/sqrt(2.0),0);
        camBuf.lookAt(ofVec3f(0,RADIUS,0), ofVec3f(0,0,1));
        camBuf.setFov(50);
        camBuf.setNearClip(0);
        camBuf.setFarClip(10000);
        v_Camera.push_back(camBuf);
    }

    
    
	camera.setFarClip(20000);
    camera.setPosition(0, 0,0);
    camera.setDistance(1.0);
    camera.move(100, 100, 0);
    camera.lookAt(ofVec3f(0,RADIUS,0), ofVec3f(0,0,1));
    camera.setFov(70);
    
    
    camera2.setFarClip(20000);
    camera2.setPosition(RADIUS/sqrt(2.0), -RADIUS/sqrt(2.0),0);
    camera2.lookAt(ofVec3f(0,RADIUS,0), ofVec3f(0,0,1));
    camera2.setFov(50);
    
    
    cam.enableOrtho();
    cam.setPosition(RADIUS/sqrt(2.0), -RADIUS/sqrt(2.0), 0);
    cam.lookAt(ofVec3f(0,RADIUS,0), ofVec3f(0,0,1));
    cam.setFov(50);
    cam.setNearClip(0);
    cam.setFarClip(10000);
    //cam.setScale(0.3*3, 0.2*3, 1.0);
    //cam.setScale(3, 2, 10);
    
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

    
}

//--------------------------------------------------------------
void ofApp::update(){
	//areaLight.setPosition(0,-200,0);
    for(int i = 0; i<v_ObjectMirror.size(); i++){
        //cout << i << endl;
        v_ObjectMirror[i].update();
        //v_ObjectMirror[i].setAngleBetween(testLight.getPosition(), camera.getPosition());
        //v_ObjectMirror[i].setAngleBetween(areaLight.getPosition(), testLight.getPosition() );
        
        //v_ObjectMirror[i].setAngleBetween(areaLight.getPosition(), camera.getPosition());
        //v_ObjectMirror[i].setAngleBetween(areaLight.getPosition(), v_ObjectMirror[i].getPos()+ofVec3f(0,-200,0));
        
        if(b_Render){
            v_ObjectMirror[i].setAngleBetween(areaLight.getPosition(), v_ObjectMirror[i].getPos()-v_Camera[i_Camera].getLookAtDir());
        }else{
            //v_ObjectMirror[i].setAngleBetween(areaLight.getPosition(), v_Camera[i_Camera].getPosition());
            //v_ObjectMirror[i].setAngleBetween(areaLight.getPosition(), v_Camera[0].getPosition());
            v_ObjectMirror[i].setAngleBetween(v_ObjectHuman[4].getPos(), v_ObjectLight[7].getPos());
        }
        //v_ObjectMirror[i].setAngleBetween(areaLight.getPosition(), ofVec3f(-1000, -00, 700));
        //v_ObjectMirror[i].setAngleBetween(testLight.getPosition(), areaLight.getPosition());
    }
    for(int i = 0; i<v_ObjectHuman.size(); i++){
        v_ObjectHuman[i].update();
    }
    for(int i = 0; i<v_ObjectLight.size(); i++){
        v_ObjectLight[i].update();
    }

    //cout<<atan(1.0)/PI<<endl;
    //cout<<atan(-2.0)/PI<<endl;
    //cam.setPosition(testLight.getPosition()+ 2*cam.getLookAtDir()*cam.getImagePlaneDistance());
    cout<< "look dir"<<cam.getLookAtDir() <<endl;
    cout<< "cam gpos"<<cam.getPosition() <<endl;
    cout<< "camera gpos"<<camera.getPosition() <<endl;
    cout<< "camera2 gpos"<<camera2.getPosition() <<endl;
    cout<<"dist cam"<<camera.getDistance()<<endl;
    //camera.setDistance(1.0);

    
    
    gpuBlur.blurOffset = 130 * ofMap(mouseY, 0, ofGetHeight(), 1, 0, true);
    gpuBlur.blurOffset = 4;
    gpuBlur.blurPasses = 10 * ofMap(mouseX, 0, ofGetWidth(), 0, 1, true);
    gpuBlur.blurPasses = 9.5;
    gpuBlur.numBlurOverlays = 1;
    gpuBlur.blurOverlayGain = 255;
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
     float blur = ofMap(mouseX, 0, ofGetWidth(), 0, 10, true);
    
//    blur.begin();
    
    //myFbo.begin();

    ofBackground(0,0,0);

    //if(!b_Camera)camera.begin();
    //if(b_Camera)cam.begin();

    

    
    
    v_Camera[i_Camera].begin();
    
    /*switch(i_Camera){
        case 0:
            camera.begin();
            break;
        case 1:
            camera2.begin();
            break;
        case 2:
            cam.begin();
            break;
    }*/

    //ofEnableAlphaBlending();
    ofSetColor(255, 255,255);
    ofDrawBox(0, 0, 0,100);
    
    if(b_TestLight){
        testLight.enable();
        areaLight.disable();
    }else{
        testLight.disable();
        areaLight.enable();
    }
    
    
    materialPlane.begin();
	
    //plane.draw();
    //ofDrawBox(-200, 0, 0, 200);

    for(int i = 0; i<v_ObjectMirror.size(); i++){
        v_ObjectMirror[i].draw();
    }
    for(int i = 0; i<v_ObjectHuman.size(); i++){
        v_ObjectHuman[i].draw();
    }
	
    
	//ofDrawSphere(0,-300,0,10000);
	materialPlane.end();
    
    for(int i = 0; i<v_ObjectLight.size(); i++){
        v_ObjectLight[i].draw();
    }
	if(!b_TestLight)areaLight.draw();
    if(b_TestLight)testLight.draw();

    
    for(int i = 0; i<v_ObjectMirror.size(); i++){
        //v_ObjectMirror[i].drawLineTo(testLight.getPosition());
        //v_ObjectMirror[i].drawLineTo(testLight.getPosition());
        //v_ObjectMirror[i].drawLineTo(v_Camera[0].getPosition());
        ofSetColor(255, 0, 0);
        ofVec3f MirrorPos;
        //MirrorPos = v_ObjectMirror[i].getMirrorPos(areaLight.getPosition());
        MirrorPos = v_ObjectMirror[i].getMirrorPos(v_ObjectLight[7].getPos());
        if(!b_Render){
            v_ObjectMirror[i].drawLineTo(MirrorPos);
            ofDrawSphere(MirrorPos, 10);
        }
        ofSetColor(200, 200, 200);
        v_ObjectMirror[i].drawNorm();
        ofVec3f test;
        test =v_ObjectMirror[i].getNorm();
        v_ObjectMirror[i].drawLineDir(ofVec3f(test.y*MIRROR_RADIUS*2,-test.x*MIRROR_RADIUS*2,0));
        v_ObjectMirror[i].drawLineDir(ofVec3f(0,-test.z*MIRROR_RADIUS*2,test.y*MIRROR_RADIUS*2));
        ofSetColor(0, 0, 255);
        v_ObjectMirror[i].drawLineDir(v_ObjectMirror[i].getReflectDir(v_ObjectLight[i_test].getPos())*RADIUS*2);
    }

    for(int i = 0; i<v_ObjectMirror.size(); i++){
        ofSetColor(0, 0, 255);
        v_ObjectMirror[i].drawLineDir(v_ObjectMirror[i].getReflectDir(v_ObjectLight[i_test].getPos())*RADIUS*2);
    }



    if(i_Camera!=2)cam.draw();
    
    
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

    /*
     ofEnableAlphaBlending();
    ofSetColor(255, 255,255,100);
    ofDrawBox(0, 0, 0, 100);
    */

    
    //if(b_Camera)cam.end();
    //if(!b_Camera)camera.end();
    
    v_Camera[i_Camera].end();
    
    /*switch(i_Camera){
        case 0:
            camera.end();
            break;
        case 1:
            camera2.end();
            break;
        case 2:
            cam.end();
            break;
    }*/

    
    //ofDrawRectangle(200, 200, 20, 20);
    //glDepthMask(GL_FALSE);
    
    ofSetColor(255, 100, 90);
    
    // this makes everything look glowy :)
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    
    ofDisableBlendMode();
    ofEnableAlphaBlending();
    

    gpuBlur.beginDrawScene();
    ofClear(0, 0, 0, 0);

    v_Camera[i_Camera].begin();
    for(int i = 0; i<v_ObjectMirror.size(); i++){
        ofSetColor(200, 200, 200);
        v_ObjectMirror[i].drawLineTo(v_ObjectHuman[4].getPos());
        v_ObjectMirror[i].drawLineTo(v_ObjectLight[7].getPos());
    }
    v_Camera[i_Camera].end();
    
    gpuBlur.endDrawScene();
    
    gpuBlur.performBlur();
    
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); //pre-multiplied alpha
    gpuBlur.drawBlurFbo();
    
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
            break;
        case OF_KEY_UP:
            //testLight.move(20,0,0);
            //cam.move(0, 100, 0);
            camera.move(0, 100, 0);
            cam.rotate(1, ofVec3f(0, 0,1));
            break;
        case OF_KEY_DOWN:
            //testLight.move(-20,0,0);
            //cam.move(0, -100, 0);
            camera.move(0, -100, 0);
            cam.rotate(-1, ofVec3f(0, 0,1));
            break;
        case OF_KEY_LEFT:
            //areaLight.rotate(1,0,0,1);
            camera.move(-100, 0, 0);
            cam.move(-100, 0, 0);
            break;
        case OF_KEY_RIGHT:
            //areaLight.rotate(-1,0,0,1);
            camera.move(100, 0, 0);
            cam.move(100, 0, 0);
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
