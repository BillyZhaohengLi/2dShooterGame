#include "ofMain.h"
#include "ofApp.h"
#include "const.h"

//========================================================================
int main( ){
	//sets the window to borderless windowed.
	//this was done because of weird coordinate issues with openFrameworks;
	//in a bordered window, the 0 y coordinate for in-game drawing is located at the
	//top of the window hidden under the border while the 0 y coordinate for the mouse
	//starts at the bottom of the border, causing undesirable discrepancy between
	//the mouse position as it appears in game and where the mouse actually is.
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
