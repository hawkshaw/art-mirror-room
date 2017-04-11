#pragma once

#include "ofMain.h"
#include "ofxObjectMirror.h"
#include "ofxObjectHuman.h"
#include "ofxObjectLight.h"
#include "ofxGui.h"

#include "ofxFboBlur.h"

#define MIR_X_NUM 5
#define MIR_X_ANG 9*1.5
#define MIR_Y_NUM 5
#define MIR_Y_ANG 9*1.5

#define NUM 500
#define SIZE 10

#define RADIUS 700

class ofApp : public ofBaseApp{
public:

    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    bool b_GuiDraw;
    bool b_TestLight;
    ofLight testLight;
    
    ofLight areaLight;
    ofPlanePrimitive plane;
    
    ofMaterial materialPlane;
    
    int i_test;
    
    vector<ofxObjectMirror> v_ObjectMirror;
    vector<ofxObjectHuman> v_ObjectHuman;
    vector<ofxObjectLight> v_ObjectLight;
    
    int i_Camera;
    bool b_Render;
    
    vector<ofEasyCam> v_Camera;
    
    ofxFboBlur gpuBlur;
    
    ofxPanel gui;
    ofxIntSlider pi_AngleSpeed;

    
};
