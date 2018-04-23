#pragma once
#include "ofMain.h"
#include "const.h"
#include "player.h"
#include <math.h>
/*
class containing all shots fired in a level.
*/
class ShotInLevel {
private:
	
public:
	/*
	internal struct; contains parameters of individual shots within a level.
	*/
	struct Shot {
		/*
		the shot's x coordinate.
		*/
		double posx;

		/*
		the shot's y coordinate.
		*/
		double posy;

		/*
		the angle of the shot's trajectory.
		*/
		double angle;

		/*
		the number of times the shot can bounce; reduced by 1 every time the shot bounces off a wall and when it hits 0, the shot is deleted.
		*/
		int bounces_remaining;

		/*
		constructor; creates a shot at the designated x and y position with a trajectory defined by an initial angle.
		*/
		Shot(double x, double y, double initial_angle);

		/*
		move the shot in the direction defined by its angle; called every update.
		*/
		void move();

		/*
		draw the shot using ofDrawCircle.
		*/
		void draw_shot();
	};

	/*
	vector containing all Shot objects in the level.
	*/
	vector<Shot> shots_in_level;

	/*
	empty constructor.
	*/
	ShotInLevel() { vector<Shot> shots_in_level; };

	/*
	add a shot at the specified location traveling in a specified angle. Calls the Shot constructor.
	*/
	void add_shot(double posx, double posy, double angle);

	/*
	moves all shots in the level; calls the move function for each individual shot.
	*/
	void move();

	/*
	draws all shots in the level; calls the draw function for each individual shot.
	*/
	void draw_shot();

	/*
	checks whether a player is hit by any given shot within the level. If the player gets hit call the kill_player function of the player.
	*/
	void hit_player(Player &player_to_check);

	void clear_shots();
};