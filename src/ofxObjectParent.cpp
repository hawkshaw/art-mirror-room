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
void ofxObjectParent::update(int _i_AngleSpeed){
    bool b_AngleChange = false;
    if(abs(f_AnglePanDest - f_AnglePan) < 1.0){
        f_AnglePan = f_AnglePanDest;
        b_AngleChange = true;
    }
    if(abs(f_AngleTiltDest - f_AngleTilt) < 1.0){
        f_AngleTilt = f_AngleTiltDest;
        b_AngleChange = true;
    }
    if(f_AnglePanDest != f_AnglePan){
        f_AnglePan = (f_AnglePanDest + f_AnglePan * _i_AngleSpeed)/ (1 + _i_AngleSpeed);
        b_AngleChange = true;
    }
    if(f_AngleTiltDest != f_AngleTilt){
        f_AngleTilt = (f_AngleTiltDest + f_AngleTilt * _i_AngleSpeed)/ (1 + _i_AngleSpeed);
        b_AngleChange = true;
    }
    if(b_AngleChange){
        vf_NormalVec.x = cos(PI * f_AngleTilt / 180.0) * sin(PI * f_AnglePan / 180.0);
        vf_NormalVec.y = cos(PI * f_AngleTilt / 180.0) * cos(PI * f_AnglePan / 180.0);
        vf_NormalVec.z = sin(PI * f_AngleTilt / 180.0);
    }
}

void ofxObjectParent::drawLineTo(ofVec3f _pos){
    ofDrawLine(vf_Pos, _pos);
}

void ofxObjectParent::drawLineDir(ofVec3f _direction){
    ofDrawLine(vf_Pos, vf_Pos+_direction);
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
    f_AnglePanDest = _f_Pan;
    f_AngleTiltDest = _f_Tilt;
    vf_NormalVec.x = cos(PI * _f_Tilt / 180.0) * sin(PI * _f_Pan / 180.0);
    vf_NormalVec.y = cos(PI * _f_Tilt / 180.0) * cos(PI * _f_Pan / 180.0);
    vf_NormalVec.z = sin(PI * _f_Tilt / 180.0);
}
//--------------------------------------------------------------
void ofxObjectParent::setRandomAngle(){
    moveAngle(f_PosPan + ofRandom(-10, 10), f_PosTilt + ofRandom(-10, 10));
}
//--------------------------------------------------------------
void ofxObjectParent::moveAngle(float _f_Pan,float _f_Tilt){
    f_AnglePanDest = _f_Pan;
    f_AngleTiltDest = _f_Tilt;
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
    f_AngleTiltDest = f_AngleTilt;
    f_AnglePanDest = f_AnglePan;
}

//--------------------------------------------------------------
ofVec3f ofxObjectParent::convPanTilt2Vec(float _f_Pan,float _f_Tilt){
    ofVec3f out;
    out.x = cos(PI * _f_Tilt / 180.0) * sin(PI * _f_Pan / 180.0);
    out.y = cos(PI * _f_Tilt / 180.0) * cos(PI * _f_Pan / 180.0);
    out.z = sin(PI * _f_Tilt / 180.0);
    return out;
}
//--------------------------------------------------------------
ofVec2f ofxObjectParent::convVec2PanTilt(ofVec3f _norm){
    float _f_AnglePan,_f_AngleTilt;
    if(_norm.y==0){
        _f_AnglePan = 90.0;
    }else{
        if(_norm.y > 0){
            _f_AnglePan = 180.0 * atan(_norm.x / _norm.y) / PI;
        }else{
            if(_norm.x > 0){
                _f_AnglePan = 180 + 180.0 * atan(_norm.x / _norm.y) / PI;
            }else{
                _f_AnglePan = 180.0 * atan(_norm.x / _norm.y) / PI - 180;
            }
        }
    }
    if((_norm.y ==0) and (_norm.x == 0)){
        _f_AngleTilt = 90.0;
    }else{
        _f_AngleTilt = 180.0 * atan(_norm.z / ofVec2f(_norm.x,_norm.y).length()) / PI;
    }
    return ofVec2f(_f_AnglePan,_f_AngleTilt);
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
