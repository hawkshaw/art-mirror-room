#include "ofxObjectLight.h"

//--------------------------------------------------------------
ofxObjectLight::ofxObjectLight(){
    light.setup();
    light.enable();
    light.setSpotlight(180,1);
    
    light.setAmbientColor(ofFloatColor(0,0,0));
    //areaLight.setAttenuation(1.0,1.0,1.0);
    light.setDiffuseColor(ofFloatColor(0.01,0.01,0.01));
    //areaLight.setDiffuseColor(ofFloatColor(0.0,0.0,0.0));
    light.setSpecularColor(ofFloatColor(1,1,1));
}
//--------------------------------------------------------------
void ofxObjectLight::setPos(float _f_Pan,float _f_Tilt,float _f_Distance){
    ofxObjectParent::setPos(_f_Pan, _f_Tilt, _f_Distance);
    light.setPosition(vf_Pos);
    light.lookAt(ofVec3f(0,0,0), ofVec3f(0,0,1));
}
//--------------------------------------------------------------
void ofxObjectLight::draw(){
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(255, 255, 255);
    //ofTranslate(vf_Pos);
    //ofRotateZ(-f_AnglePan);
    //ofRotateX(f_AngleTilt);
    //ofDrawCircle(0,0,0,40);
    //ofDrawCylinder(0, 0, 0, 30, 100);
    light.draw();
    ofPopStyle();
    ofPopMatrix();
}
