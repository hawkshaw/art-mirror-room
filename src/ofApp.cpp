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
    //testLight.setSpotlight(100,10);
    testLight.setAmbientColor(ofFloatColor(0.2,0.2,0.2));
    //testLight.setAttenuation(1.0,1.0,1.0);
    //testLight.setDiffuseColor(ofFloatColor(0.5,0.5,0.5));
    //testLight.setSpecularColor(ofFloatColor(1,1,1));
    testLight.setDiffuseColor( ofFloatColor( 238.f/255.f, 57.f/255.f, 135.f/255.f ));
    testLight.setSpecularColor(ofFloatColor(.8f, .8f, .9f));
    
    
    testLight.setPosition(200,200,0);
    //testLight.lookAt(ofVec3f(0,0,0));
    
    
	areaLight.setup();
	areaLight.enable();
	areaLight.setAreaLight(10,10);
	//areaLight.setSpotlight(15,1000000);
    areaLight.setSpotlight(5,0);
    
    areaLight.setAmbientColor(ofFloatColor(0,0,0));
	//areaLight.setAttenuation(1.0,1.0,1.0);
	areaLight.setDiffuseColor(ofFloatColor(0,0,0));
	areaLight.setSpecularColor(ofFloatColor(1,1,1));
	//areaLight.rotate(-90,ofVec3f(1,0,0));
	//areaLight.rotate(30,ofVec3f(0,0,1));
	areaLight.setPosition(0,200,0);
    areaLight.lookAt(ofVec3f(0,0,0));
    
	ofBackground(0);
	

    //plane.set(400,400,2,2);
    //plane.move(ofVec3f(100,300,0));
    
    plane.set(400,400,2,2);
	plane.rotate(-90,ofVec3f(1,0,0));
	plane.move(ofVec3f(0,-300,0));
	
    materialPlane.setAmbientColor(ofFloatColor(0,0,0,1.0));
	materialPlane.setDiffuseColor(ofFloatColor(0.8,0.8,0.8,1.0));
    
    
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
}

//--------------------------------------------------------------
void ofApp::update(){
	//areaLight.setPosition(0,-200,0);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0,0,0);
    camera.begin();
    
    if(b_TestLight)testLight.enable();
    
    if(!b_TestLight)materialPlane.begin();
	
    plane.draw();
    ofDrawBox(1000, 0, 0, 200);

    
	//ofDrawSphere(0,-300,0,10000);
	if(!b_TestLight)materialPlane.end();
	if(!b_TestLight)areaLight.draw();
    //if(b_TestLight)testLight.draw();
    camera.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key){
        case 't':
            b_TestLight = !b_TestLight;
            break;
        case OF_KEY_UP:
            areaLight.move(0,10,0);
            break;
        case OF_KEY_DOWN:
            areaLight.move(0,-10,0);
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
