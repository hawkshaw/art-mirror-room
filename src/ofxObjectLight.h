/*
 *
 */
#pragma once

#ifndef __ofxObjectLight__
#define __ofxObjectLight__

#include "ofMain.h"
#include "ofxObjectParent.h"


class ofxObjectLight :public ofxObjectParent{
public:
    ofxObjectLight();
    void draw();
    virtual void setPos(float _f_Pan,float _f_Tilt,float _f_Distance);
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
    ofLight light;
};


#endif
