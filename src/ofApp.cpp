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
Player p1 = Player(wall_width * 2.5, (level_height_multiplier - 2.5) * wall_width, 0, 0, 255, "default");

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
boolean for handling player input for player name in main menu.
*/
bool entered = false;

//--------------------------------------------------------------
void ofApp::setup(){
	//load text for buttons
	button_text.loadFont("verdana.ttf", wall_width);
	button_text.setLineHeight(18.0f);
	button_text.setLetterSpacing(1.037);

	game_title_text.loadFont("verdana.ttf", wall_width * 2);
	game_title_text.setLineHeight(18.0f);
	game_title_text.setLetterSpacing(1.037);

	character_name.loadFont("verdana.ttf", wall_width * 0.6);
	character_name.setLineHeight(18.0f);
	character_name.setLetterSpacing(1.037);

	ofSetWindowTitle("2D shooter game");
	p1.set_location(level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.4);
	game_current = MAIN_MENU;

	add_buttons(buttons_in_level);

	levelbounds.add_boundary();
}

//--------------------------------------------------------------
void ofApp::update(){
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
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
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
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key >= 0 && key <= 255) {
		//sets the relevant cell in the keydown array to true
		if (game_current == IN_GAME_SINGLE) {
			keydown[toupper(key)] = true;
			if (toupper(key) == 'P') {
				game_current = PAUSE;
			}
		}
		else if (game_current == PAUSE) {
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
	enter_name();

	//check if any button is pressed
	if (mouse_down) {
		int pressed = buttons_in_level.on_button(ofGetMouseX(), ofGetMouseY(), MAIN_MENU);
		if (!mouse_held) {
			switch (pressed) {
			case (start_singleplayer_button):
				p1.set_name(player_name);
				entered = false;
				game_current = SINGLE_PARAMS;
				mouse_held = true;
				break;
			case (start_multiplayer_button):
				mouse_held = true;
				break;
			case (exit_button):
				std::exit(0);
				break;
			case (red_button):
				buttons_in_level.tick_button(red_button);
				p1.set_color(255, 0, 0);
				mouse_held = true;
				break;
			case (green_button):
				buttons_in_level.tick_button(green_button);
				p1.set_color(0, 255, 0);
				mouse_held = true;
				break;
			case (blue_button):
				buttons_in_level.tick_button(blue_button);
				p1.set_color(0, 0, 255);
				mouse_held = true;
				break;
			case (yellow_button):
				buttons_in_level.tick_button(yellow_button);
				p1.set_color(255, 255, 0);
				mouse_held = true;
				break;
			case (magenta_button):
				buttons_in_level.tick_button(magenta_button);
				p1.set_color(255, 0, 255);
				mouse_held = true;
				break;
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
			case (few_walls):
				p1.set_location(wall_width * 2.5, (level_height_multiplier - 2.5) * wall_width);
				levelbounds.random_level_generator(8);
				mouse_held = true;
				game_current = IN_GAME_SINGLE;
				break;
			case (medium_walls):
				p1.set_location(wall_width * 2.5, (level_height_multiplier - 2.5) * wall_width);
				levelbounds.random_level_generator(16);
				mouse_held = true;
				game_current = IN_GAME_SINGLE;
				break;
			case (a_lot_walls):
				p1.set_location(wall_width * 2.5, (level_height_multiplier - 2.5) * wall_width);
				levelbounds.random_level_generator(24);
				mouse_held = true;
				game_current = IN_GAME_SINGLE;
				break;
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
			if (player_name.length() <= 15 && !entered) {
				player_name += i;
			}
		}
	}
	if (keydown[8]) {
		something_pressed = true;
		if (player_name.length() > 0 && !entered) {
			player_name.pop_back();
		}
	}
	if (something_pressed) {
		entered = true;
	}
	else {
		entered = false;
	}
}

void ofApp::update_singleplayer_game() {
	//reduces the firing cooldown of the player.
	p1.cooldown_reduce();

	//determines the player's new direction based on the keys held down at this particular time.
	int vert_displacement = 0;
	int hor_displacement = 0;
	if (keydown['W']) {
		vert_displacement--;
	}
	if (keydown['S']) {
		vert_displacement++;
	}
	if (keydown['A']) {
		hor_displacement--;
	}
	if (keydown['D']) {
		hor_displacement++;
	}

	//sets the player's new direction based on the keys held down.
	if (vert_displacement == -1) {
		if (hor_displacement == -1) {
			p1.change_direction(NORTHWEST);
		}
		else if (hor_displacement == 0) {
			p1.change_direction(NORTH);
		}
		else {
			p1.change_direction(NORTHEAST);
		}
	}
	else if (vert_displacement == 0) {
		if (hor_displacement == -1) {
			p1.change_direction(WEST);
		}
		else if (hor_displacement == 0) {
			p1.change_direction(STOP);
		}
		else {
			p1.change_direction(EAST);
		}
	}
	else {
		if (hor_displacement == -1) {
			p1.change_direction(SOUTHWEST);
		}
		else if (hor_displacement == 0) {
			p1.change_direction(SOUTH);
		}
		else {
			p1.change_direction(SOUTHEAST);
		}
	}

	//after changing direction, move the player.
	p1.move();

	//if the mouse button is held down and the player can shoot, fire a shot (and put the player into cooldown).
	if (mouse_down && p1.can_shoot() && p1.isalive()) {
		PlaySound(TEXT("sounds\\fire_shot.wav"), NULL, SND_FILENAME | SND_ASYNC);
		double shot_angle = p1.fire_shot();
		pair<double, double> player_location = p1.get_location();
		shots_on_screen.add_shot(player_location.first += (player_radius * 1.01) * cos(shot_angle), player_location.second += (player_radius * 1.01) * sin(shot_angle), shot_angle);
	}

	//move all shots on the screen.
	shots_on_screen.move();

	//after moving the shots, bounce all shots which have hit a wall.
	levelbounds.bounce_shots(shots_on_screen);

	//if the player collides with wall segment(s), resolve the collision(s).
	levelbounds.collision_resolver(p1);

	//determine whether any of the shots hit the player.
	shots_on_screen.hit_player(p1);
}

void ofApp::update_pause() {
	if (mouse_down) {
		int pressed = buttons_in_level.on_button(ofGetMouseX(), ofGetMouseY(), PAUSE);
		if (!mouse_held) {
			cout << pressed;
			switch (pressed) {
			case (paused_back_to_menu):
				mouse_held = true;
				levelbounds.clear_level();
				shots_on_screen.clear_shots();
				p1.set_location(level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.4);
				p1.revive_player();
				game_current = MAIN_MENU;
				break;
			}
		}
	}
}

void ofApp::draw_menu() {
	//draw the demo player
	p1.draw_player();
	p1.set_name(player_name);

	//draw the player name
	character_name.drawString("Player name:", level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.35);
	character_name.drawString(player_name, level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.4);

	//draw player color
	character_name.drawString("Player color:", level_width_multiplier * wall_width * 0.75, level_height_multiplier * wall_width * 0.35);

	//draw the title
	game_title_text.drawStringCentered("2D Shooter Game", level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.15);
	buttons_in_level.draw_button(game_current, button_text);
}

void ofApp::draw_single_params() {
	button_text.drawStringCentered("Please select the amount of walls:", level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.15);
	buttons_in_level.draw_button(game_current, button_text);
}

void ofApp::draw_singleplayer_game() {
	//draw all wall segments
	levelbounds.draw_all_walls();

	//draw the player
	p1.draw_player();

	//draw the shots
	shots_on_screen.draw_shot();
}

void ofApp::draw_pause() {
	//draw all wall segments
	levelbounds.draw_all_walls();

	//draw the player
	p1.draw_player();

	//draw the shots
	shots_on_screen.draw_shot();

	//draw paused interface
	ofSetColor(255, 255, 255, 128);
	ofDrawRectangle(level_width_multiplier * wall_width * 0.25, level_height_multiplier * wall_width * 0.25, level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.5);
	ofSetColor(0, 0, 0);
	character_name.drawStringCentered("Game paused", level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.3);
	character_name.drawStringCentered("Press P to unpause", level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.35);
	buttons_in_level.draw_button(game_current, button_text);
}
