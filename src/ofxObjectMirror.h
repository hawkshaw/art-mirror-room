/*
 *
 */
#pragma once

#ifndef __ofxObjectMirror__
#define __ofxObjectMirror__

#include "ofMain.h"
#include "ofxObjectParent.h"


#define MIRROR_RADIUS 40


class ofxObjectMirror :public ofxObjectParent{
public:
    ofxObjectMirror();
    void draw();
    void drawNorm();
    ofVec3f getMirrorPos(ofVec3f _pos);
    ofVec3f getReflectDir(ofVec3f _pos);
    /*
     In this case
     Pan+: to right
     Tilt+: go up
     
     In general
     Roll+: right side down
     Pitch+: go up
     Yaw+: to right
     */
private:
};


#endif
