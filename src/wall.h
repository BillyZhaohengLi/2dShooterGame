#pragma once
#include <vector>
#include "ofMain.h"
#include "const.h"
#include "player.h"
#include "shot.h"
#include "helperfunctions.h"
using namespace std;
class Wall {
private:
	struct WallSegment {
		int x_left_;
		int x_span_;
		int y_up_;
		int y_span_;
		WallSegment(int x_left, int y_up, int x_span, int y_span);
		pair<int, int> collision_handler(int x_loc, int y_loc);
		void bounce_shot(ShotInLevel::Shot &to_bounce);
	};
	vector<WallSegment> walls;
public:
	Wall() { vector<WallSegment> walls(); };
	void add_boundary();
	void draw_all_walls();
	void add_wall(int x_left, int y_up, int x_span, int y_span);
	pair<int, int> collision_resolver(int x_loc, int y_loc);
	void bounce_shots(ShotInLevel &shots_in_level);
};
