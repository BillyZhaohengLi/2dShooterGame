#pragma once
#include "const.h"
#include "ofMain.h"
#include "ofxCenteredTrueTypeFont.h"
#include "helperfunctions.h"
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
	direction the player is facing; used to draw the player, has nothing to do with movement.
	*/
	int facing_x;
	int facing_y;

	/*
	cooldown of player's shots. If 0 the player can fire a shot.
	*/
	int shot_cooldown;

	/*
	whether the player is alive.
	*/
	bool alive;

	/*
	whether the player is a bot.
	*/
	bool is_bot;

	/*
	the cooldown between changing directions. Used by bots only.
	*/
	int change_direction_cd;

	/*
	the player's name.
	*/
	string name;

	/*
	the font to display the player's name in. Scales with the player's name length.
	*/
	ofxCenteredTrueTypeFont name_font;

public:
	/*
	constructor; create a player at the specified x and y coordinates with color rgb.
	*/
	Player(double x, double y, int r, int g, int b, bool bot, string text);

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

	/*
	revives the player (sets alive to true). Called at the start of every round.
	*/
	void revive_player();
	
	/*
	updates the direction the player is facing (used to draw the player's gun). Has different outcomes based on whether the player is a bot.
	*/
	void update_player_facing(int mouse_x, int mouse_y, Player opponent);
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

	/*
	set the player's name. Also alters font size based on the new name's length.
	*/
	void set_name(string new_name);

	/*
	getter for the player's name.
	*/
	string get_name();

	/*
	sets the player's color.
	*/
	void set_color(int new_red, int new_green, int new_blue);

	/*
	changes the player's direction based on what keys are held down. Has different outcomes based on whether the player is a bot.
	*/
	void change_direction(bool keydown[255]);

	/*
	prompts the player to shoot a bullet. Has different outcomes based on whether the player is a bot.
	the return value is a very ugly data structure consisting of the values in the following order:
	1. whether the player decides to fire a shot (bool); if this is false none of the following return values matter.
	2. the angle of the shot (double)
	3. the starting x position of the shot (double)
	4. the starting 7 position of the shot (double)
	*/
	pair<pair<bool, double>, pair<double, double>> shoot_prompt(bool mouse_down, bool clear_shot);

	/*
	sets randomized names for bots.
	*/
	void randomize_name();

	/*
	sets randomized colors for bots.
	*/
	void randomize_color();

	void set_bot(bool bot);
};