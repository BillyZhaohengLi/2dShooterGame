#pragma once
#include "const.h"
#include "ofMain.h"
#include "ofxCenteredTrueTypeFont.h"
#include <vector>
#include <math.h>
#include <mmsystem.h>
/*
player class; one player per object; stores parameters related to players in level.
*/
class Player {
private:
	/*
	player's x coordinate.
	*/
	double xpos;

	/*
	player's y coordinate.
	*/
	double ypos;

	/*
	player's rgb values; determines what color the player shows up as.
	*/
	int red;
	int green;
	int blue;

	/*
	direction the player is facing. Used to determine movement.
	*/
	direction facing;

	/*
	cooldown of player's shots. If 0 the player can fire a shot.
	*/
	int shot_cooldown;

	/*
	whether the player is alive.
	*/
	bool alive;

	string name;

	ofxCenteredTrueTypeFont name_font;
public:
	/*
	constructor; create a player at the specified x and y coordinates with color rgb.
	*/
	Player(double x, double y, int r, int g, int b, string text);

	/*
	returns the player's location as a pair of doubles.
	*/
	pair<double, double> get_location();

	/*
	set's the player's location; used to handle collisions with walls
	*/
	void set_location(double new_x, double new_y);

	/*
	returns whether the player is alive.
	*/
	bool isalive();

	/*
	change the direction the player is facing; called when the player enters some sort of combination of WASD keys.
	*/
	void change_direction(direction change_to);

	/*
	moves the player. Called at every update function; modifies player coordinates based on the direction they are facing.
	*/
	void move();

	/*
	kills the player (sets alive to false). Called when the player gets hit by a shot.
	*/
	void kill_player();

	void revive_player();

	/*
	draws the player using ofDrawCircle.
	*/
	void draw_player();

	/*
	fires a shot; returns the angle at which the shot was fired and sets cooldown to a designated value.
	*/
	double fire_shot();

	/*
	returns a boolean based on whether the player can fire a shot. True if cooldown is 0; false if otherwise.
	*/
	bool can_shoot();

	/*
	reduces the player's cooldown by 1 if its not 0. Called every update.
	*/
	void cooldown_reduce();

	void set_name(string new_name);
	void set_color(int new_red, int new_green, int new_blue);
};