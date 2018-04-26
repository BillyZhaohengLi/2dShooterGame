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
		void update_multi_menu();
		void update_singleplayer_game();
		void update_pause();
		void update_round_over();
		void update_help();
		void update_multi_connect();

		//draw helper functions
		void draw_menu();
		void draw_multi_menu();
		void draw_singleplayer_game();
		void draw_pause();
		void draw_round_over();
		void draw_help();
		void draw_multi_connect();

		//sounds to be used in game
		ofSoundPlayer shotSound;
		ofSoundPlayer dieSound;

		//fonts to be used in game
		ofxCenteredTrueTypeFont game_title_text;
		ofxCenteredTrueTypeFont button_text;
		ofxCenteredTrueTypeFont character_name;

		//tcp server and client; used for multiplayer
		ofxTCPServer multiplayer_server;
		ofxTCPClient multiplayer_client;

		//boolean for whether the user is connected to a host. Only used as a signal to switch to the multiplayer main menu.
		bool connected_to_host;

		//array of booleans used to store which keys are held down.
		bool keydown[255];

		//boolean on whether the left mouse button is held down.
		bool mouse_down;

		//boolean on whether the mouse is held; used to prevent crashing interfaces
		bool mouse_held;

		//boolean for handling player input for player name in main menu; used to prevent multiple keys being entered with one press
		//due to how fast update is called.
		bool entered;

		//boolean for handling whether the player is in multiplayer mode.
		bool in_multi;

		//the amount of walls to generate in a level when the start button is clicked.
		int walls_amount;

		//wall object containing the walls in the level.
		Wall levelbounds;

		//shotInLevel object containing the shots on screen.
		ShotInLevel shots_on_screen;

		//instantiate buttons in game
		AllButtons buttons_in_level;

		//instantiate game to start at main menu
		game_state game_current;

		//store player name.
		string player_name;

		//store ip address.
		string ip_address;

		//enum for game outcome.
		winner game_result;

		//enum for the state of the program; used to handle communication based on whether the program is a client or a host.
		connection client_server;

		//players in the game. By default p1 is the player character and p2 is a bot.
		Player p1 = Player(wall_width * 2.5, (level_height_multiplier - 2.5) * wall_width, 0, 0, 255, false, "default");
		Player p2 = Player((level_width_multiplier - 2.5) * wall_width, wall_width * 2.5, 0, 0, 255, true, "default");
};
