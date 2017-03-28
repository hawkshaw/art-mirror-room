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
    
    
    testLight.setPosition(200,0,0);
    //testLight.lookAt(ofVec3f(0,0,0));
    
    
	areaLight.setup();
	areaLight.enable();
	//areaLight.setAreaLight(10,10);
	//areaLight.setSpotlight(15,1000000);
    //areaLight.setSpotlight(5,0);
    areaLight.setSpotlight(150,10);
    
    areaLight.setAmbientColor(ofFloatColor(0,0,0));
	//areaLight.setAttenuation(1.0,1.0,1.0);
	areaLight.setDiffuseColor(ofFloatColor(0.3,0.3,0.3));
	areaLight.setSpecularColor(ofFloatColor(1,1,1));
	//areaLight.rotate(-90,ofVec3f(1,0,0));
	//areaLight.rotate(30,ofVec3f(0,0,1));
	areaLight.setPosition(0,-500,0);
    
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
    camera.setPosition(0, -1000, 300);
    camera.lookAt(ofVec3f(0,0,0), ofVec3f(0,0,1));
    
    cam.setPosition(-1000, -00, 700);
    cam.lookAt(ofVec3f(0,0,0), ofVec3f(0,0,1));
    cam.setFov(100);
    
    ofxObjectMirror bufMirror;
    bufMirror.setPos(45, 0, 400);
    //bufMirror.setAngle(45, 0);
    bufMirror.setNormalVec(ofVec3f(1.0,-2.0,0));
    v_ObjectMirror.push_back(bufMirror);
    ofxObjectMirror bufMirror2;
    bufMirror2.setPos(-65, 0, 400);
    //bufMirror2.setNormalVec(ofVec3f(-2,0,-7));
    bufMirror2.setAngle(90, 70);
    v_ObjectMirror.push_back(bufMirror2);
    ofxObjectMirror bufMirror3;
    bufMirror3.setPos(0, 20, 400);
    bufMirror3.setNormalVec(ofVec3f(0,0,1.0));
    //bufMirror3.setAngle(0, 90);
    v_ObjectMirror.push_back(bufMirror3);
    //ofSetCircleResolution(30);
    ofSetCylinderResolution(24, 1);
    
    areaLight.lookAt(bufMirror3.getPos());

}

//--------------------------------------------------------------
void ofApp::update(){
	//areaLight.setPosition(0,-200,0);
    for(int i = 0; i<v_ObjectMirror.size(); i++){
        cout << i << endl;
        v_ObjectMirror[i].update();
        //v_ObjectMirror[i].setAngleBetween(testLight.getPosition(), camera.getPosition());
        v_ObjectMirror[i].setAngleBetween(areaLight.getPosition(), cam.getPosition());
        //v_ObjectMirror[i].setAngleBetween(testLight.getPosition(), areaLight.getPosition());
    }
    //cout<<atan(1.0)/PI<<endl;
    //cout<<atan(-2.0)/PI<<endl;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0,0,0);
    
    camera.begin();
    //cam.begin();
    
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

    ofSetColor(255, 255, 255);
    for(int i = 0; i<v_ObjectMirror.size(); i++){
        //v_ObjectMirror[i].drawLineTo(testLight.getPosition());
        //v_ObjectMirror[i].drawLineTo(camera.getPosition());
        v_ObjectMirror[i].drawLineTo(cam.getPosition());
        v_ObjectMirror[i].drawLineTo(areaLight.getPosition());
        v_ObjectMirror[i].drawNorm();
        ofVec3f test;
        test =v_ObjectMirror[i].getNorm();
        v_ObjectMirror[i].drawLineDir(ofVec3f(test.y*200,-test.x*200,0));
        v_ObjectMirror[i].drawLineDir(ofVec3f(0,-test.z*200,test.y*200));
    }

    //cam.end();
    camera.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key){
        case 't':
            b_TestLight = !b_TestLight;
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
