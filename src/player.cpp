#include "player.h"
/*
constructor; create a player at the specified x and y coordinates with color rgb.
*/
Player::Player(double x, double y, int r, int g, int b) {
	xpos = x;
	ypos = y;
	red = r;
	green = g;
	blue = b;
	alive = true;
	facing = STOP;
	shot_cooldown = 10;
}

/*
returns the player's location as a pair of doubles.
*/
pair<double, double> Player::get_location() {
	return pair<double, double>(xpos, ypos);
}

/*
set's the player's location; used to handle collisions with walls
*/
void Player::set_location(double new_x, double new_y) {
	xpos = new_x;
	ypos = new_y;
}

/*
returns whether the player is alive.
*/
bool Player::isalive() {
	return alive;
}

/*
change the direction the player is facing; called when the player enters some sort of combination of WASD keys.
*/
void Player::change_direction(direction change_to) {
	facing = change_to;
}

/*
moves the player. Called at every update function; modifies player coordinates based on the direction they are facing.
*/
void Player::move() {
	//only move the player if they are alive (duh).
	if (alive) {
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
}

/*
kills the player (sets alive to false). Called when the player gets hit by a shot.
*/
void Player::kill_player() {
	if (alive) {
		PlaySound(TEXT("sounds\\die.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
	alive = false;
}

/*
draws the player using ofDrawCircle.
*/
void Player::draw_player() {
	if (alive) {
		ofSetColor(red, green, blue);

		//draw the player circle corresponding with the hitbox
		ofDrawCircle(xpos, ypos, player_radius);
		ofSetColor(0, 0, 0);
		ofSetLineWidth(4);

		//draw a smiley face on the player
		ofDrawCircle(xpos - cos(pi / 4) * player_radius * 0.5, ypos - cos(pi / 4) * player_radius * 0.5, player_radius * 0.2);
		ofDrawCircle(xpos + cos(pi / 4) * player_radius * 0.5, ypos - cos(pi / 4) * player_radius * 0.5, player_radius * 0.2);
		ofDrawLine(xpos - cos(pi / 4) * player_radius * 0.75, ypos + cos(pi / 4) * player_radius * 0.5, xpos - cos(pi / 4) * player_radius * 0.5, ypos + cos(pi / 4) * player_radius * 0.75);
		ofDrawLine(xpos + cos(pi / 4) * player_radius * 0.75, ypos + cos(pi / 4) * player_radius * 0.5, xpos + cos(pi / 4) * player_radius * 0.5, ypos + cos(pi / 4) * player_radius * 0.75);
		ofDrawLine(xpos - cos(pi / 4) * player_radius * 0.5, ypos + cos(pi / 4) * player_radius * 0.75, xpos + cos(pi / 4) * player_radius * 0.5, ypos + cos(pi / 4) * player_radius * 0.75);
		
		double gun_angle = atan2(ofGetMouseY() - ypos, ofGetMouseX() - xpos);
		//draw the gun; if the player is firing add a firing effect.
		if (shot_cooldown >= player_shot_cooldown * 0.9) {
			ofDrawLine(xpos + cos(gun_angle) * player_radius, ypos + sin(gun_angle) * player_radius, xpos + cos(gun_angle) * player_radius * 1.25, ypos + sin(gun_angle) * player_radius * 1.25);
			ofSetColor(255, 255, 0, 128);
			ofDrawCircle(xpos + cos(gun_angle) * player_radius * 1.25, ypos + sin(gun_angle) * player_radius * 1.25, 6);
		}
		else {
			ofDrawLine(xpos + cos(gun_angle) * player_radius, ypos + sin(gun_angle) * player_radius, xpos + cos(gun_angle) * player_radius * 1.5, ypos + sin(gun_angle) * player_radius * 1.5);
		}
	}
	//if the player is dead draw them in black.
	else {
		ofSetColor(red, green, blue);

		//draw the player circle
		ofDrawCircle(xpos, ypos, player_radius);
		ofSetColor(0, 0, 0);
		ofSetLineWidth(3);

		//draw a sad face on the player
		ofDrawLine(xpos - cos(pi / 4) * player_radius * 0.15, ypos - cos(pi / 4) * player_radius * 0.15, xpos - cos(pi / 4) * player_radius * 0.85, ypos - cos(pi / 4) * player_radius * 0.85);
		ofDrawLine(xpos + cos(pi / 4) * player_radius * 0.15, ypos - cos(pi / 4) * player_radius * 0.15, xpos + cos(pi / 4) * player_radius * 0.85, ypos - cos(pi / 4) * player_radius * 0.85);
		ofDrawLine(xpos - cos(pi / 4) * player_radius * 0.15, ypos - cos(pi / 4) * player_radius * 0.85, xpos - cos(pi / 4) * player_radius * 0.85, ypos - cos(pi / 4) * player_radius * 0.15);
		ofDrawLine(xpos + cos(pi / 4) * player_radius * 0.15, ypos - cos(pi / 4) * player_radius * 0.85, xpos + cos(pi / 4) * player_radius * 0.85, ypos - cos(pi / 4) * player_radius * 0.15);
		ofDrawLine(xpos - cos(pi / 4) * player_radius * 0.75, ypos + cos(pi / 4) * player_radius * 0.75, xpos - cos(pi / 4) * player_radius * 0.5, ypos + cos(pi / 4) * player_radius * 0.5);
		ofDrawLine(xpos + cos(pi / 4) * player_radius * 0.75, ypos + cos(pi / 4) * player_radius * 0.75, xpos + cos(pi / 4) * player_radius * 0.5, ypos + cos(pi / 4) * player_radius * 0.5);
		ofDrawLine(xpos - cos(pi / 4) * player_radius * 0.5, ypos + cos(pi / 4) * player_radius * 0.5, xpos + cos(pi / 4) * player_radius * 0.5, ypos + cos(pi / 4) * player_radius * 0.5);
	}
}

/*
fires a shot; returns the angle at which the shot was fired and sets cooldown to a designated value.
*/
double Player::fire_shot() {
	shot_cooldown = player_shot_cooldown;
	return atan2(ofGetMouseY() - ypos, ofGetMouseX() - xpos);
}

/*
returns a boolean based on whether the player can fire a shot. True if cooldown is 0; false if otherwise.
*/
bool Player::can_shoot() {
	return shot_cooldown == 0;
}

/*
reduces the player's cooldown by 1 if its not 0. Called every update.
*/
void Player::cooldown_reduce() {
	if (shot_cooldown != 0) {
		shot_cooldown--;
	}
}