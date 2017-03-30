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
    b_Camera = false;
    i_test = 0;
    
    b_TestLight = false;
    
	ofEnableLighting();
	ofEnableDepthTest();
    
    ofSetSmoothLighting(true);
    
    testLight.setup();
    testLight.disable();
    //testLight.enable();
    testLight.setPointLight();
    //testLight.setAreaLight(1000, 1000);
    //testLight.setSpotlight(100,10);
    
    ///testLight.setAmbientColor(ofFloatColor(1.0,0.2,0.2));
    //testLight.setAmbientColor(ofFloatColor(0,0,0));
    
    //testLight.setAttenuation(1.0,1.0,1.0);
    //testLight.setDiffuseColor(ofFloatColor(0.5,0.5,0.5));
    //testLight.setSpecularColor(ofFloatColor(1,1,1));
    
    ///testLight.setDiffuseColor( ofFloatColor( 238.f/255.f, 57.f/255.f, 135.f/255.f ));
    //testLight.setDiffuseColor( ofFloatColor(0,0,0));
    testLight.setSpecularColor(ofFloatColor(1.0f, 0.0f, 0.0f));
    
    
    testLight.setPosition(200,-400,0);
    //testLight.lookAt(ofVec3f(0,0,0));
    
    
	areaLight.setup();
	areaLight.enable();
	//areaLight.setAreaLight(10,10);
	//areaLight.setSpotlight(15,1000000);
    //areaLight.setSpotlight(5,0);
    areaLight.setSpotlight(180,1);
    
    areaLight.setAmbientColor(ofFloatColor(0,0,0));
	//areaLight.setAttenuation(1.0,1.0,1.0);
	areaLight.setDiffuseColor(ofFloatColor(0.1,0.1,0.1));
	areaLight.setSpecularColor(ofFloatColor(1,1,1));
	//areaLight.rotate(-90,ofVec3f(1,0,0));
	//areaLight.rotate(30,ofVec3f(0,0,1));
	areaLight.setPosition(0,-RADIUS,0);
    areaLight.lookAt(ofVec3f(0,0,0), ofVec3f(0,0,1));
	ofBackground(0);
	

    //plane.set(400,400,2,2);
    //plane.move(ofVec3f(100,300,0));
    
    plane.set(400,400,2,2);
	plane.rotate(-90,ofVec3f(1,0,0));
	plane.move(ofVec3f(0,-300,0));
	
    //materialPlane.setAmbientColor(ofFloatColor(0,0,0,1.0));
	//materialPlane.setDiffuseColor(ofFloatColor(0.8,0.8,0.8,1.0));
    
    
    //materialPlane.setAmbientColor(ofFloatColor(1.0,1.0,1.0,1.0));
    //materialPlane.setDiffuseColor(ofFloatColor(1.0,1.0,1.0,1.0));
    //materialPlane.setAmbientColor(ofFloatColor(0.00,0.0,0.00,1.0));
    //materialPlane.setDiffuseColor(ofFloatColor(0.00,0.0,0.00,1.0));
    //materialPlane.setSpecularColor(ofFloatColor(0.8,0.8,0.8,1.0));
	materialPlane.setSpecularColor(ofFloatColor(1.0,1.0,1.0,1.0));
	materialPlane.setShininess(10000);
    
	camera.setFarClip(20000);
    
    camera.enableOrtho();//important!!
    
    camera.setPosition(RADIUS/sqrt(2.0), -RADIUS/sqrt(2.0),0);
    camera.lookAt(ofVec3f(0,0,0), ofVec3f(0,0,1));
    camera.setFov(100);
    
    cam.enableOrtho();
    cam.setPosition(-500, -500, 0);
    cam.lookAt(ofVec3f(0,0,0), ofVec3f(0,0,1));
    cam.setFov(100);
    
    
    for(int i = -MIR_X_NUM ;i<=MIR_X_NUM ;i++){
        for(int j = 0 ;j<=MIR_Y_NUM ;j++){
            ofxObjectMirror bufMirror;
            bufMirror.setPos(i*MIR_X_ANG, j*MIR_Y_ANG, RADIUS);
            v_ObjectMirror.push_back(bufMirror);
        }
    }
    

    
    
    ofSetCylinderResolution(24, 1);
    
    
    /*
    //ofBlur
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    //blur.setup(ofGetWidth(), ofGetHeight(), 32, .2, 1, 0.5);
    blur.setup(ofGetWidth(), ofGetHeight(), 32, .6, 4, 5);
    fbo.allocate(ofGetWidth(), ofGetHeight());
    */
    
    
    myFbo.allocate(512, 512,GL_RGB);
    myGlitch.setup(&myFbo);
    myGlitch.setFx(OFXPOSTGLITCH_GLOW			, true);
    
}

//--------------------------------------------------------------
void ofApp::update(){
	//areaLight.setPosition(0,-200,0);
    for(int i = 0; i<v_ObjectMirror.size(); i++){
        //cout << i << endl;
        v_ObjectMirror[i].update();
        //v_ObjectMirror[i].setAngleBetween(testLight.getPosition(), camera.getPosition());
        v_ObjectMirror[i].setAngleBetween(areaLight.getPosition(), testLight.getPosition() );
        //v_ObjectMirror[i].setAngleBetween(areaLight.getPosition(), camera.getPosition());
        //v_ObjectMirror[i].setAngleBetween(areaLight.getPosition(), ofVec3f(-1000, -00, 700));
        //v_ObjectMirror[i].setAngleBetween(testLight.getPosition(), areaLight.getPosition());
    }
    //cout<<atan(1.0)/PI<<endl;
    //cout<<atan(-2.0)/PI<<endl;
    cam.setPosition(testLight.getPosition()+ 2*cam.getLookAtDir()*cam.getImagePlaneDistance());
    cout<< "pos"<<cam.getLookAtDir() <<endl;
    cout<< "gpos"<<cam.getPosition() + cam.getLookAtDir()*cam.getImagePlaneDistance() <<endl;


}

//--------------------------------------------------------------
void ofApp::draw(){
    //fbo.begin();
    
    ofBackground(0,0,0);

    if(!b_Camera)camera.begin();
    if(b_Camera)cam.begin();



    
    
    
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
	
    
	//ofDrawSphere(0,-300,0,10000);
	materialPlane.end();
	if(!b_TestLight)areaLight.draw();
    if(b_TestLight)testLight.draw();

    ofSetColor(200, 200, 200);
    for(int i = 0; i<v_ObjectMirror.size(); i++){
        //v_ObjectMirror[i].drawLineTo(testLight.getPosition());
        v_ObjectMirror[i].drawLineTo(testLight.getPosition());
        
        //v_ObjectMirror[i].drawLineTo(camera.getPosition());
        //v_ObjectMirror[i].drawLineTo(cam.getPosition());
        v_ObjectMirror[i].drawLineTo(areaLight.getPosition());
        v_ObjectMirror[i].drawLineTo(v_ObjectMirror[i].getMirrorPos(areaLight.getPosition()));
        v_ObjectMirror[i].drawNorm();
        ofVec3f test;
        test =v_ObjectMirror[i].getNorm();
        v_ObjectMirror[i].drawLineDir(ofVec3f(test.y*MIRROR_RADIUS*2,-test.x*MIRROR_RADIUS*2,0));
        v_ObjectMirror[i].drawLineDir(ofVec3f(0,-test.z*MIRROR_RADIUS*2,test.y*MIRROR_RADIUS*2));
    }

    
    cam.draw();
    
    ofPushStyle();
    ofNoFill();
    ofMatrix4x4 inverseCameraMatrix;
    inverseCameraMatrix.makeInvertOf(cam.getModelViewProjectionMatrix());
    ofMultMatrix( inverseCameraMatrix );
    cout<<inverseCameraMatrix<<endl;
    
    ofPopStyle();
    
    if(b_Camera)cam.end();
    if(!b_Camera)camera.end();

    
    myFbo.begin();
    ofBackground(255,0,0);
    ofSetColor(255,255,255);
    ofDrawRectangle(200, 200, 200, 200);
    myFbo.end();
    
    /* Apply effects */
    myGlitch.generateFx();
    
    /* draw effected view */
    //ofSetColor(255);
    myFbo.draw(512, 0);
    /*
    
    fbo.end();
    
    blur.begin();
    ofDisableBlendMode();
    ofBackground(0);
    fbo.draw(0,0);
    blur.end();
    
    blur.draw();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    //fbo.draw(0,0);
*/
    
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key){
        case 't':
            b_TestLight = !b_TestLight;
            break;
        case 'f':
            ofToggleFullscreen();
            break;
        case OF_KEY_UP:
            testLight.move(20,0,0);
            break;
        case OF_KEY_DOWN:
            testLight.move(-20,0,0);
            break;
        case OF_KEY_LEFT:
            areaLight.rotate(1,0,0,1);
            break;
        case OF_KEY_RIGHT:
            areaLight.rotate(-1,0,0,1);
            break;
        case 'l':
            i_test += 5;
            break;
        case 'r':
            i_test -= 5;
            break;
        case 'c':
            b_Camera = !b_Camera;
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
