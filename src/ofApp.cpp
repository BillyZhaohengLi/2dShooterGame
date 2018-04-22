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
Player p1 = Player(wall_width * 2.5, (level_height_multiplier - 2.5) * wall_width, 0, 0, 255);

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

//--------------------------------------------------------------
void ofApp::setup(){
	//load text for buttons
	button_text.loadFont("verdana.ttf", wall_width);
	button_text.setLineHeight(18.0f);
	button_text.setLetterSpacing(1.037);

	game_title_text.loadFont("verdana.ttf", wall_width * 2);
	game_title_text.setLineHeight(18.0f);
	game_title_text.setLetterSpacing(1.037);

	ofSetWindowTitle("2D shooter game");
	game_current = MAIN_MENU;

	//start game button
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.35, level_height_multiplier * wall_width * 0.35,
		level_width_multiplier * wall_width * 0.3, level_height_multiplier * wall_width * 0.15, "Start game", MAIN_MENU);

	//multiplayer button (doesn't do anything yet)
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.35, level_height_multiplier * wall_width * 0.55,
		level_width_multiplier * wall_width * 0.3, level_height_multiplier * wall_width * 0.15, "Multiplayer", MAIN_MENU);

	//exit button; exits the game
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.35, level_height_multiplier * wall_width * 0.75,
		level_width_multiplier * wall_width * 0.3, level_height_multiplier * wall_width * 0.15, "Exit", MAIN_MENU);

	levelbounds.add_boundary();
	levelbounds.random_level_generator(24);
}

//--------------------------------------------------------------
void ofApp::update(){
	switch (game_current) {
	case MAIN_MENU:
		update_menu();
		break;
	case IN_GAME_SINGLE:
		update_singleplayer_game();
		break;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	switch (game_current) {
	case MAIN_MENU:
		draw_menu();
		break;
	case IN_GAME_SINGLE:
		draw_singleplayer_game();
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	//sets the relevant cell in the keydown array to true
	int upper_key = toupper(key);
	keydown[upper_key] = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	//sets the relevant cell in the keydown array to false
	int upper_key = toupper(key);
	keydown[upper_key] = false;
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
	if (mouse_down) {
		int pressed = buttons_in_level.on_button(ofGetMouseX(), ofGetMouseY(), MAIN_MENU);
		if (pressed == start_singleplayer_button) {
			game_current = IN_GAME_SINGLE;
		}
		else if (pressed == start_multiplayer_button) {

		}
		else if (pressed == exit_button) {
			std::exit(0);
		}
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

void ofApp::draw_menu() {
	//draw the title
	game_title_text.drawStringCentered("2D Shooter Game", level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.15);
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

