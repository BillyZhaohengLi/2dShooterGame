#include "shot.h"
ShotInLevel::Shot::Shot(double x, double y, double initial_angle) {
	posx = x;
	posy = y;
	angle = initial_angle;
	bounces_remaining = 5;
}
void ShotInLevel::move() {
	for (int i = 0; i < shots_in_level.size(); i++) {
		shots_in_level[i].move();
	}
}
void ShotInLevel::Shot::move() {
	posx = posx + shot_length * cos(angle);
	posy = posy + shot_length * sin(angle);
}

void ShotInLevel::add_shot(double x, double y, double initial_angle) {
	shots_in_level.push_back(Shot(x, y, initial_angle));
}

void ShotInLevel::Shot::draw_shot() {
	ofSetLineWidth(4);
	ofSetColor(255, 0, 0);
	ofDrawLine(posx, posy, posx - shot_length * cos(angle), posy - shot_length * sin(angle));
}

void ShotInLevel::draw_shot() {
	for (int i = 0; i < shots_in_level.size(); i++) {
		shots_in_level[i].draw_shot();
	}
}