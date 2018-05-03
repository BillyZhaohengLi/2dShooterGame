#pragma once

#include "ofMain.h"
#include "const.h"
#include "ofxNetwork.h"
#include "game_assets/wall.h"
#include "game_assets/player.h"
#include "game_assets/shot.h"
#include "game_addons/button.h"
#include "game_addons/gametext.h"
#include "game_addons/multiplayernetwork.h"
#include "game_addons/ofxCenteredTrueTypeFont.h"
#include "helpers/add_buttons_text.h"
#include "helpers/objecthelperfunctions.h"
#include <mmsystem.h>

//unit test headers. comment out when finished with testing and building the actual program.
#include "test/player_tests.h"
#include "test/shot_tests.h"
#include "test/wall_tests.h"
#include "test/button_tests.h"
#include "test/multiplayer_network_tests.h"
#include "test/helperfunctions_tests.h"
#include "test/objecthelperfunctions_tests.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		
		//update helper functions
		void update_menu();
		void update_waiting_room();
		void update_singleplayer_game();
		void update_pause();
		void update_round_over();
		void update_help();
		void update_multi_connect();
		void update_disconnected();

		//draw helper functions
		void draw_menu();
		void draw_singleplayer_game();
		void draw_multi_connect();

		//sounds to be used in game
		ofSoundPlayer shotSound;
		ofSoundPlayer dieSound;

		//tcp server and client; used for multiplayer
		MultiplayerNetwork multiplayer_network;

		//buffer string for continually repeating the last message sent while in the waiting room.
		string buffer;

		//string to display in the multiplayer connect interface indicating success/failure of connections.
		string multiplayer_string;

		//game outcome message to be displayed in the game over screen indicating which player won.
		string game_outcome_message;

		//array of booleans used to store which keys are held down.
		bool keydown[255];

		//boolean on whether the left mouse button is held down.
		bool mouse_down;

		//boolean on whether the mouse is held; used to prevent more than one button being 
		//triggered with one mouse press
		bool mouse_held;

		//boolean for handling player input for player name in main menu; used to prevent 
		//multiple keys being entered with one press
		//due to how fast update is called. By default nothing has been entered yet.
		bool entered = false;

		//the amount of walls to generate in a level when the start button is clicked. 
		//Defaults to the minimum option.
		int walls_amount = kFewWallsAmount;

		//wall object containing the walls in the level.
		Wall levelbounds;

		//shotInLevel object containing the shots on screen.
		ShotInLevel shots_on_screen;

		//buttons in game
		AllButtons buttons_in_level;

		//text in game
		AllText text_in_level;

		//the current interface the program is in. instantiated to start at main menu
		GameState game_current = MAIN_MENU;

		//store player name.
		string player_name;

		//store ip address.
		string ip_address;

		//players in the game. By default p1 is the player character and p2 is a bot.
		Player p1 = Player(kLevelWidthMultiplier * kWallWidth * 0.5, 
			kLevelHeightMultiplier * kWallWidth * 0.4, 
			kBluePalette, false, "default");
		Player p2 = Player((kLevelWidthMultiplier - 2.5) * kWallWidth, 
			kWallWidth * 2.5, kBluePalette, true, "default");

		//methods down here are default openframeworks functions which were not used in this program.
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
};
