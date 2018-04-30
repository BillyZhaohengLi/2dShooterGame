#include "ofMain.h"
#include "ofApp.h"
#include "const.h"

//========================================================================
int main( ){
	ofGLFWWindowSettings settings;
	settings.width = kLevelWidthMultiplier * kWallWidth;
	settings.height = kLevelHeightMultiplier * kWallWidth;
	settings.decorated = false;
	settings.windowMode = OF_WINDOW;
	ofCreateWindow(settings);		// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofSetFrameRate(40);
	ofRunApp(new ofApp());
}
