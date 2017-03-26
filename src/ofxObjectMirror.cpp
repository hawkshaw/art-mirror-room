#include "ofxObjectMirror.h"

//--------------------------------------------------------------
ofxObjectMirror::ofxObjectMirror(){
    //init
    f_PosPan = 0;
    f_PosTilt = 0;
    f_PosDistance = 0;
    f_AnglePan = 0;
    f_AngleTilt = 0;
    vf_NormalVec = ofVec3f(0,0,0);
    f_PosX = 0;
    f_PosY = 0;
    f_PosZ = 0;
}
//--------------------------------------------------------------
void ofxObjectMirror::setup(){
}
//--------------------------------------------------------------
void ofxObjectMirror::set(string s){
}
//--------------------------------------------------------------
void ofxObjectMirror::update(){
}
//--------------------------------------------------------------
void ofxObjectMirror::draw(){
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(255, 255, 255);
    ofTranslate(f_PosX, f_PosY, f_PosZ);
    ofRotateZ(-f_AnglePan);
    ofRotateX(f_AngleTilt);
    //ofDrawCircle(0,0,0,40);
    ofDrawCylinder(0, 0, 0, 40, 0.1);
    ofPopStyle();
    ofPopMatrix();
}
//--------------------------------------------------------------
void ofxObjectMirror::setPos(float _f_Pan,float _f_Tilt,float _f_Distance){
    f_PosPan = _f_Pan;
    f_PosTilt = _f_Tilt;
    f_PosDistance = _f_Distance;
    f_PosX = _f_Distance * cos(PI * _f_Tilt / 180.0) * sin(PI * _f_Pan / 180.0);
    f_PosY = _f_Distance * cos(PI * _f_Tilt / 180.0) * cos(PI * _f_Pan / 180.0);
    f_PosZ = _f_Distance * sin(PI * _f_Tilt / 180.0);
}
//--------------------------------------------------------------
ofVec3f ofxObjectMirror::getPos(){
    return ofVec3f(f_PosX, f_PosY, f_PosZ);
}
//--------------------------------------------------------------
void ofxObjectMirror::setAngle(float _f_Pan,float _f_Tilt){
    f_AnglePan = _f_Pan;
    f_AngleTilt = _f_Tilt;
}
//--------------------------------------------------------------
void ofxObjectMirror::setNormalVec(ofVec3f _norm){
    //鏡の法線で指定
    //default (0,-1,0)
    //atan();
    if(_norm.y==0){
        f_AnglePan = 90.0;
    }else{
        if(_norm.y > 0){
            f_AnglePan = 180.0 * atan(_norm.x / _norm.y) / PI;
        }else{
            if(_norm.x > 0){
                f_AnglePan = 180 + 180.0 * atan(_norm.x / _norm.y) / PI;
            }else{
                f_AnglePan = 180.0 * atan(_norm.x / _norm.y) / PI - 180;
            }
        }
    }
    if((_norm.y ==0) and (_norm.x == 0)){
        f_AngleTilt = 90.0;
    }else{
        f_AngleTilt = 180.0 * atan(_norm.z / ofVec2f(_norm.x,_norm.y).length()) / PI;
    }
    cout << "set" << f_AnglePan << " " << f_AngleTilt << endl;
}
//--------------------------------------------------------------
void ofxObjectMirror::setAngleBetween(ofVec3f _pos1,ofVec3f _pos2){
    //鏡の法線を定める
    ofVec3f buf1,buf2;
    buf1 = _pos1 - ofVec3f(f_PosX,f_PosY,f_PosZ);
    buf2 = _pos2 - ofVec3f(f_PosX,f_PosY,f_PosZ);
    cout<<buf1 << ":" << buf2<<endl;
    buf1 /= buf1.length();
    buf2 /= buf2.length();
    cout<<buf1 << ":" << buf2<<endl;
    setNormalVec(buf1 + buf2);
}
