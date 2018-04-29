#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//load sounds
	shotSound.load("fire_shot.wav");
	dieSound.load("die.wav");

	//add buttons in the level
	add_buttons_text(buttons_in_level, text_in_level);

	//tick the appropriate settings buttons in main menu
	buttons_in_level.tick_button(blue_button);
	buttons_in_level.tick_button(few_walls);

	//add boundaries to the level (the boundaries are fixed for each game anyways, better done sooner than later)
	levelbounds.add_boundary();
}

//--------------------------------------------------------------
void ofApp::update(){
	//call separate update functions based on current game state
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
	case MULTI_ROUND_OVER:
		update_round_over();
		break;
	case HELP:
		update_help();
		break;
	case MULTI_CONNECT:
		update_multi_connect();
		break;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//specific drawing done by separate draw functions based on current game state
	switch (game_current) {
	case MAIN_MENU:
	case MULTI_MENU:
		draw_menu();
		break;
	case IN_GAME_SINGLE:
	case IN_GAME_MULTI:
	case PAUSE:
	case ROUND_OVER:
	case MULTI_ROUND_OVER:
		draw_singleplayer_game();
		break;
	case MULTI_CONNECT:
		draw_multi_connect();
		break;
	}

	//draw button and text in level
	ofSetColor(0, 0, 0);
	text_in_level.draw_text(game_current);
	buttons_in_level.draw_button(game_current);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key >= 0 && key <= 255) {
		//sets the relevant cell in the keydown array to true
		if (game_current == IN_GAME_SINGLE) {
			//if there is a game currently going on set the keys to case insensitive
			keydown[toupper(key)] = true;
			//if pause is pressed during a single player game pause the game
			if (toupper(key) == 'P') {
				game_current = PAUSE;
			}
		}
		else if (game_current == IN_GAME_MULTI) {
			keydown[toupper(key)] = true;
		}
		else if (game_current == PAUSE) {
			//if pause is pressed during pause then resume the game
			keydown[toupper(key)] = true;
			if (toupper(key) == 'P') {
				game_current = IN_GAME_SINGLE;
			}
		}
		else {
			keydown[key] = true;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key >= 0 && key <= 255) {
		//sets the relevant cell in the keydown array to true
		if (game_current == IN_GAME_SINGLE || game_current == PAUSE) {
			keydown[toupper(key)] = false;
		}
		else if (game_current == IN_GAME_MULTI) {
			keydown[toupper(key)] = false;
		}
		else {
			keydown[key] = false;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	mouse_down = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	mouse_down = false;
	mouse_held = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::update_menu() {
	string message;

	//receive message; also handle the case if the connection is terminated
	if (multiplayer_network.get_status() != NONE) {
		//if the connection is terminated set variables accordingly, close the servere and go back to main menu
		if (!multiplayer_network.is_connected()) {
			multiplayer_network.close();
			p2.set_bot(true);
			p1.set_location(level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.4);
			game_current = MAIN_MENU;
		}
		//otherwise recieve a message from the client
		message = multiplayer_network.receive();
	}

	//handle message from partner
	if (message.size() > 0) {
		//if the message begins with "PLAYER" then it is a message to update the opponent's player model;
		if (message.substr(0, 6) == "PLAYER") {
			p2.deserialize_update_model_message(message);
		}
		else if (message.substr(0, 6) == "UPDATE") {
			switch (multiplayer_network.get_status()) {
			case (HOST):
				p1.reset_player((level_width_multiplier - 2.5) * wall_width, wall_width * 2.5);
				p2.reset_player(wall_width * 2.5, (level_height_multiplier - 2.5) * wall_width);
				break;
			case (CLIENT):
				p2.reset_player((level_width_multiplier - 2.5) * wall_width, wall_width * 2.5);
				p1.reset_player(wall_width * 2.5, (level_height_multiplier - 2.5) * wall_width);
				break;
			}
			levelbounds.deserialize_update_message(message.substr(6));
			game_current = IN_GAME_MULTI;
			return;
		}
	}

	//helper function to enter name
	pair<bool, string> temp = enter_name(entered, player_name, keydown);
	entered = temp.first;
	player_name = temp.second;

	//check if any button is pressed
	if (mouse_down && !mouse_held) {
		int pressed = buttons_in_level.on_button(ofGetMouseX(), ofGetMouseY(), game_current);
		switch (pressed) {

		//single player button; sets the player name to whatever the user entered.
		case (start_singleplayer_button):
			//sets the typed name to the player
			p1.set_name(player_name);

			//generate walls
			levelbounds.random_level_generator(walls_amount);

			//reset players to be ready for the game
			p1.reset_player(wall_width * 2.5, (level_height_multiplier - 2.5) * wall_width);
			p2.reset_player((level_width_multiplier - 2.5) * wall_width, wall_width * 2.5);

			mouse_held = true;
			entered = false;
			switch (multiplayer_network.get_status()) {
			case (NONE):
				//sets a random name and color for the bot
				p2.randomize_name();
				p2.randomize_color();
				game_current = IN_GAME_SINGLE;
				return;
				break;
			default:
				multiplayer_network.send("UPDATE" + levelbounds.serialized_string());
				buffer = "UPDATE" + levelbounds.serialized_string();
				game_current = WAITING_ROOM;
				return;
				break;
			}
			break;

		//multiplayer button; takes the player to the multiplayer interface and starts the TCP server
		case (start_multiplayer_button):
			mouse_held = true;
			multiplayer_network.server_setup();
			game_current = MULTI_CONNECT;
			break;

		//help button; sends the player to the help interface
		case (help_button):
			mouse_held = true;
			game_current = HELP;
			break;

		//exit button; exits the program.
		case (exit_button):
			std::exit(0);
			break;

		//disconnect from the session.
		case (multi_disconnect_button):
			mouse_held = true;
			//close either the server or the client based on what the program was connected to the session as.
			multiplayer_network.close();

			//set variables back to default
			p2.set_bot(true);
			p1.set_location(level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.4);
			game_current = MAIN_MENU;
			break;

		//palette buttons; modifies the player color based on the palette clicked (also unticks all other color palettes)
		case (red_button):
		case (green_button):
		case (blue_button):
		case (yellow_button):
		case (magenta_button):
		case (cyan_button):
			for (int i = red_button; i <= cyan_button; i++) {
				buttons_in_level.untick_button(i);
			}
			buttons_in_level.tick_button(pressed);
			p1.set_color(pressed);
			mouse_held = true;
			break;

		//button for generating walls in the level. (unticks all other wall choices)
		case (few_walls):
		case (medium_walls):
		case (a_lot_walls):
			for (int i = few_walls; i <= a_lot_walls; i++) {
				buttons_in_level.untick_button(i);
			}
			buttons_in_level.tick_button(pressed);
			walls_amount = wall_button_to_wall_amount(pressed);
			mouse_held = true;
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
	string message = multiplayer_network.receive();
	if (message[0] == 'U' || message[0] == 'T' || message[0] == 'F') {
		game_current = IN_GAME_MULTI;
	}
	else if (message[0] == 'P' && buffer == "BCKMAIN") {
		game_current = MULTI_MENU;
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
		p1.change_direction(keydown);
		p2.change_direction(keydown);

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
		bool clear_shot = levelbounds.bot_shot_predictor(p1, p2);
		pair<pair<bool, double>, pair<double, double>> p1_shot_params = p1.shoot_prompt(mouse_down, clear_shot);
		pair<pair<bool, double>, pair<double, double>> p2_shot_params = p2.shoot_prompt(mouse_down, clear_shot);
		if (p1_shot_params.first.first) {
			shotSound.play();
			shots_on_screen.add_shot(p1_shot_params.second.first, p1_shot_params.second.second, p1_shot_params.first.second);
		}
		if (p2_shot_params.first.first) {
			shotSound.play();
			shots_on_screen.add_shot(p2_shot_params.second.first, p2_shot_params.second.second, p2_shot_params.first.second);
		}

		//move all shots on the screen.
		shots_on_screen.move();

		//after moving the shots, bounce all shots which have hit a wall.
		levelbounds.bounce_shots(shots_on_screen);

		//determine whether any of the shots hit the player.
		shots_on_screen.hit_player(p1);
		shots_on_screen.hit_player(p2);

		//determine if either player is dead.
		if (!p1.isalive() && !p2.isalive()) {
			dieSound.play();
			game_result = TIE;
			game_current = ROUND_OVER;
		}
		else if (!p1.isalive()) {
			dieSound.play();
			game_result = P2_WIN;
			game_current = ROUND_OVER;
		}
		else if (!p2.isalive()) {
			dieSound.play();
			game_result = P1_WIN;
			game_current = ROUND_OVER;
		}
	}

	//updates for multiplayer game for client.
	//no calculations are done on client side; the job of the client is to send the input at every update to the host where the calculations
	//are handled and the level graphics are sent back to be parsed here.
	else if (multiplayer_network.get_status() == CLIENT) {
		//if the connection is terminated reset the game and go back to the main menu
		if (!multiplayer_network.is_connected()) {
			multiplayer_network.close();

			levelbounds.clear_level();
			shots_on_screen.clear_shots();

			p2.set_bot(true);
			p2.reset_player(level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.4);
			p1.reset_player(level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.4);
			game_current = MAIN_MENU;
			return;
		}
		string to_send = serialize_input(keydown, mouse_down, ofGetMouseX(), ofGetMouseY());
		multiplayer_network.send(to_send);

		//reading buffer until there are no messages left; causes data loss but drastically reduces lag
		string message = multiplayer_network.receive();
		//if there is a message update the shots on screen and the players accordingly.
		if (message.size() > 0) {
			vector<string> message_array = split(message, "G");
			if (message_array[0] == "UPDATE") {
				shots_on_screen.deserialize_update_message(message_array[1]);
				p2.deserialize_update_game_message(message_array[2]);
				p1.deserialize_update_game_message(message_array[3]);
				//denotes whether a shot was fired; if yes, play the shot sound.
				if (message_array[4] == "S") {
					shotSound.play();
				}
			}
		}

		//determine whether the game is over.
		if (!p1.isalive() && !p2.isalive()) {
			dieSound.play();
			game_result = TIE;
			game_current = MULTI_ROUND_OVER;
		}
		else if (!p1.isalive()) {
			dieSound.play();
			game_result = P2_WIN;
			game_current = MULTI_ROUND_OVER;
		}
		else if (!p2.isalive()) {
			dieSound.play();
			game_result = P1_WIN;
			game_current = MULTI_ROUND_OVER;
		}
	}

	//updates for multiplayer game for client.
	//all calculations are done on the host server; receives input from the client and handles player movement, sending the game status back to the client
	//at every update.
	else if (multiplayer_network.get_status() == HOST) {
		//if the connection is terminated reset the game and go back to the main menu
		if (!multiplayer_network.is_connected()) {
			multiplayer_network.close();

			levelbounds.clear_level();
			shots_on_screen.clear_shots();

			p2.set_bot(true);
			p2.reset_player(level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.4);
			p1.reset_player(level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.4);
			game_current = MAIN_MENU;
			return;
		}

		bool shot_fired = false;
		//reduces the firing cooldown of the players.
		p1.cooldown_reduce();
		p2.cooldown_reduce();

		//updates the parameters of p1
		p1.change_direction(keydown);
		p1.update_player_facing(ofGetMouseX(), ofGetMouseY(), p2);
		p1.move();
		levelbounds.collision_resolver(p1);

		//reading buffer until there are no messages left; causes data loss but drastically reduces lag
		string message = multiplayer_network.receive();

		//if there is a valid message, update the parameters of p2.
		if (message.size() > 0 && (message[0] == 'T' || message[0] == 'F')) {
			pair<pair<vector<bool>, bool>, pair<double, double>> message_pairs = deserialize_input(message);
			p2.change_direction_p2(message_pairs.first.first);
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
		//otherwise just move them according to the last received input.
		else {
			p2.move();
			levelbounds.collision_resolver(p2);
		}

		pair<pair<bool, double>, pair<double, double>> p1_shot_params = p1.shoot_prompt(mouse_down, false);
		if (p1_shot_params.first.first) {
			shot_fired = true;
			shotSound.play();
			shots_on_screen.add_shot(p1_shot_params.second.first, p1_shot_params.second.second, p1_shot_params.first.second);
		}

		//move all shots on the screen.
		shots_on_screen.move();

		//after moving the shots, bounce all shots which have hit a wall.
		levelbounds.bounce_shots(shots_on_screen);

		//determine whether any of the shots hit the player.
		shots_on_screen.hit_player(p1);
		shots_on_screen.hit_player(p2);

		//send updated game to client
		string to_send = ("UPDATE" + shots_on_screen.serialized_string() + p1.serialized_game_string() + p2.serialized_game_string() + "G");
		if (shot_fired) {
			to_send += "S";
		}
		else {
			to_send += "N";
		}
		multiplayer_network.send(to_send);

		//determine whether the game is over.
		if (!p1.isalive() && !p2.isalive()) {
			dieSound.play();
			game_result = TIE;
			game_current = MULTI_ROUND_OVER;
		}
		else if (!p1.isalive()) {
			dieSound.play();
			game_result = P2_WIN;
			game_current = MULTI_ROUND_OVER;
		}
		else if (!p2.isalive()) {
			dieSound.play();
			game_result = P1_WIN;
			game_current = MULTI_ROUND_OVER;
		}
	}
	
}

void ofApp::update_pause() {
	//detect pressed buttons
	if (mouse_down && !mouse_held) {
		switch (buttons_in_level.on_button(ofGetMouseX(), ofGetMouseY(), game_current)) {

		//go back to main menu
		case (paused_back_to_menu):
			mouse_held = true;

			//clear the level; remove all non-boundary walls and shots
			levelbounds.clear_level();
			shots_on_screen.clear_shots();

			//reset both players and set p1 back to the display area
			p1.reset_player(level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.4);
			p2.reset_player((level_width_multiplier - 2.5) * wall_width, wall_width * 2.5);

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
		if (message == "REMATCH") {
			shots_on_screen.clear_shots();
			p1.reset_player(wall_width * 2.5, (level_height_multiplier - 2.5) * wall_width);
			p2.reset_player((level_width_multiplier - 2.5) * wall_width, wall_width * 2.5);
			for (int i = 0; i < 255; i++) {
				keydown[i] = false;
			}
			game_current = IN_GAME_MULTI;
			return;
		}
		//other user pressed back to main
		else if (message == "BCKMAIN") {
			levelbounds.clear_level();
			shots_on_screen.clear_shots();
			switch (multiplayer_network.get_status()) {
			case (HOST):
				p1.reset_player(level_width_multiplier * wall_width * 0.45, level_height_multiplier * wall_width * 0.4);
				p2.reset_player(level_width_multiplier * wall_width * 0.55, level_height_multiplier * wall_width * 0.4);
				break;
			case (CLIENT):
				p2.reset_player(level_width_multiplier * wall_width * 0.45, level_height_multiplier * wall_width * 0.4);
				p1.reset_player(level_width_multiplier * wall_width * 0.55, level_height_multiplier * wall_width * 0.4);
				break;
			}
			for (int i = 0; i < 255; i++) {
				keydown[i] = false;
			}
			game_current = MULTI_MENU;
			return;
		}
	}

	//detect pressed buttons
	if (mouse_down && !mouse_held) {
		switch (buttons_in_level.on_button(ofGetMouseX(), ofGetMouseY(), game_current)) {

		//rematch button; does not regenerate walls.
		case (rematch_button):
			mouse_held = true;

			//clear all shots in the level.
			shots_on_screen.clear_shots();

			//reset both players
			p1.reset_player(wall_width * 2.5, (level_height_multiplier - 2.5) * wall_width);
			p2.reset_player((level_width_multiplier - 2.5) * wall_width, wall_width * 2.5);

			//clears keys; this prevents weird issues with holding down keys at the time of the rematch
			for (int i = 0; i < 255; i++) {
				keydown[i] = false;
			}
			switch (multiplayer_network.get_status()) {

			//case for singleplayer game
			case (NONE):
				game_current = IN_GAME_SINGLE;
				break;

			//case for multiplayer
			default:
				multiplayer_network.send("REMATCH");
				buffer = "REMATCH";
				game_current = WAITING_ROOM;
				break;
			}
		break;
		//return to main menu
		case (round_over_back_to_menu):
			switch (multiplayer_network.get_status()) {

			//case for singleplayer game
			case (NONE):
				mouse_held = true;

				//clear all non-boundary walls and shots in the level.
				levelbounds.clear_level();
				shots_on_screen.clear_shots();

				//reset both players and set p1 back to the display area
				p1.reset_player(level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.4);
				p2.reset_player((level_width_multiplier - 2.5) * wall_width, wall_width * 2.5);

				//clears keys; this prevents weird issues with holding down keys at the time of going back to main menu
				for (int i = 0; i < 255; i++) {
					keydown[i] = false;
				}
				game_current = MAIN_MENU;
				break;

			//case for host server; only difference is a message is sent to client signifying the button was pressed
			case (HOST):
				mouse_held = true;

				//clear all non-boundary walls and shots in the level.
				levelbounds.clear_level();
				shots_on_screen.clear_shots();

				//reset both players and set p1 back to the display area
				p1.reset_player(level_width_multiplier * wall_width * 0.45, level_height_multiplier * wall_width * 0.4);
				p2.reset_player(level_width_multiplier * wall_width * 0.55, level_height_multiplier * wall_width * 0.4);

				//clears keys; this prevents weird issues with holding down keys at the time of going back to main menu
				for (int i = 0; i < 255; i++) {
					keydown[i] = false;
				}
				multiplayer_network.send("BCKMAIN");
				buffer = "BCKMAIN";
				game_current = WAITING_ROOM;
				break;

			//case for client; only difference is a message is sent to server signifying the button was pressed (and p1 p2 positions swapped).
			case (CLIENT):
				mouse_held = true;

				//clear all non-boundary walls and shots in the level.
				levelbounds.clear_level();
				shots_on_screen.clear_shots();

				//reset both players and set p1 back to the display area
				p2.reset_player(level_width_multiplier * wall_width * 0.45, level_height_multiplier * wall_width * 0.4);
				p1.reset_player(level_width_multiplier * wall_width * 0.55, level_height_multiplier * wall_width * 0.4);

				//clears keys; this prevents weird issues with holding down keys at the time of going back to main menu
				for (int i = 0; i < 255; i++) {
					keydown[i] = false;
				}
				multiplayer_network.send("BCKMAIN");
				buffer = "BCKMAIN";
				game_current = WAITING_ROOM;
				break;
			}
		}
	}
}

void ofApp::update_help() {
	//detect pressed buttons
	if (mouse_down && !mouse_held) {
		switch (buttons_in_level.on_button(ofGetMouseX(), ofGetMouseY(), game_current)) {

		//go back to main menu
		case (help_back_to_menu):
			mouse_held = true;
			game_current = MAIN_MENU;
			break;
		}
	}
}

void ofApp::update_multi_connect() {
	//enter ip address
	pair<bool, string> temp = enter_ip(entered, ip_address, keydown);
	entered = temp.first;
	ip_address = temp.second;

	if (multiplayer_network.is_connected()) {
		//set players to appropriate locations in the level
		if (multiplayer_network.get_status() == HOST) {
			p1.set_location(level_width_multiplier * wall_width * 0.45, level_height_multiplier * wall_width * 0.4);
			p2.set_location(level_width_multiplier * wall_width * 0.55, level_height_multiplier * wall_width * 0.4);
		}
		else {
			p1.set_location(level_width_multiplier * wall_width * 0.55, level_height_multiplier * wall_width * 0.4);
			p2.set_location(level_width_multiplier * wall_width * 0.45, level_height_multiplier * wall_width * 0.4);
		}
		//set p2 to not be a bot since p2 is now player-controlled
		p2.set_bot(false);

		//send the details of the player to the other user
		multiplayer_network.send(p1.serialized_model_string());

		//set enums accordingly
		game_current = MULTI_MENU;
	}

	//detect pressed buttons
	if (mouse_down && !mouse_held) {
		switch (buttons_in_level.on_button(ofGetMouseX(), ofGetMouseY(), game_current)) {

		//connect to a server at the specified ip address.
		case (multi_connect_button):
			mouse_held = true;
			multiplayer_network.client_setup(ip_address);
			break;

		//go back to main menu
		case (multi_connect_back_to_menu):
			mouse_held = true;
			multiplayer_network.close();
			game_current = MAIN_MENU;
			break;
		}
	}
}

void ofApp::draw_menu() {
	//draw player name
	text_in_level.draw_dynamic_text(player_name, level_width_multiplier * wall_width * 0.1, 
		level_height_multiplier * wall_width * 0.4, false, 2);

	//draw the demo player
	p1.draw_player();

	//if the player is connect also draw the opponent
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
		ofSetColor(255, 255, 255, 128);
		ofDrawRectangle(level_width_multiplier * wall_width * 0.25, level_height_multiplier * wall_width * 0.25, level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.5);
		ofSetColor(0, 0, 0);
		break;

	//game is over
	case (MULTI_ROUND_OVER):
	case (ROUND_OVER):
		//draw an overlaying rectangle to prevent black text from mixing in with the walls
		ofSetColor(255, 255, 255, 128);
		ofDrawRectangle(level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.9, level_width_multiplier * wall_width * 0.8, level_height_multiplier * wall_width * 0.08);
		ofSetColor(0, 0, 0);

		//draw the match outcome
		string game_outcome_message;
		switch (game_result) {
		case (TIE):
			game_outcome_message = "It's a tie.";
			break;
		case (P1_WIN):
			game_outcome_message = p1.get_name() + " wins!";
			break;
		case (P2_WIN):
			game_outcome_message = p2.get_name() + " wins!";
			break;
		}
		text_in_level.draw_dynamic_text(game_outcome_message, level_width_multiplier * wall_width * 0.12,
			level_height_multiplier * wall_width * 0.95, false, 2);
		break;
	}
		
}

void ofApp::draw_multi_connect() {
	//draw the current entered ip address
	text_in_level.draw_dynamic_text("IP address:" + ip_address, level_width_multiplier * wall_width * 0.1,
		level_height_multiplier * wall_width * 0.55, false, 2);
}