#include "ofApp.h"
bool keydown[255];
bool mouse_down;
Wall levelbounds;
ShotInLevel shots_on_screen;
Player p1 = Player(100, 100, 0, 0, 255);
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("2D shooter game");
	levelbounds.add_boundary();

}

//--------------------------------------------------------------
void ofApp::update(){
	p1.cooldown_reduce();
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
	//determine new direction
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
	p1.move();
	if (mouse_down && p1.can_shoot()) {
		double shot_angle = p1.fire_shot();
		pair<int, int> player_location = p1.get_location();
		shots_on_screen.add_shot(player_location.first += shot_length * cos(shot_angle), player_location.second += shot_length * sin(shot_angle), shot_angle);
	}
	shots_on_screen.move();
	levelbounds.bounce_shots(shots_on_screen);
}

//--------------------------------------------------------------
void ofApp::draw(){
	levelbounds.draw_all_walls();
	p1.draw_player();
	shots_on_screen.draw_shot();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	int upper_key = toupper(key);
	keydown[upper_key] = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
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
