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

void Wall::bounce_shots(ShotInLevel shots_in_level) {
	for (int i = 0; i < shots_in_level.shots_in_level.size(); i++) {
		for (int j = 0; j < walls.size(); j++) {
			walls[j].bounce_shot(shots_in_level.shots_in_level[i]);
		}
	}
}

void Wall::WallSegment::bounce_shot(ShotInLevel::Shot shot_to_bounce) {
	Point shot_before = Point(shot_to_bounce.posx - shot_length * cos(shot_to_bounce.angle), shot_to_bounce.posy - shot_length * sin(shot_to_bounce.angle));
	Point shot_now = Point(shot_to_bounce.posx, shot_to_bounce.posy);
	Point wall_NW = Point(x_left_, y_up_);
	Point wall_NE = Point(x_left_ + x_span_, y_up_);
	Point wall_SW = Point(x_left_, y_up_ + y_span_);
	Point wall_SE = Point(x_left_ + x_span_, y_up_ + y_span_);
	//left wall
	if (doIntersect(shot_before, shot_now, wall_NW, wall_SW)) {
		cout << shot_to_bounce.angle << "\n";
		//if the shot is coming from the left
		if (shot_to_bounce.angle >= -pi / 2 && shot_to_bounce.angle <= pi / 2) {
			shot_to_bounce.posx = x_left_ * 2 - shot_to_bounce.posx;
			if (shot_to_bounce.angle <= 0) {
				shot_to_bounce.angle = -pi - shot_to_bounce.angle;
			}
			else {
				shot_to_bounce.angle = pi - shot_to_bounce.angle;
			}
		}
	}
	//right wall
	if (doIntersect(shot_before, shot_now, wall_NE, wall_SE)) {
		cout << shot_to_bounce.angle << "\n";
		//if the shot is coming from the right
		if (shot_to_bounce.angle <= -pi / 2 || shot_to_bounce.angle >= pi / 2) {
			shot_to_bounce.posx = (x_left_ + x_span_) * 2 - shot_to_bounce.posx;
			if (shot_to_bounce.angle <= -pi / 2) {
				shot_to_bounce.angle = -pi - shot_to_bounce.angle;
			}
			else {
				shot_to_bounce.angle = pi - shot_to_bounce.angle;
			}
		}
	}
	//top wall
	if (doIntersect(shot_before, shot_now, wall_NW, wall_NE)) {
		cout << shot_to_bounce.angle << "\n";
		//if the shot is coming from the top
		if (shot_to_bounce.angle >= 0) {
			shot_to_bounce.posy = y_up_ * 2 - shot_to_bounce.posy;
			shot_to_bounce.angle = -shot_to_bounce.angle;
		}
	}
	//bottom wall
	if (doIntersect(shot_before, shot_now, wall_SW, wall_SE)) {
		cout << shot_to_bounce.angle << "\n";
		//if the shot is coming from the bottom
		if (shot_to_bounce.angle <= 0) {
			shot_to_bounce.posy = (y_up_ + y_span_) * 2 - shot_to_bounce.posy;
			shot_to_bounce.angle = -shot_to_bounce.angle;
		}
	}
}

pair<int, int> Wall::collision_resolver(int x_loc, int y_loc) {
	for (int i = 0; i < walls.size(); i++) {

	}
	return pair<int, int>(0, 0);
}