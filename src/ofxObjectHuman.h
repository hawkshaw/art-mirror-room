/*
 *
 */
#pragma once

#ifndef __ofxObjectHuman__
#define __ofxObjectHuman__

#include "ofMain.h"
#include "ofxObjectParent.h"


class ofxObjectHuman :public ofxObjectParent{
public:
    ofxObjectHuman();
    void draw();
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
