#include "ofxObjectParent.h"

//--------------------------------------------------------------
ofxObjectParent::ofxObjectParent(){
    //init
    f_PosPan = 0;
    f_PosTilt = 0;
    f_PosDistance = 0;
    f_AnglePan = 0;
    f_AngleTilt = 0;
    vf_NormalVec = ofVec3f(0,0,0);
    vf_Pos = ofVec3f(0,0,0);
    //f_PosX = 0;
    //f_PosY = 0;
    //f_PosZ = 0;
}
//--------------------------------------------------------------
void ofxObjectParent::setup(){
}
//--------------------------------------------------------------
void ofxObjectParent::set(string s){
}
//--------------------------------------------------------------
void ofxObjectParent::update(){
}

void ofxObjectParent::myDrawLine(ofVec3f _pos1,ofVec3f _pos2,int _i_GlowLevel=0,ofColor _penColor = ofColor(255,255,255)){
    if(_i_GlowLevel){
    }else{
    }
    ofDrawLine(_pos1,_pos2);
}

void ofxObjectParent::drawLineTo(ofVec3f _pos){
    myDrawLine(vf_Pos, _pos,1);
}

void ofxObjectParent::drawLineDir(ofVec3f _direction){
    myDrawLine(vf_Pos, vf_Pos+_direction,1);
}


//--------------------------------------------------------------
void ofxObjectParent::setPos(float _f_Pan,float _f_Tilt,float _f_Distance){
    f_PosPan = _f_Pan;
    f_PosTilt = _f_Tilt;
    f_PosDistance = _f_Distance;
    vf_Pos.x = _f_Distance * cos(PI * _f_Tilt / 180.0) * sin(PI * _f_Pan / 180.0);
    vf_Pos.y = _f_Distance * cos(PI * _f_Tilt / 180.0) * cos(PI * _f_Pan / 180.0);
    vf_Pos.z = _f_Distance * sin(PI * _f_Tilt / 180.0);
}
//--------------------------------------------------------------
ofVec3f ofxObjectParent::getPos(){
    return vf_Pos;
}

//--------------------------------------------------------------
ofVec3f ofxObjectParent::getNorm(){
    return vf_NormalVec;
}
//--------------------------------------------------------------
void ofxObjectParent::setAngle(float _f_Pan,float _f_Tilt){
    f_AnglePan = _f_Pan;
    f_AngleTilt = _f_Tilt;
}
//--------------------------------------------------------------
void ofxObjectParent::setNormalVec(ofVec3f _norm){
    vf_NormalVec = _norm/_norm.length();
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
    //cout << "set" << f_AnglePan << " " << f_AngleTilt << endl;
}
//--------------------------------------------------------------
void ofxObjectParent::setAngleBetween(ofVec3f _pos1,ofVec3f _pos2){
    //鏡の法線を定める
    ofVec3f buf1,buf2;
    buf1 = _pos1 - vf_Pos;
    buf2 = _pos2 - vf_Pos;
    //cout<<buf1 << ":" << buf2<<endl;
    buf1 /= buf1.length();
    buf2 /= buf2.length();
    //cout<<buf1 << ":" << buf2<<endl;
    setNormalVec(buf1 + buf2);
}
