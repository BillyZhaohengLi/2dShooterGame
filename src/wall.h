#pragma once
#include <vector>
#include "const.h"
using namespace std;
class Wall {
private:
	struct WallSegment {
		int x_left_;
		int x_right_;
		int y_up_;
		int y_down_;
		WallSegment(int x_left, int x_right, int y_up, int y_down);
	};
	vector<WallSegment> walls;
public:
	Wall();
	void draw_all_walls();
	void add_wall(int x_left, int x_right, int y_up, int y_down);
	bool in_wall(int x_coord, int y_coord);
	pair<int, int> laser_bounce(int velocity, int angle);
};
