#include "wall.h"
Wall::WallSegment::WallSegment(int x_left, int y_up, int x_span, int y_span) {
	x_left_ = x_left;
	x_span_ = x_span;
	y_up_ = y_up;
	y_span_ = y_span;
}

pair<int, int> Wall::WallSegment::collision_handler(int xpos, int ypos) {
	bool colliding = false;
	return pair<int, int>(0, 0);
}

void Wall::add_boundary() {
	//top wall
	walls.push_back(WallSegment(0, 0, level_width, wall_width));
	//bottom wall
	walls.push_back(WallSegment(0, level_height - wall_width, level_width, wall_width));
	//left wall
	walls.push_back(WallSegment(0, wall_width, wall_width, level_height - wall_width * 2));
	//right wall
	walls.push_back(WallSegment(level_width - wall_width, wall_width, wall_width, level_height - wall_width * 2));
	
}

void Wall::add_wall(int x_left, int y_up, int x_right, int y_down) {
	walls.push_back(WallSegment(x_left, y_up, x_right, y_down));
}

void Wall::draw_all_walls() {
	ofSetColor(0, 0, 0);
	for (WallSegment i : walls) {
		ofDrawRectangle(i.x_left_, i.y_up_, i.x_span_, i.y_span_);
	}
}

void Wall::bounce_shots(ShotInLevel &shots_in_level) {
	vector<int> to_remove;
	for (int i = 0; i < shots_in_level.shots_in_level.size(); i++) {
		for (int j = 0; j < walls.size(); j++) {
			walls[j].bounce_shot(shots_in_level.shots_in_level[i]);
			if (shots_in_level.shots_in_level[i].bounces_remaining <= 0 && std::find(to_remove.begin(), to_remove.end(), i) == to_remove.end()) {
				to_remove.push_back(i);
			}
		}
	}
	for (int i = to_remove.size() - 1; i > -1; i--) {
		shots_in_level.shots_in_level.erase(shots_in_level.shots_in_level.begin() + to_remove[i]);
	}
}

void Wall::WallSegment::bounce_shot(ShotInLevel::Shot& to_bounce) {
	Point shot_before = Point(to_bounce.posx - shot_length * cos(to_bounce.angle), to_bounce.posy - shot_length * sin(to_bounce.angle));
	Point shot_now = Point(to_bounce.posx, to_bounce.posy);
	Point wall_NW = Point(x_left_, y_up_);
	Point wall_NE = Point(x_left_ + x_span_, y_up_);
	Point wall_SW = Point(x_left_, y_up_ + y_span_);
	Point wall_SE = Point(x_left_ + x_span_, y_up_ + y_span_);
	//left wall
	if (doIntersect(shot_before, shot_now, wall_NW, wall_SW)) {
		//if the shot is coming from the left
		if (to_bounce.angle >= -pi / 2 && to_bounce.angle <= pi / 2) {
			to_bounce.bounces_remaining--;
			to_bounce.posx = x_left_ * 2 - to_bounce.posx;
			if (to_bounce.angle <= 0) {
				to_bounce.angle = -pi - to_bounce.angle;
			}
			else {
				to_bounce.angle = pi - to_bounce.angle;
			}
		}
	}
	//right wall
	if (doIntersect(shot_before, shot_now, wall_NE, wall_SE)) {
		//if the shot is coming from the right
		if (to_bounce.angle <= -pi / 2 || to_bounce.angle >= pi / 2) {
			to_bounce.bounces_remaining--;
			to_bounce.posx = (x_left_ + x_span_) * 2 - to_bounce.posx;
			if (to_bounce.angle <= -pi / 2) {
				to_bounce.angle = -pi - to_bounce.angle;
			}
			else {
				to_bounce.angle = pi - to_bounce.angle;
			}
		}
	}
	//top wall
	if (doIntersect(shot_before, shot_now, wall_NW, wall_NE)) {
		to_bounce.bounces_remaining--;
		//if the shot is coming from the top
		if (to_bounce.angle >= 0) {
			to_bounce.posy = y_up_ * 2 - to_bounce.posy;
			to_bounce.angle = -to_bounce.angle;
		}
	}
	//bottom wall
	if (doIntersect(shot_before, shot_now, wall_SW, wall_SE)) {
		to_bounce.bounces_remaining--;
		//if the shot is coming from the bottom
		if (to_bounce.angle <= 0) {
			to_bounce.posy = (y_up_ + y_span_) * 2 - to_bounce.posy;
			to_bounce.angle = -to_bounce.angle;
		}
	}
}

pair<int, int> Wall::collision_resolver(int x_loc, int y_loc) {
	for (int i = 0; i < walls.size(); i++) {

	}
	return pair<int, int>(0, 0);
}