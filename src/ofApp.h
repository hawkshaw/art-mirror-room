#pragma once

#include "ofMain.h"
#include "ofxObjectMirror.h"
#include "ofxBlur.h"
#include "ofxPostGlitch.h"


#define MIR_X_NUM 5
#define MIR_X_ANG 9
#define MIR_Y_NUM 5
#define MIR_Y_ANG 9

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
		
        bool b_TestLight;
        ofLight testLight;
    
		ofLight areaLight;
		ofPlanePrimitive plane;
		ofEasyCam camera;
        ofCamera cam;
		ofMaterial materialPlane;
    
    int i_test;
    
        vector<ofxObjectMirror> v_ObjectMirror;
    
    ofxBlur blur;
    ofFbo fbo;
    	ofxPostGlitch	myGlitch;
    ofFbo			myFbo;
    
    bool b_Camera;
};
