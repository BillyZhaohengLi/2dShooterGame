#pragma once

#include "ofMain.h"
#include "wall.h"
#include "player.h"
#include "const.h"
#include "shot.h"
#include "button.h"
#include "add_buttons.h"
#include "ofxCenteredTrueTypeFont.h"
#include "ofxNetwork.h"
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
		
		//update helper functions
		void update_menu();
		void update_single_params();
		void update_singleplayer_game();
		void update_pause();
		void update_round_over();
		void update_help();
		void update_multi_connect();

		//draw helper functions
		void draw_menu();
		void draw_single_params();
		void draw_singleplayer_game();
		void draw_pause();
		void draw_round_over();
		void draw_help();
		void draw_multi_connect();

		//helper function for taking player name
		void enter_name();
		void enter_ip();

		ofSoundPlayer shotSound;
		ofSoundPlayer dieSound;

		ofxCenteredTrueTypeFont game_title_text;
		ofxCenteredTrueTypeFont button_text;
		ofxCenteredTrueTypeFont character_name;

		ofxTCPServer multiplayer_server;
		ofxTCPClient multiplayer_client;

		bool connected_to_host;
};
