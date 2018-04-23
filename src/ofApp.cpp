#include "ofApp.h"
/*
array of booleans used to store which keys are held down.
*/
bool keydown[255];

/*
boolean on whether the left mouse button is held down.
*/
bool mouse_down;

/*
boolean on whether the mouse is held; used to prevent crashing interfaces
*/
bool mouse_held;

/*
wall object containing the walls in the level.
*/
Wall levelbounds;

/*
shotInLevel object containing the shots on screen.
*/
ShotInLevel shots_on_screen;

/*
instantiate a player at the specified location.
*/
Player p1 = Player(wall_width * 2.5, (level_height_multiplier - 2.5) * wall_width, 0, 0, 255, false, "default");

/*
bot player.
*/
Player p2 = Player((level_width_multiplier - 2.5) * wall_width, wall_width * 2.5, 0, 0, 255, true, "default");

/*
instantiate buttons in game
*/
AllButtons buttons_in_level;

/*
instantiate game to start at main menu
*/
game_state game_current;

/*
store player name.
*/
string player_name;

/*
enum for game outcome.
*/
winner game_result;

/*
boolean for handling player input for player name in main menu.
*/
bool entered = false;

//--------------------------------------------------------------
void ofApp::setup(){
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

	ofSetWindowTitle("2D shooter game");
	
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
	case SINGLE_PARAMS:
		update_single_params();
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
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//call separate draw functions based on current game state
	switch (game_current) {
	case MAIN_MENU:
		draw_menu();
		break;
	case SINGLE_PARAMS:
		draw_single_params();
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
	enter_name();

	//check if any button is pressed
	if (mouse_down) {
		int pressed = buttons_in_level.on_button(ofGetMouseX(), ofGetMouseY(), MAIN_MENU);
		if (!mouse_held) {
			switch (pressed) {
			//single player button; sets the player name to whatever the user entered.
			case (start_singleplayer_button):
				if (player_name == "") {
					p1.set_name("*blank*");
				}
				else {
					p1.set_name(player_name);
				}
				entered = false;
				game_current = SINGLE_PARAMS;
				mouse_held = true;
				break;
			//multiplayer button; to be implemented
			case (start_multiplayer_button):
				mouse_held = true;
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
			//red palette button; modifies the player color
			case (red_button):
				buttons_in_level.tick_button(red_button);
				p1.set_color(255, 0, 0);
				mouse_held = true;
				break;
			//green palette button; modifies the player color
			case (green_button):
				buttons_in_level.tick_button(green_button);
				p1.set_color(0, 255, 0);
				mouse_held = true;
				break;
			//blue palette button; modifies the player color
			case (blue_button):
				buttons_in_level.tick_button(blue_button);
				p1.set_color(0, 0, 255);
				mouse_held = true;
				break;
			//yellow palette button; modifies the player color
			case (yellow_button):
				buttons_in_level.tick_button(yellow_button);
				p1.set_color(255, 255, 0);
				mouse_held = true;
				break;
			//magenta palette button; modifies the player color
			case (magenta_button):
				buttons_in_level.tick_button(magenta_button);
				p1.set_color(255, 0, 255);
				mouse_held = true;
				break;
			//cyan palette button; modifies the player color
			case (cyan_button):
				buttons_in_level.tick_button(cyan_button);
				p1.set_color(0, 255, 255);
				mouse_held = true;
				break;
			}
		}
	}
}

void ofApp::update_single_params() {
	if (mouse_down) {
		int pressed = buttons_in_level.on_button(ofGetMouseX(), ofGetMouseY(), SINGLE_PARAMS);
		if (!mouse_held) {
			switch (pressed) {
			//button to instantiate level with few walls
			case (few_walls):
				//set player locations to default
				p1.set_location(wall_width * 2.5, (level_height_multiplier - 2.5) * wall_width);

				//generate walls
				levelbounds.random_level_generator(8);

				//sets player weapons to cooldown (to prevent accidental firings immediately after game begins)
				p1.fire_shot();
				p2.fire_shot();

				//sets a random name and color for the bot
				p2.randomize_name();
				p2.randomize_color();

				mouse_held = true;
				game_current = IN_GAME_SINGLE;
				break;
			//button to instantiate level with some walls
			case (medium_walls):
				//set player locations to default
				p1.set_location(wall_width * 2.5, (level_height_multiplier - 2.5) * wall_width);

				//generate walls
				levelbounds.random_level_generator(16);

				//sets player weapons to cooldown (to prevent accidental firings immediately after game begins)
				p1.fire_shot();
				p2.fire_shot();

				//sets a random name and color for the bot
				p2.randomize_name();
				p2.randomize_color();
				mouse_held = true;
				game_current = IN_GAME_SINGLE;
				break;
			//button to instantiate level with a lot of walls
			case (a_lot_walls):
				//set player locations to default
				p1.set_location(wall_width * 2.5, (level_height_multiplier - 2.5) * wall_width);

				//generate walls
				levelbounds.random_level_generator(24);

				//sets player weapons to cooldown (to prevent accidental firings immediately after game begins)
				p1.fire_shot();
				p2.fire_shot();

				//sets a random name and color for the bot
				p2.randomize_name();
				p2.randomize_color();
				mouse_held = true;
				game_current = IN_GAME_SINGLE;
				break;
			//button to go back to main menu
			case (params_back_to_menu):
				game_current = MAIN_MENU;
				mouse_held = true;
				break;
			}
		}
	}
}

void ofApp::enter_name() {
	//enter name
	bool something_pressed = false;
	for (int i = character_start; i < character_end; i++) {
		if (keydown[i]) {
			something_pressed = true;
			//only one letter can be entered per update; also disables entering when the name goes over the maximum name length.
			if (player_name.length() < max_name_length && !entered) {
				player_name += i;
			}
		}
	}
	//8 is the backspace button; if it is pressed pop the last letter the player entered.
	if (keydown[8]) {
		something_pressed = true;
		if (player_name.length() > 0 && !entered) {
			player_name.pop_back();
		}
	}
	//boolean variable to prevent multiple letters entered with one key press due to how fast update is called
	if (something_pressed) {
		entered = true;
	}
	else {
		entered = false;
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
		shots_on_screen.add_shot(p1_shot_params.second.first, p1_shot_params.second.second, p1_shot_params.first.second);
	}
	if (p2_shot_params.first.first) {
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
		game_result = TIE;
		game_current = ROUND_OVER;
	}
	else if (!p1.isalive()) {
		game_result = P2_WIN;
		game_current = ROUND_OVER;
	}
	else if (!p2.isalive()) {
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

void ofApp::draw_menu() {
	//draw the demo player
	p1.update_player_facing(ofGetMouseX(), ofGetMouseY(), p2);
	p1.draw_player();
	p1.set_name(player_name);

	//draw the player name
	character_name.drawString("Player name:", level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.35);
	character_name.drawString(player_name, level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.4);

	//draw player color
	character_name.drawString("Player color:", level_width_multiplier * wall_width * 0.75, level_height_multiplier * wall_width * 0.35);

	//draw the title
	game_title_text.drawStringCentered("2D Shooter Game", level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.15);

	//draw buttons in level
	buttons_in_level.draw_button(game_current, button_text);
}

void ofApp::draw_single_params() {
	button_text.drawStringCentered("Please select the amount of walls:", level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.15);

	//draw buttons in level
	buttons_in_level.draw_button(game_current, button_text);
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
	//draw all wall segments
	levelbounds.draw_all_walls();

	//draw the player
	p1.draw_player();
	p2.draw_player();

	//draw the shots
	shots_on_screen.draw_shot();

	//draw paused interface
	ofSetColor(255, 255, 255, 128);
	ofDrawRectangle(level_width_multiplier * wall_width * 0.25, level_height_multiplier * wall_width * 0.25, level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.5);
	ofSetColor(0, 0, 0);
	character_name.drawStringCentered("Game paused", level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.3);
	character_name.drawStringCentered("Press P to unpause", level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.35);

	//draw buttons in level
	buttons_in_level.draw_button(game_current, button_text);
}

void ofApp::draw_round_over() {
	//draw all wall segments
	levelbounds.draw_all_walls();

	//draw the player
	p1.draw_player();
	p2.draw_player();

	//draw the shots
	shots_on_screen.draw_shot();

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
	ofSetColor(0, 0, 0);
	game_title_text.drawStringCentered("Help", level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.15);
	character_name.drawString("Move: WASD keys", level_width_multiplier * wall_width * 0.2, level_height_multiplier * wall_width * 0.35);
	character_name.drawString("Fire: mouse button", level_width_multiplier * wall_width * 0.2, level_height_multiplier * wall_width * 0.45);
	character_name.drawString("Pause: P (single player only)", level_width_multiplier * wall_width * 0.2, level_height_multiplier * wall_width * 0.55);

	//draw buttons in level
	buttons_in_level.draw_button(game_current, button_text);
}
