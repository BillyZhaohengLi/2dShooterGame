#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//instantiate some class variables
	entered = false;
	in_multi = false;
	walls_amount = few_walls_amount;
	connected_to_host = false;
	client_server = NONE;

	//load text for buttons
	button_text.loadFont("verdana.ttf", wall_width);
	button_text.setLineHeight(18.0f);
	button_text.setLetterSpacing(1.037);

	//load text for titles
	game_title_text.loadFont("verdana.ttf", wall_width * 2);
	game_title_text.setLineHeight(18.0f);
	game_title_text.setLetterSpacing(1.037);

	//load text for character name
	character_name.loadFont("verdana.ttf", wall_width * 0.6);
	character_name.setLineHeight(18.0f);
	character_name.setLetterSpacing(1.037);

	//load sounds
	shotSound.load("fire_shot.wav");
	dieSound.load("die.wav");
	
	//set current menu to main menu and set p1 into center location for display
	p1.set_location(level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.4);
	game_current = MAIN_MENU;

	//add buttons in the level
	add_buttons(buttons_in_level);

	//add boundaries to the level (the boundaries are fixed for each game anyways, better done sooner than later)
	levelbounds.add_boundary();
}

//--------------------------------------------------------------
void ofApp::update(){
	//call separate update functions based on current game state
	switch (game_current) {
	case MAIN_MENU:
		update_menu();
		break;
	case MULTI_MENU:
		update_multi_menu();
		break;
	case IN_GAME_SINGLE:
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
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//call separate draw functions based on current game state
	switch (game_current) {
	case MAIN_MENU:
		draw_menu();
		break;
	case MULTI_MENU:
		draw_multi_menu();
		break;
	case IN_GAME_SINGLE:
		draw_singleplayer_game();
		break;
	case PAUSE:
		draw_pause();
		break;
	case ROUND_OVER:
		draw_round_over();
		break;
	case HELP:
		draw_help();
		break;
	case MULTI_CONNECT:
		draw_multi_connect();
		break;
	}
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
	//helper function to enter name
	pair<bool, string> temp = enter_name(entered, player_name, keydown);
	entered = temp.first;
	player_name = temp.second;

	//check if any button is pressed
	if (mouse_down) {
		int pressed = buttons_in_level.on_button(ofGetMouseX(), ofGetMouseY(), MAIN_MENU);
		if (!mouse_held) {
			switch (pressed) {

			//single player button; sets the player name to whatever the user entered.
			case (start_singleplayer_button):
				p1.set_name(player_name);
				entered = false;
				game_current = IN_GAME_SINGLE;

				p1.set_location(wall_width * 2.5, (level_height_multiplier - 2.5) * wall_width);

				//generate walls
				levelbounds.random_level_generator(walls_amount);

				//sets player weapons to cooldown (to prevent accidental firings immediately after game begins)
				p1.fire_shot();
				p2.fire_shot();

				//sets a random name and color for the bot
				p2.randomize_name();
				p2.randomize_color();

				mouse_held = true;
				break;

			//multiplayer button; takes the player to the multiplayer interface and starts the TCP server
			case (start_multiplayer_button):
				mouse_held = true;
				multiplayer_server.setup(multiplayer_port);
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

			//red palette button; modifies the player color (also unticks all other color palettes)
			case (red_button):
				for (int i = red_button; i <= cyan_button; i++) {
					buttons_in_level.untick_button(i);
				}
				buttons_in_level.tick_button(red_button);
				p1.set_color(255, 0, 0);
				mouse_held = true;
				break;

			//green palette button; modifies the player color (also unticks all other color palettes)
			case (green_button):
				for (int i = red_button; i <= cyan_button; i++) {
					buttons_in_level.untick_button(i);
				}
				buttons_in_level.tick_button(green_button);
				p1.set_color(0, 255, 0);
				mouse_held = true;
				break;

			//blue palette button; modifies the player color (also unticks all other color palettes)
			case (blue_button):
				for (int i = red_button; i <= cyan_button; i++) {
					buttons_in_level.untick_button(i);
				}
				buttons_in_level.tick_button(blue_button);
				p1.set_color(0, 0, 255);
				mouse_held = true;
				break;

			//yellow palette button; modifies the player color (also unticks all other color palettes)
			case (yellow_button):
				for (int i = red_button; i <= cyan_button; i++) {
					buttons_in_level.untick_button(i);
				}
				buttons_in_level.tick_button(yellow_button);
				p1.set_color(255, 255, 0);
				mouse_held = true;
				break;

			//magenta palette button; modifies the player color (also unticks all other color palettes)
			case (magenta_button):
				for (int i = red_button; i <= cyan_button; i++) {
					buttons_in_level.untick_button(i);
				}
				buttons_in_level.tick_button(magenta_button);
				p1.set_color(255, 0, 255);
				mouse_held = true;
				break;

			//cyan palette button; modifies the player color (also unticks all other color palettes)
			case (cyan_button):
				for (int i = red_button; i <= cyan_button; i++) {
					buttons_in_level.untick_button(i);
				}
				buttons_in_level.tick_button(cyan_button);
				p1.set_color(0, 255, 255);
				mouse_held = true;
				break;

			//button for generating few walls in the level. (also unticks all other wall choices)
			case (few_walls):
				for (int i = few_walls; i <= a_lot_walls; i++) {
					buttons_in_level.untick_button(i);
				}
				buttons_in_level.tick_button(few_walls);
				walls_amount = few_walls_amount;
				mouse_held = true;
				break;

			//button for generating some walls in the level. (also unticks all other wall choices)
			case (medium_walls):
				for (int i = few_walls; i <= a_lot_walls; i++) {
					buttons_in_level.untick_button(i);
				}
				buttons_in_level.tick_button(medium_walls);
				walls_amount = medium_walls_amount;
				mouse_held = true;
				break;

			//button for generating a lot of walls in the level. (also unticks all other wall choices)
			case (a_lot_walls):
				for (int i = few_walls; i <= a_lot_walls; i++) {
					buttons_in_level.untick_button(i);
				}
				buttons_in_level.tick_button(a_lot_walls);
				walls_amount = a_lot_walls_amount;
				mouse_held = true;
				break;
			}
		}
	}
}

void ofApp::update_singleplayer_game() {
	//reduces the firing cooldown of the players.
	p1.cooldown_reduce();
	p2.cooldown_reduce();

	//determines the players' new direction based on the keys held down at this particular time.
	p1.change_direction(keydown);
	p2.change_direction(keydown);

	//after changing directions, move the players.
	p1.move();
	p2.move();

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

	//if the player collides with wall segment(s), resolve the collision(s).
	levelbounds.collision_resolver(p1);
	levelbounds.collision_resolver(p2);

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

void ofApp::update_pause() {
	if (mouse_down) {
		int pressed = buttons_in_level.on_button(ofGetMouseX(), ofGetMouseY(), PAUSE);
		if (!mouse_held) {
			switch (pressed) {

			//go back to main menu
			case (paused_back_to_menu):
				mouse_held = true;

				//clear the level; remove all non-boundary walls and shots
				levelbounds.clear_level();
				shots_on_screen.clear_shots();

				//set player locations back to default (set p1 back to display area)
				p1.set_location(level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.4);
				p2.set_location((level_width_multiplier - 2.5) * wall_width, wall_width * 2.5);

				//set both players to alive
				p1.revive_player();
				p2.revive_player();

				game_current = MAIN_MENU;
				break;
			}
		}
	}
}

void ofApp::update_round_over() {
	if (mouse_down) {
		int pressed = buttons_in_level.on_button(ofGetMouseX(), ofGetMouseY(), ROUND_OVER);
		if (!mouse_held) {
			switch (pressed) {

			//rematch button; does not regenerate walls.
			case (rematch_button):
				mouse_held = true;

				//clear all shots in the level.
				shots_on_screen.clear_shots();

				//sets players back to default positions
				p1.set_location(wall_width * 2.5, (level_height_multiplier - 2.5) * wall_width);
				p2.set_location((level_width_multiplier - 2.5) * wall_width, wall_width * 2.5);

				//set both players to alive
				p1.revive_player();
				p2.revive_player();

				//put both player weapons on cooldown
				p1.fire_shot();
				p2.fire_shot();

				//clears keys; this prevents weird issues with holding down keys at the time of the rematch
				for (int i = 0; i < 255; i++) {
					keydown[i] = false;
				}

				game_current = IN_GAME_SINGLE;
				break;

			//return to main menu
			case (round_over_back_to_menu):
				mouse_held = true;

				//clear all non-boundary walls and shots in the level.
				levelbounds.clear_level();
				shots_on_screen.clear_shots();

				//set player locations back to default (set p1 back to display area)
				p1.set_location(level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.4);
				p2.set_location((level_width_multiplier - 2.5) * wall_width, wall_width * 2.5);

				//set both players to alive
				p1.revive_player();
				p2.revive_player();

				//clears keys; this prevents weird issues with holding down keys at the time of going back to main menu
				for (int i = 0; i < 255; i++) {
					keydown[i] = false;
				}
				game_current = MAIN_MENU;
				break;
			}
		}
	}
}

void ofApp::update_help() {
	if (mouse_down) {
		int pressed = buttons_in_level.on_button(ofGetMouseX(), ofGetMouseY(), HELP);
		if (!mouse_held) {
			switch (pressed) {

			//go back to main menu
			case (help_back_to_menu):
				mouse_held = true;
				game_current = MAIN_MENU;
				break;
			}
		}
	}
}

void ofApp::update_multi_connect() {
	//enter ip address
	pair<bool, string> temp = enter_ip(entered, ip_address, keydown);
	entered = temp.first;
	ip_address = temp.second;

	if (multiplayer_server.getNumClients() > 0) {
		//set players to appropriate locations in the level
		p1.set_location(level_width_multiplier * wall_width * 0.45, level_height_multiplier * wall_width * 0.4);
		p2.set_location(level_width_multiplier * wall_width * 0.55, level_height_multiplier * wall_width * 0.4);

		//set p2 to not be a bot since p2 is now player-controlled
		p2.set_bot(false);

		//send the details of the player to the other user
		multiplayer_server.send(0, p1.serialized_string());

		//set enums accordingly
		client_server = HOST;
		game_current = MULTI_MENU;
	}
	if (connected_to_host) {
		//set players to appropriate locations in the level
		p1.set_location(level_width_multiplier * wall_width * 0.55, level_height_multiplier * wall_width * 0.4);
		p2.set_location(level_width_multiplier * wall_width * 0.45, level_height_multiplier * wall_width * 0.4);

		//set p2 to not be a bot since p2 is now player-controlled
		p2.set_bot(false);

		//send the details of the player to the other user
		multiplayer_client.send(p1.serialized_string());

		//set enums accordingly
		client_server = CLIENT;
		game_current = MULTI_MENU;
	}

	if (mouse_down) {
		int pressed = buttons_in_level.on_button(ofGetMouseX(), ofGetMouseY(), MULTI_CONNECT);
		if (!mouse_held) {
			switch (pressed) {

			//connect to a server at the specified ip address.
			case (multi_connect_button):
				mouse_held = true;
				multiplayer_server.close();
				connected_to_host = multiplayer_client.setup(ip_address, 11999);
				break;

			//go back to main menu
			case (multi_connect_back_to_menu):
				mouse_held = true;
				multiplayer_server.close();
				game_current = MAIN_MENU;
				break;
			}
		}
	}
}

void ofApp::update_multi_menu() {
	string message;

	//receive message; also handle the case if the connection is terminated
	if (client_server == HOST) {
		//if the connection is terminated set variables accordingly, close the servere and go back to main menu
		if (multiplayer_server.getNumClients() == 0) {
			multiplayer_server.close();
			p2.set_bot(true);
			p1.set_location(level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.4);
			connected_to_host = false;
			client_server = NONE;
			game_current = MAIN_MENU;
		}
		//otherwise recieve a message from the client
		message = multiplayer_server.receive(0);
	}
	else if (client_server == CLIENT) {
		//if the connection is terminated set variables accordingly, close the servere and go back to main menu
		if (!multiplayer_client.isConnected()) {
			multiplayer_client.close();
			p2.set_bot(true);
			p1.set_location(level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.4);
			connected_to_host = false;
			client_server = NONE;
			game_current = MAIN_MENU;
		}
		//otherwise recieve a message from the host
		message = multiplayer_client.receive();
	}

	//handle message from partner
	if (message.length() > 0) {
		//if the message begins with "PLAYER" then it is a message to update the opponent's player model;
		if (message.substr(0, 6) == "PLAYER") {
			p2.deserialize_update_message(message);
		}
	}

	//helper function to enter name
	pair<bool, string> temp = enter_name(entered, player_name, keydown);
	entered = temp.first;
	player_name = temp.second;

	//check if any button is pressed
	if (mouse_down) {
		int pressed = buttons_in_level.on_button(ofGetMouseX(), ofGetMouseY(), MULTI_MENU);
		if (!mouse_held) {
			switch (pressed) {

			//start the multiplayer game; to be implemented
			case (multi_start_game_button):
				mouse_held = true;
				break;

			//disconnect from the session.
			case (multi_disconnect_button):
				mouse_held = true;
				//close either the server or the client based on what the program was connected to the session as.
				if (client_server == HOST) {
					multiplayer_server.close();
				}
				else if (client_server == CLIENT) {
					multiplayer_client.close();
				}

				//set variables back to default
				p2.set_bot(true);
				p1.set_location(level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.4);
				connected_to_host = false;
				client_server = NONE;
				game_current = MAIN_MENU;
				break;

			//red palette button; modifies the player color
			case (red_button_m):
				for (int i = red_button_m; i <= cyan_button_m; i++) {
					buttons_in_level.untick_button(i);
				}
				buttons_in_level.tick_button(red_button_m);
				p1.set_color(255, 0, 0);
				mouse_held = true;
				break;

			//green palette button; modifies the player color
			case (green_button_m):
				for (int i = red_button_m; i <= cyan_button_m; i++) {
					buttons_in_level.untick_button(i);
				}
				buttons_in_level.tick_button(green_button_m);
				p1.set_color(0, 255, 0);
				mouse_held = true;
				break;

			//blue palette button; modifies the player color
			case (blue_button_m):
				for (int i = red_button_m; i <= cyan_button_m; i++) {
					buttons_in_level.untick_button(i);
				}
				buttons_in_level.tick_button(blue_button_m);
				p1.set_color(0, 0, 255);
				mouse_held = true;
				break;

			//yellow palette button; modifies the player color
			case (yellow_button_m):
				for (int i = red_button_m; i <= cyan_button_m; i++) {
					buttons_in_level.untick_button(i);
				}
				buttons_in_level.tick_button(yellow_button_m);
				p1.set_color(255, 255, 0);
				mouse_held = true;
				break;

			//magenta palette button; modifies the player color
			case (magenta_button_m):
				for (int i = red_button_m; i <= cyan_button_m; i++) {
					buttons_in_level.untick_button(i);
				}
				buttons_in_level.tick_button(magenta_button_m);
				p1.set_color(255, 0, 255);
				mouse_held = true;
				break;

			//cyan palette button; modifies the player color
			case (cyan_button_m):
				for (int i = red_button_m; i <= cyan_button_m; i++) {
					buttons_in_level.untick_button(i);
				}
				buttons_in_level.tick_button(cyan_button_m);
				p1.set_color(0, 255, 255);
				mouse_held = true;
				break;

			//button for generating few walls in the level.
			case (few_walls_m):
				for (int i = few_walls_m; i <= a_lot_walls_m; i++) {
					buttons_in_level.untick_button(i);
				}
				buttons_in_level.tick_button(few_walls_m);
				walls_amount = few_walls_amount;
				mouse_held = true;
				break;

			//button for generating some walls in the level.
			case (medium_walls_m):
				for (int i = few_walls_m; i <= a_lot_walls_m; i++) {
					buttons_in_level.untick_button(i);
				}
				buttons_in_level.tick_button(medium_walls_m);
				walls_amount = medium_walls_amount;
				mouse_held = true;
				break;

			//button for generating a lot of walls in the level.
			case (a_lot_walls_m):
				for (int i = few_walls_m; i <= a_lot_walls_m; i++) {
					buttons_in_level.untick_button(i);
				}
				buttons_in_level.tick_button(a_lot_walls_m);
				walls_amount = a_lot_walls_amount;
				mouse_held = true;
				break;
			}
		}
	}

	//send the data of the player to the other user.
	if (client_server == HOST) {
		multiplayer_server.send(0, p1.serialized_string());
	}
	else if (client_server == CLIENT) {
		multiplayer_client.send(p1.serialized_string());
	}
}

void ofApp::draw_menu() {
	ofSetColor(0, 0, 0);

	//draw player name
	character_name.drawString("Player name:", level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.35);
	character_name.drawString(player_name, level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.4);

	//draw other text
	character_name.drawString("Player color:", level_width_multiplier * wall_width * 0.75, level_height_multiplier * wall_width * 0.35);
	character_name.drawString("Wall settings:", level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.5);
	character_name.drawString("Few", level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.55);
	character_name.drawString("Some", level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.60);
	character_name.drawString("A lot", level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.65);

	//draw the title
	game_title_text.drawStringCentered("2D Shooter Game", level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.15);

	//draw buttons in level
	buttons_in_level.draw_button(game_current, button_text);

	//draw the demo player
	p1.update_player_facing(ofGetMouseX(), ofGetMouseY(), p2);
	p1.draw_player();
	p1.set_name(player_name);
}

void ofApp::draw_singleplayer_game() {
	//draw all wall segments
	levelbounds.draw_all_walls();

	//draw the player
	p1.update_player_facing(ofGetMouseX(), ofGetMouseY(), p2);
	p2.update_player_facing(ofGetMouseX(), ofGetMouseY(), p1);
	p1.draw_player();
	p2.draw_player();

	//draw the shots
	shots_on_screen.draw_shot();
}

void ofApp::draw_pause() {
	ofSetColor(0, 0, 0);
	//draw all wall segments
	levelbounds.draw_all_walls();

	//draw the player
	p1.draw_player();
	p2.draw_player();

	//draw the shots
	shots_on_screen.draw_shot();

	//draw paused interface
	//draw an overlaying rectangle to prevent black text from mixing in with the walls
	ofSetColor(255, 255, 255, 128);
	ofDrawRectangle(level_width_multiplier * wall_width * 0.25, level_height_multiplier * wall_width * 0.25, level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.5);
	ofSetColor(0, 0, 0);
	character_name.drawStringCentered("Game paused", level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.3);
	character_name.drawStringCentered("Press P to unpause", level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.35);

	//draw buttons in level
	buttons_in_level.draw_button(game_current, button_text);
}

void ofApp::draw_round_over() {
	ofSetColor(0, 0, 0);
	//draw all wall segments
	levelbounds.draw_all_walls();

	//draw the player
	p1.draw_player();
	p2.draw_player();

	//draw the shots
	shots_on_screen.draw_shot();

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
	character_name.drawString(game_outcome_message, level_width_multiplier * wall_width * 0.12, level_height_multiplier * wall_width * 0.95);

	//draw buttons in level
	buttons_in_level.draw_button(game_current, character_name);
}

void ofApp::draw_help() {
	//draw help text
	ofSetColor(0, 0, 0);
	game_title_text.drawStringCentered("Help", level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.15);
	character_name.drawString("Move: WASD keys", level_width_multiplier * wall_width * 0.2, level_height_multiplier * wall_width * 0.35);
	character_name.drawString("Fire: mouse button", level_width_multiplier * wall_width * 0.2, level_height_multiplier * wall_width * 0.45);
	character_name.drawString("Pause: P (single player only)", level_width_multiplier * wall_width * 0.2, level_height_multiplier * wall_width * 0.55);

	//draw buttons in level
	buttons_in_level.draw_button(game_current, button_text);
}

void ofApp::draw_multi_connect() {
	//draw multiplayer connect text
	ofSetColor(0, 0, 0);
	game_title_text.drawStringCentered("Multiplayer connect", level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.15);
	character_name.drawString("Enter an IP address to LAN connect to or wait for a connection:", level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.35);
	character_name.drawString("IP address:" + ip_address, level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.55);

	//draw buttons in level
	buttons_in_level.draw_button(game_current, button_text);
}

void ofApp::draw_multi_menu() {
	ofSetColor(0, 0, 0);

	//draw the player name
	character_name.drawString("Player name:", level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.35);
	character_name.drawString(player_name, level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.4);

	//draw other text
	character_name.drawString("Player color:", level_width_multiplier * wall_width * 0.75, level_height_multiplier * wall_width * 0.35);
	character_name.drawString("Wall settings:", level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.5);
	character_name.drawString("Few", level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.55);
	character_name.drawString("Some", level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.60);
	character_name.drawString("A lot", level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.65);

	//draw the title
	game_title_text.drawStringCentered("2D Shooter Game", level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.15);

	//draw buttons in level
	buttons_in_level.draw_button(game_current, button_text);

	//draw the demo player
	p1.update_player_facing(ofGetMouseX(), ofGetMouseY(), p2);
	p1.draw_player();
	p1.set_name(player_name);

	//draw the opponent's player
	p2.draw_player();
}
