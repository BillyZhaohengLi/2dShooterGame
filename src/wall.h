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
		int x_left_;

		/*
		the width of the wall.
		*/
		int x_span_;

		/*
		the y coordinate of the top side of the wall.
		*/
		int y_up_;

		/*
		the height of the wall.
		*/
		int y_span_;

		/*
		constructor; create a wall segment at the specified location with specified width and height.
		*/
		WallSegment(int x_left, int y_up, int x_span, int y_span);

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
	default constructor.
	*/
	Wall() { vector<WallSegment> walls(); };

	/*
	add 4 wall segments into the level representing the four sides of the level, "boxing" the player in.
	*/
	void add_boundary();

	/*
	add a new wall into the level.
	*/
	void add_wall(int x_left, int y_up, int x_span, int y_span);

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
	randomly generates walls in the level. Takes in two players to check that none of the walls are generated too close / on top of either player.
	*/
	void random_level_generator(int wall_count);

	bool closed_path_checker();

	bool intersect(int newx, int newy, int newwidth, int newheight);

	bool Wall::intersect_with_spawn(int newx, int newy, int newwidth, int newheight);
};
