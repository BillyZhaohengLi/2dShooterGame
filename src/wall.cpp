#include "wall.h"
Wall::WallSegment::WallSegment(int x_left, int x_right, int y_up, int y_down) {
	x_left_ = x_left;
	x_right_ = x_right;
	y_up_ = y_up;
	y_down_ = y_down;
}
Wall::Wall() {
	//top wall
	walls.push_back(WallSegment(0, level_width, 0, wall_width));
	//bottom wall
	walls.push_back(WallSegment(0, level_width, level_height - wall_width, level_height));
	//left wall
	walls.push_back(WallSegment(0, wall_width, wall_width, level_height - wall_width));
	//right wall
	walls.push_back(WallSegment(level_width - wall_width, level_width, wall_width, level_height - wall_width));
}

void Wall::add_wall(int x_left, int x_right, int y_up, int y_down) {
	walls.push_back(WallSegment(x_left, x_right, y_up, y_down));
}