#include "ofApp.h"

//---setup; load different game elements to prepare for game
void ofApp::setup(){
	//unit tests in test folder. Not actually needed to run program; just comment out during build after done with unit testing
	//PLAYER_TESTS();
	//SHOT_TESTS();
	//WALL_TESTS();
	//BUTTON_TESTS();
	//MULTIPLAYER_NETWORK_TESTS();
	HELPERFUNCTIONS_TESTS();
	OBJECTHELPERFUNCTIONS_TESTS();

	//load sounds
	shotSound.load("fire_shot.wav");
	dieSound.load("die.wav");

	//add buttons in the level
	add_buttons_text(buttons_in_level, text_in_level);

	//tick the appropriate settings buttons in main menu
	buttons_in_level.tick_button(kBluePalette);
	buttons_in_level.tick_button(kFewWallsButton);

	//add boundaries to the level (the boundaries are fixed for each game anyways, better done sooner than later)
	levelbounds.add_boundary();
}

//---update function; call separate subdivided update functions based on current game state
void ofApp::update(){
	//one server can only have one client at a time; disconnect all clients beside client 0.
	multiplayer_network.disconnect_additional_clients();

	//handles the case when the program's partner disconnects in multiplayer; in this case this should be handled here to close the server and
	//go into the correct interface (disconnect) ASAP. Also resets the game elements to the singleplayer menu state.
	if (multiplayer_network.get_status() != NONE && !multiplayer_network.is_connected() && 
		game_current != MULTI_CONNECT) {
		multiplayer_network.close();
		reset_to_menu(p1, p2, shots_on_screen, levelbounds, multiplayer_network.get_status(), keydown);
		if (multiplayer_network.received_message_from_server()) {
			game_current = DISCONNECTED;
		}
		else {
			game_current = DISCONNECTED_BY_HOST;
		}
	}

	switch (game_current) {
	case MAIN_MENU:
	case MULTI_MENU:
		update_menu();
		break;
	case WAITING_ROOM:
		update_waiting_room();
		break;
	case IN_GAME_SINGLE:
	case IN_GAME_MULTI:
		update_singleplayer_game();
		break;
	case PAUSE:
		update_pause();
		break;
	case ROUND_OVER:
		update_round_over();
		break;
	case HELP:
		update_help();
		break;
	case MULTI_CONNECT:
		update_multi_connect();
		break;
	case DISCONNECTED:
	case DISCONNECTED_BY_HOST:
		update_disconnected();
		break;
	}
}

//---draw function; specific drawing subdivided to separate draw functions based on current game state
void ofApp::draw(){
	switch (game_current) {
	case MAIN_MENU:
	case MULTI_MENU:
		draw_menu();
		break;
	case IN_GAME_SINGLE:
	case IN_GAME_MULTI:
	case PAUSE:
	case ROUND_OVER:
		draw_singleplayer_game();
		break;
	case MULTI_CONNECT:
		draw_multi_connect();
		break;
	}

	//draw button and text in level
	text_in_level.draw_text(game_current);
	buttons_in_level.draw_button(game_current);
}

//---keypressed; sets the relevant cell in the keydown array to true.
void ofApp::keyPressed(int key){
	if (key >= 0 && key <= 255) {
		if (game_current == IN_GAME_SINGLE || game_current == IN_GAME_MULTI) {
			//if there is a game currently going on set the keys to case insensitive
			keydown[toupper(key)] = true;
			//if pause is pressed during a single player game pause the game
			if (toupper(key) == kPause && game_current == IN_GAME_SINGLE) {
				game_current = PAUSE;
			}
		}
		else if (game_current == PAUSE) {
			keydown[toupper(key)] = true;
			//if pause is pressed during pause then resume the game
			if (toupper(key) == kPause) {
				game_current = IN_GAME_SINGLE;
			}
		}
		else {
			keydown[key] = true;
		}
	}
}

//---keyreleased; sets the relevant cell in the keydown array to false.
void ofApp::keyReleased(int key){
	if (key >= 0 && key <= 255) {
		//if there is a game currently going on set the keys to case insensitive
		if (game_current == IN_GAME_SINGLE || game_current == PAUSE || game_current == IN_GAME_MULTI) {
			keydown[toupper(key)] = false;
		}
		else {
			keydown[key] = false;
		}
	}
}

//---mouse pressed; sets mouse_down to true
void ofApp::mousePressed(int x, int y, int button){
	mouse_down = true;
}

//---mouse released; sets mouse_down and mouse_held to false.
void ofApp::mouseReleased(int x, int y, int button){
	mouse_down = false;
	mouse_held = false;
}

void ofApp::update_menu() {
	//receive and handle message from partner; if singleplayer this part is skipped since the size of message will be 0.
	string message = multiplayer_network.receive();
	if (message.size() > 0) {
		//if the message begins with the player model string then it is a message to update the opponent's player model;
		if (message.substr(0, strlen(kPlayerString)) == kPlayerString) {
			p2.deserialize_update_model_message(message);
		}
		//if the message begins with update game string then it is a message to update the generated walls in the level and start the game.
		else if (message.substr(0, strlen(kPlayerString)) == kUpdateString) {
			reset_game(p1, p2, shots_on_screen, keydown);
			levelbounds.deserialize_update_message(message.substr(strlen(kPlayerString)));
			game_current = IN_GAME_MULTI;
			return;
		}
	}

	//helper function to enter name
	enter_name(entered, player_name, keydown);

	//check if any button is pressed
	if (mouse_down && !mouse_held) {
		mouse_held = true;
		int pressed = buttons_in_level.on_button(ofGetMouseX(), ofGetMouseY(), game_current);
		switch (pressed) {

		//single player button; sets the player name to whatever the user entered.
		case (kStartSingleplayerButton):
			//sets the typed name to the player
			p1.set_name(player_name);
			entered = false;

			//generate walls
			levelbounds.random_level_generator(walls_amount);

			//reset players to be ready for the game
			reset_game(p1, p2, shots_on_screen, keydown);

			switch (multiplayer_network.get_status()) {

			//case for singleplayer game
			case (NONE):
				//sets a random name and color for the bot
				p2.randomize_appearance();
				game_current = IN_GAME_SINGLE;
				return;
				break;

			//case for multiplayer game
			default:
				//sends the signal to the partner to start the game; while waiting for response move into waiting room
				multiplayer_network.send(kUpdateString + levelbounds.serialized_string());
				buffer = kUpdateString + levelbounds.serialized_string();
				game_current = WAITING_ROOM;
				return;
				break;
			}
			break;

		//multiplayer button; takes the player to the multiplayer interface and starts the TCP server
		case (kStartMultiplayerButton):
			game_current = MULTI_CONNECT;
			break;

		//help button; sends the player to the help interface
		case (kHelpButton):
			game_current = HELP;
			break;

		//exit button; exits the program.
		case (kExitButton):
			std::exit(0);
			break;

		//disconnect from the session.
		case (kMultiDisconnectButton):
			//close either the server or the client based on what the program was connected to the session as and reset the game objects.
			multiplayer_network.close();
			reset_to_menu(p1, p2, shots_on_screen, levelbounds, 
				multiplayer_network.get_status(), keydown);
			game_current = DISCONNECTED;
			break;

		//palette buttons; modifies the player color based on the palette clicked (also unticks all other color palettes)
		case (kRedPalette):
		case (kGreenPalette):
		case (kBluePalette):
		case (kYellowPalette):
		case (kMagentaPalette):
		case (kCyanPalette):
			for (int i = kRedPalette; i <= kCyanPalette; i++) {
				buttons_in_level.untick_button(i);
			}
			buttons_in_level.tick_button(pressed);
			p1.set_color(pressed);
			break;

		//button for generating walls in the level. (unticks all other wall choices)
		case (kFewWallsButton):
		case (kMediumWallsButton):
		case (kALotWallsButton):
			for (int i = kFewWallsButton; i <= kALotWallsButton; i++) {
				buttons_in_level.untick_button(i);
			}
			buttons_in_level.tick_button(pressed);
			walls_amount = wall_button_to_wall_amount(pressed);
			break;
		}
	}

	//update the player's parameters based on the modifications made in the update call
	p1.update_player_facing(ofGetMouseX(), ofGetMouseY(), p2);
	p1.set_name(player_name);

	//send the data of the player to the other user.
	if (multiplayer_network.is_connected()) {
		multiplayer_network.send(p1.serialized_model_string());
	}
}

void ofApp::update_waiting_room() {
	//waiting room; the program which initiated a change of interface should wait here for response from their partner
	//to ensure that they are on the same interface.
	string message = multiplayer_network.receive();
	if (message.size() > 0) {
		//messages beginning with 'U', 'T' and 'F' signify that the partner is in the multiplayer game and the program should proceed.
		if (message.substr(0, strlen(kPlayerString)) == kUpdateString || message[0] == kTrueBooleanChar ||
			message[0] == kFalseBooleanChar) {
			game_current = IN_GAME_MULTI;
		}
		//messages beginning with 'P' signify that the partner is back in the main menu and the program should proceed, if the program is currently in the game over screen
		else if (message.substr(0, strlen(kPlayerString)) == kPlayerString && buffer == kBackMainString) {
			game_current = MULTI_MENU;
		}
	}
	multiplayer_network.send(buffer);
}

void ofApp::update_singleplayer_game() {
	//updates for singleplayer game
	if (multiplayer_network.get_status() == NONE) {
		//reduces the firing cooldown of the players.
		p1.cooldown_reduce();
		p2.cooldown_reduce();

		//determines the players' new direction based on the keys held down at this particular time.
		p1.change_direction({ keydown[kUp], keydown[kLeft], keydown[kDown], keydown[kRight] });
		p2.change_direction({ keydown[kUp], keydown[kLeft], keydown[kDown], keydown[kRight] });

		//update the direction the players' guns point at.
		p1.update_player_facing(ofGetMouseX(), ofGetMouseY(), p2);
		p2.update_player_facing(ofGetMouseX(), ofGetMouseY(), p1);

		//after changing directions, move the players.
		p1.move();
		p2.move();

		//if the player collides with wall segment(s), resolve the collision(s).
		levelbounds.collision_resolver(p1);
		levelbounds.collision_resolver(p2);

		//check firing shots for both players
		bool obstructed = levelbounds.player_path_obstructed(p1, p2);
		pair<pair<bool, double>, pair<double, double>> p1_shot_params = 
			p1.shoot_prompt(mouse_down, obstructed);
		pair<pair<bool, double>, pair<double, double>> p2_shot_params = 
			p2.shoot_prompt(mouse_down, obstructed);
		if (p1_shot_params.first.first) {
			shotSound.play();
			shots_on_screen.add_shot(p1_shot_params.second.first, 
				p1_shot_params.second.second, p1_shot_params.first.second);
		}
		if (p2_shot_params.first.first) {
			shotSound.play();
			shots_on_screen.add_shot(p2_shot_params.second.first, 
				p2_shot_params.second.second, p2_shot_params.first.second);
		}

		//move all shots on the screen.
		shots_on_screen.move();

		//after moving the shots, bounce all shots which have hit a wall.
		levelbounds.bounce_shots(shots_on_screen);

		//determine whether any of the shots hit the player.
		shots_on_screen.hit_player(p1);
		shots_on_screen.hit_player(p2);

		//determine if either player is dead; if this is the case, play the dead sound, generate the game outcome message and change game interface.
		if (!p1.isalive() || !p2.isalive()) {
			dieSound.play();
			game_outcome_message = generate_game_over_message(p1, p2);
			game_current = ROUND_OVER;
		}
	}

	//updates for multiplayer game for client.
	//no calculations are done on client side; the job of the client is to send the input at every update to the host where the calculations
	//are handled and the level graphics are sent back to be parsed here.
	else if (multiplayer_network.get_status() == CLIENT) {
		string to_send = serialize_input(keydown, mouse_down, ofGetMouseX(), ofGetMouseY());
		multiplayer_network.send(to_send);

		//reading buffer until there are no messages left; causes data loss but drastically reduces lag
		string message = multiplayer_network.receive();
		//if there is a message update the shots on screen and the players accordingly.
		if (message.size() > 0) {
			vector<string> message_array = split(message, kBigDelimiter);
			if (message_array[0] == kUpdateString) {
				shots_on_screen.deserialize_update_message(message_array[1]);
				p2.deserialize_update_game_message(message_array[2]);
				p1.deserialize_update_game_message(message_array[3]);
				//denotes whether a shot was fired; if yes, play the shot sound.
				if (message_array[4] == kTrueBoolean) {
					shotSound.play();
				}
			}
		}

		//determine if either player is dead; if this is the case, play the dead sound, generate the game outcome message and change game interface.
		if (!p1.isalive() || !p2.isalive()) {
			dieSound.play();
			game_outcome_message = generate_game_over_message(p1, p2);
			game_current = ROUND_OVER;
		}
	}

	//updates for multiplayer game for host.
	//all calculations are done on the host server; receives input from the client and handles player movement, sending the game status back to the client
	//at every update.
	else if (multiplayer_network.get_status() == HOST) {
		bool shot_fired = false;
		//reduces the firing cooldown of the players.
		p1.cooldown_reduce();
		p2.cooldown_reduce();

		//updates the parameters of p1; for a detailed description see the singleplayer game engine.
		p1.change_direction({ keydown[kUp], keydown[kLeft], keydown[kDown], keydown[kRight] });
		p1.update_player_facing(ofGetMouseX(), ofGetMouseY(), p2);
		p1.move();
		levelbounds.collision_resolver(p1);
		pair<pair<bool, double>, pair<double, double>> p1_shot_params = p1.shoot_prompt(mouse_down, false);
		if (p1_shot_params.first.first) {
			shot_fired = true;
			shotSound.play();
			shots_on_screen.add_shot(p1_shot_params.second.first, p1_shot_params.second.second, p1_shot_params.first.second);
		}

		//if there is a valid message, update the parameters of p2; otherwise don't do anything with them.
		string message = multiplayer_network.receive();
		if (message.size() > 0 && (message[0] == kTrueBooleanChar || message[0] == kFalseBooleanChar)) {
			pair<pair<vector<bool>, bool>, pair<double, double>> message_pairs = deserialize_input(message);
			p2.change_direction(message_pairs.first.first);
			p2.update_player_facing(message_pairs.second.first, message_pairs.second.second, p1);
			p2.move();
			levelbounds.collision_resolver(p2);
			pair<pair<bool, double>, pair<double, double>> p2_shot_params = p2.shoot_prompt(message_pairs.first.second, false);
			if (p2_shot_params.first.first) {
				shot_fired = true;
				shotSound.play();
				shots_on_screen.add_shot(p2_shot_params.second.first, p2_shot_params.second.second, p2_shot_params.first.second);
			}
		}

		//move all shots on the screen.
		shots_on_screen.move();

		//after moving the shots, bounce all shots which have hit a wall.
		levelbounds.bounce_shots(shots_on_screen);

		//determine whether any of the shots hit the player.
		shots_on_screen.hit_player(p1);
		shots_on_screen.hit_player(p2);

		//send updated game to client
		string to_send = (kUpdateString + shots_on_screen.serialized_string() + 
			p1.serialized_game_string() + p2.serialized_game_string() + kBigDelimiter);
		//determines whether a shot was fired this frame; if yes tell the client to play the shot_fired sound.
		if (shot_fired) {
			to_send += kTrueBoolean;
		}
		else {
			to_send += kFalseBoolean;
		}
		multiplayer_network.send(to_send);

		//determine if either player is dead; if this is the case, play the dead sound, generate the game outcome message and change game interface.
		if (!p1.isalive() || !p2.isalive()) {
			dieSound.play();
			game_outcome_message = generate_game_over_message(p1, p2);
			game_current = ROUND_OVER;
		}
	}	
}

void ofApp::update_pause() {
	//detect pressed buttons
	if (mouse_down && !mouse_held) {
		mouse_held = true;
		switch (buttons_in_level.on_button(ofGetMouseX(), ofGetMouseY(), game_current)) {
		//go back to main menu
		case (kPausedToMenuButton):
			//reset the level
			reset_to_menu(p1, p2, shots_on_screen, levelbounds, multiplayer_network.get_status(), keydown);
			game_current = MAIN_MENU;
			break;
		}
	}
}

void ofApp::update_round_over() {
	//receive message from the client/server if applicable
	string message = multiplayer_network.receive();

	//if there is a message, interpret it and determine what button the other user pressed and update game state accordingly.
	if (message.size() > 0) {
		//other user pressed rematch
		if (message == kRematchString) {
			reset_game(p1, p2, shots_on_screen, keydown);
			game_current = IN_GAME_MULTI;
			return;
		}
		//other user pressed back to main
		else if (message == kBackMainString) {
			reset_to_menu(p1, p2, shots_on_screen, levelbounds, multiplayer_network.get_status(), keydown);
			game_current = MULTI_MENU;
			return;
		}
	}

	//detect pressed buttons
	if (mouse_down && !mouse_held) {
		mouse_held = true;
		switch (buttons_in_level.on_button(ofGetMouseX(), ofGetMouseY(), game_current)) {

		//rematch button; does not regenerate walls, but reset the players and the shots.
		case (kRematchButton):
			reset_game(p1, p2, shots_on_screen, keydown);

			switch (multiplayer_network.get_status()) {

			//case for singleplayer game
			case (NONE):
				game_current = IN_GAME_SINGLE;
				break;

			//case for multiplayer
			default:
				multiplayer_network.send(kRematchString);
				buffer = kRematchString;
				game_current = WAITING_ROOM;
				break;
			}
		break;
		//return to main menu; reset all appropriate game objects.
		case (kRoundOverToMenuButton):
			reset_to_menu(p1, p2, shots_on_screen, levelbounds, multiplayer_network.get_status(), keydown);
			switch (multiplayer_network.get_status()) {

			//case for singleplayer game
			case (NONE):
				game_current = MAIN_MENU;
				break;

			//case for multiplayer game; sends a message to the partner to go back to main menu.
			default:
				multiplayer_network.send(kBackMainString);
				buffer = kBackMainString;
				game_current = WAITING_ROOM;
				break;
			}
		}
	}
}

void ofApp::update_help() {
	//detect pressed buttons
	if (mouse_down && !mouse_held) {
		mouse_held = true;
		switch (buttons_in_level.on_button(ofGetMouseX(), ofGetMouseY(), game_current)) {

		//go back to main menu
		case (kHelpToMenuButton):
			game_current = MAIN_MENU;
			break;
		}
	}
}

void ofApp::update_multi_connect() {
	//enter ip address
	enter_ip(entered, ip_address, keydown);

	if (multiplayer_network.is_connected()) {
		multiplayer_string = "";
		reset_to_menu(p1, p2, shots_on_screen, levelbounds, multiplayer_network.get_status(), keydown);

		//send the details of the player to the other user
		multiplayer_network.send(p1.serialized_model_string());

		//set enums accordingly
		game_current = MULTI_MENU;
	}

	//detect pressed buttons
	if (mouse_down && !mouse_held) {
		bool setup;
		mouse_held = true;
		switch (buttons_in_level.on_button(ofGetMouseX(), ofGetMouseY(), game_current)) {

		//connect to a server at the specified ip address.
		case (kConnectToServerButton):
			setup = multiplayer_network.client_setup(ip_address);
			//if the connection was not successful, show the failure message
			if (!setup) {
				multiplayer_string = kConnectFail;
			}
			break;
		
		//start a multiplayer server
		case (kStartServerButton):
			//prevent a second server from starting if this program instance is already hosting one
			if (multiplayer_string == kHostingServer || multiplayer_string == kAlreadyHost) {
				multiplayer_string = kAlreadyHost;
			}
			//otherwise attempt to set up a server
			else {
				setup = multiplayer_network.server_setup();
				//setup failed
				if (!setup) {
					multiplayer_string = kServerConflict;
				}
				//setup success
				else {
					multiplayer_string = kHostingServer;
				}
			}
			break;

		//go back to main menu
		case (kMultiConnectToMenuButton):
			multiplayer_string = "";
			multiplayer_network.close();
			game_current = MAIN_MENU;
			break;
		}
	}
}

void ofApp::update_disconnected() {
	if (mouse_down && !mouse_held) {
		mouse_held = true;
		switch (buttons_in_level.on_button(ofGetMouseX(), ofGetMouseY(), game_current)) {
		case (kDisconnectConfirmButton):
			game_current = MAIN_MENU;
			break;
		}
	}
}

void ofApp::draw_menu() {
	//draw player name
	text_in_level.draw_dynamic_text(player_name, kLevelWidthMultiplier * kWallWidth * 0.1, 
		kLevelHeightMultiplier * kWallWidth * 0.4, false, 2);

	//draw the demo player
	p1.draw_player();

	//if there is a connected partner also draw the opponent
	if (multiplayer_network.is_connected()) {
		p2.draw_player();
	}
}

void ofApp::draw_singleplayer_game() {
	//draw all wall segments
	levelbounds.draw_all_walls();

	//draw the player
	p1.draw_player();
	p2.draw_player();

	//draw the shots
	shots_on_screen.draw_shot();

	//draw additional objects based on game state
	switch (game_current) {

	//game is paused
	case (PAUSE):
		//draw an overlaying rectangle to prevent black text from mixing in with the walls
		ofSetColor(ofColor::white, 128);
		ofDrawRectangle(kLevelWidthMultiplier * kWallWidth * 0.25, kLevelHeightMultiplier * kWallWidth * 0.25, 
			kLevelWidthMultiplier * kWallWidth * 0.5, kLevelHeightMultiplier * kWallWidth * 0.5);
		break;

	//game is over
	case (ROUND_OVER):
		//draw an overlaying rectangle to prevent black text from mixing in with the walls
		ofSetColor(ofColor::white, 128);
		ofDrawRectangle(kLevelWidthMultiplier * kWallWidth * 0.1, kLevelHeightMultiplier * kWallWidth * 0.9,
			kLevelWidthMultiplier * kWallWidth * 0.8, kLevelHeightMultiplier * kWallWidth * 0.08);

		//draw the match outcome
		text_in_level.draw_dynamic_text(game_outcome_message, kLevelWidthMultiplier * kWallWidth * 0.12,
			kLevelHeightMultiplier * kWallWidth * 0.95, false, 2);
		break;
	}
}

void ofApp::draw_multi_connect() {
	//draw the current entered ip address
	text_in_level.draw_dynamic_text("IP address:" + ip_address, kLevelWidthMultiplier * kWallWidth * 0.1,
		kLevelHeightMultiplier * kWallWidth * 0.45, false, 2);

	//draw the text signifying the status of the multiplayer network (e.g. server set up, connection failed)
	text_in_level.draw_dynamic_text(multiplayer_string, kLevelWidthMultiplier * kWallWidth * 0.1,
		kLevelHeightMultiplier * kWallWidth * 0.55, false, 2);
}

//---methods down here are default openframeworks functions which were not used in this program.
void ofApp::mouseMoved(int x, int y) {}
void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mouseEntered(int x, int y) {}
void ofApp::mouseExited(int x, int y) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}
void ofApp::gotMessage(ofMessage msg) {}