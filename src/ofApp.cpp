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
Player p1 = Player(100, 100, 0, 0, 255);
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("2D shooter game");
	levelbounds.add_boundary();
	levelbounds.add_wall(400, 400, 200, 200);
}

//--------------------------------------------------------------
void ofApp::update(){
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

//--------------------------------------------------------------
void ofApp::draw(){
	//draw all wall segments
	levelbounds.draw_all_walls();

	//draw the player
	p1.draw_player();

	//draw the shots
	shots_on_screen.draw_shot();
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
