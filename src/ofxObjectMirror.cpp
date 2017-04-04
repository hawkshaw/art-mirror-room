#include "ofxObjectMirror.h"

//--------------------------------------------------------------
ofxObjectMirror::ofxObjectMirror(){
}

//--------------------------------------------------------------
void ofxObjectMirror::draw(){
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(255, 255, 255);
    ofTranslate(vf_Pos);
    ofRotateZ(-f_AnglePan);
    ofRotateX(f_AngleTilt);
    //ofDrawCircle(0,0,0,40);
    ofDrawCylinder(0, 0, 0, MIRROR_RADIUS, 1);
    ofPopStyle();
    ofPopMatrix();
}
//--------------------------------------------------------------
void ofxObjectMirror::drawNorm(){
    drawLineDir(vf_NormalVec*MIRROR_RADIUS);
}

//--------------------------------------------------------------
ofVec3f ofxObjectMirror::getMirrorPos(ofVec3f _pos){
    float distance;
    distance = vf_NormalVec.x * (_pos.x  - vf_Pos.x) + vf_NormalVec.y * (_pos.y  - vf_Pos.y) + vf_NormalVec.z  * ( _pos.z - vf_Pos.z);
    return _pos - 2 * distance * vf_NormalVec;
}
