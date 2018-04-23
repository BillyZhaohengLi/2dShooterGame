#pragma once

#include "ofMain.h"
#include "wall.h"
#include "player.h"
#include "const.h"
#include "shot.h"
#include "button.h"
#include "add_buttons.h"
#include "ofxCenteredTrueTypeFont.h"
#include <mmsystem.h>

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
		
		void update_menu();
		void update_single_params();
		void update_singleplayer_game();
		void update_pause();

		void draw_menu();
		void draw_single_params();
		void draw_singleplayer_game();
		void draw_pause();

		void ofApp::enter_name();

		ofxCenteredTrueTypeFont game_title_text;
		ofxCenteredTrueTypeFont button_text;
		ofxCenteredTrueTypeFont character_name;
};
