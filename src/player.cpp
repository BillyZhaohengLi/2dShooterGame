#include "player.h"
Player::Player(double x, double y, int r, int g, int b) {
	xpos = x;
	ypos = y;
	red = r;
	green = g;
	blue = b;
	alive = true;
	facing = STOP;
	shot_cooldown = 0;
}

void Player::move() {
	switch (facing) {
	case STOP:
		break;
	case WEST:
		xpos -= player_velocity;
		break;
	case EAST:
		xpos += player_velocity;
		break;
	case NORTH:
		ypos -= player_velocity;
		break;
	case SOUTH:
		ypos += player_velocity;
		break;
	case NORTHWEST:
		xpos -= (player_velocity * (sqrt(2) / 2));
		ypos -= (player_velocity * (sqrt(2) / 2));
		break;
	case NORTHEAST:
		xpos += (player_velocity * (sqrt(2) / 2));
		ypos -= (player_velocity * (sqrt(2) / 2));
		break;
	case SOUTHWEST:
		xpos -= (player_velocity * (sqrt(2) / 2));
		ypos += (player_velocity * (sqrt(2) / 2));
		break;
	case SOUTHEAST:
		xpos += (player_velocity * (sqrt(2) / 2));
		ypos += (player_velocity * (sqrt(2) / 2));
		break;
	}
}

void Player::change_direction(direction change_to) {
	facing = change_to;
}

bool Player::isalive() {
	return alive;
}

void Player::draw_player() {
	ofSetColor(red, green, blue);
	ofDrawCircle(xpos, ypos, player_radius);
}

double Player::fire_shot() {
	shot_cooldown = player_shot_cooldown;
	return atan2(ofGetMouseY() - ypos, ofGetMouseX() - xpos);
}

pair<int, int> Player::get_location() {
	return pair<int, int>(xpos, ypos);
}

bool Player::can_shoot() {
	return shot_cooldown == 0;
}

void Player::cooldown_reduce() {
	if (shot_cooldown != 0) {
		shot_cooldown--;
	}
}