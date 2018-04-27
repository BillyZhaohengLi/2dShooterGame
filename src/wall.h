#pragma once
#include <vector>
#include "ofMain.h"
#include "const.h"
#include "player.h"
#include "shot.h"
#include "helperfunctions.h"
using namespace std;
/*
class for the collection of wall segments in a level.
*/
class Wall {
private:
	/*
	internal struct containing parameters for individual wall segments.
	*/
	struct WallSegment {

		/*
		the x coordinate of the left side of the wall.
		*/
		int xpos_;

		/*
		the width of the wall.
		*/
		int xspan_;

		/*
		the y coordinate of the top side of the wall.
		*/
		int ypos_;

		/*
		the height of the wall.
		*/
		int yspan_;

		/*
		constructor; create a wall segment at the specified location with specified width and height.
		*/
		WallSegment(int xpos, int ypos, int xspan, int yspan);

		/*
		handles collision between a wall segment and the player; if the player is in contact with the wall push them out.
		*/
		bool collision_handler(Player& player_moving);

		/*
		handles collision between a wall segment and an individual shot. If the shot hits the wall "bounces" the shot in an appropriate direction.
		*/
		bool bounce_shot(ShotInLevel::Shot &to_bounce);
	};

	/*
	vector containing all wall segments in a level.
	*/
	vector<WallSegment> walls;
public:
	/*
	add 4 wall segments into the level representing the four sides of the level, "boxing" the player in.
	*/
	void add_boundary();

	/*
	add a new wall into the level.
	*/
	void add_wall(int xpos, int ypos, int xspan, int yspan);

	/*
	draw all walls in the level calling ofDrawRectangle for each wall segment.
	*/
	void draw_all_walls();

	/*
	bounces shots off walls in a level. Calls bounce_shots of each wall segment for each individual shot in shots_in_level.
	*/
	void bounce_shots(ShotInLevel &shots_in_level);

	/*
	resolves collision between the player and the walls in the level; calls collision_handler function of individual wall segments.
	*/
	void collision_resolver(Player &player_moving);

	/*
	predict shots for bots; takes in positions of two players and returns whether the line segment between the players is obstructed by walls.
	*/
	bool bot_shot_predictor(Player p1, Player p2);

	/*
	randomly generates walls in the level. Generates the specified amount of wall segments while ensuring that none of the walls overlap with each other,
	spawn near the player spawns or block off the players by splitting the map into two.
	*/
	void random_level_generator(int wall_count);

	/*
	checks whether there is a valid path between the two players.
	*/
	bool closed_path_checker();

	/*
	check whether the given wall segment intersects with any existing wall segments.
	*/
	bool intersect(int newx, int newy, int newwidth, int newheight);

	/*
	check whether the given wall segment intersects with any existing wall segments and the player spawn boxes.
	*/
	bool intersect_with_spawn(int newx, int newy, int newwidth, int newheight);

	/*
	clears the level; removes all non-boundary walls
	*/
	void clear_level();

	/*
	serialized string format of all wall segments in the level. Used in multiplayer; walls are generated at the host server and sent to the client.
	*/
	string serialized_string();

	/*
	deserialize an update message from the host server and adds the appropriate wall segments to the wall object in the client program.
	*/
	void deserialize_update_message(string message);
};
