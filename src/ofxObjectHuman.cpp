#include "ofxObjectHuman.h"

//--------------------------------------------------------------
ofxObjectHuman::ofxObjectHuman(){
}

//--------------------------------------------------------------
void ofxObjectHuman::draw(){
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(255, 255, 255);
    ofTranslate(vf_Pos);
    ofRotateZ(-f_AnglePan);
    ofRotateX(f_AngleTilt);
    //ofDrawCircle(0,0,0,40);
    ofDrawCylinder(0, 0, 0, 50, 50);
    ofPopStyle();
    ofPopMatrix();
}

