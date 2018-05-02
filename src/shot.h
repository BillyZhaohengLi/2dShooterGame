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
		double xpos_;

		/*
		the shot's y coordinate.
		*/
		double ypos_;

		/*
		the angle of the shot's trajectory.
		*/
		double angle_;

		/*
		the number of times the shot can bounce; reduced by 1 every time the shot bounces off a wall and when it hits 0, the shot is deleted.
		*/
		int bounces_remaining_;

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

		/*
		returns an ugly data structure containing the shot parameters of this shot.
		nothing is actually done with the contents of the data structure; it is only used to reset the shot by being fed back into the shot
		in the reset_shot method below.
		*/
		pair<pair<double, double>, pair<double, int>> get_shot_parameters();

		/*
		set the shot's parameters based on the index and the aforementioned data structure in get_shot_parameters.
		*/
		void reset_shot(pair<pair<double, double>, pair<double, int>> parameters);
	};

	/*
	vector containing all Shot objects in the level.
	*/
	vector<Shot> shots_in_level;

	/*
	add a shot at the specified location traveling in a specified angle. Calls the Shot constructor.
	*/
	void add_shot(double xpos, double ypos, double angle);

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

	/*
	removes all current shots in the level.
	*/
	void clear_shots();

	/*
	serialized string format of all shots in the level. Used in multiplayer; shots are managed at the host server and sent to the client.
	*/
	string serialized_string();

	/*
	deserialize an update message from the host server and adds the appropriate shots to the ShotsInLevel in the client program.
	*/
	void deserialize_update_message(string message);

	/*
	returns an ugly data structure containing the shot parameters of the (shot_id)th shot in the level in terms of array index.
	nothing is actually done with the contents of the data structure; it is only used to reset the shot by being fed back into the reset_shot
	method below this if needed in the shot-wall collision algorithm.
	if the shot is not found returns all 0s.
	*/
	pair<pair<double, double>, pair<double, int>> get_shot_parameters(int shot_id);

	/*
	set a shot's parameters based on the index and the aforementioned data structure in get_shot_parameters.
	*/
	void reset_shot(int shot_id, pair<pair<double, double>, pair<double, int>> parameters);
};