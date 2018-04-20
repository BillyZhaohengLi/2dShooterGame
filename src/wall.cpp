#include "wall.h"
/*
constructor; create a wall segment at the specified location with specified width and height.
*/
Wall::WallSegment::WallSegment(int x_left, int y_up, int x_span, int y_span) {
	x_left_ = x_left;
	x_span_ = x_span;
	y_up_ = y_up;
	y_span_ = y_span;
}

/*
handles collision between a wall segment and the player; if the player is in contact with the wall push them out.
*/
void Wall::WallSegment::collision_handler(Player& player_moving) {
	//get the player's coordinates
	pair<double, double> temp = player_moving.get_location();
	double p_x = temp.first;
	double p_y = temp.second;

	//convert the player coordinates and the four corners of the wall segment into points; check for collision
	//between the player and the four sides defined by the four points of the wall segment.
	Point player_location = Point(temp.first, temp.second);
	Point wall_NW = Point(x_left_, y_up_);
	Point wall_NE = Point(x_left_ + x_span_, y_up_);
	Point wall_SW = Point(x_left_, y_up_ + y_span_);
	Point wall_SE = Point(x_left_ + x_span_, y_up_ + y_span_);
	//the player collides with the north wall
	if (line_segment_circle(wall_NW, wall_NE, player_location, player_radius)) {
		cout << "touch wall" << "\n";
		//if circle is above wall
		if (p_y < y_up_) {
			//touching wall at corner; trig knowledge alert
			//resolves the collision by pushing the player in the direction that requires the least distance moved to resolve the collision.
			if (p_x < x_left_) {
				double x_dif = x_left_ - p_x;
				double y_dif = y_up_ - p_y;
				double angle = atan(y_dif / x_dif);
				double new_x = x_left_ - player_radius * cos(angle) - epsilon;
				double new_y = y_up_ - player_radius * sin(angle) - epsilon;
				player_moving.set_location(new_x, new_y);
			}
			else if (p_x > x_left_ + x_span_) {
				double x_dif = p_x - x_left_ - x_span_;
				double y_dif = y_up_ - p_y;
				double angle = atan(y_dif / x_dif);
				double new_x = x_left_ + x_span_ + player_radius * cos(angle) + epsilon;
				double new_y = y_up_ - player_radius * sin(angle) - epsilon;
				player_moving.set_location(new_x, new_y);
			}
			//touching wall at side. Pushes the player outwards.
			else {
				player_moving.set_location(p_x, y_up_ - player_radius - epsilon);
			}
		}
	}
	//the player collides with the south wall
	if (line_segment_circle(wall_SW, wall_SE, player_location, player_radius)) {
		cout << "touch wall" << "\n";
		//if circle is below wall
		if (p_y > y_up_ + y_span_) {
			//touching wall at corner; trig knowledge alert
			if (p_x < x_left_) {
				double x_dif = x_left_ - p_x;
				double y_dif = p_y - y_up_ - y_span_;
				double angle = atan(y_dif / x_dif);
				double new_x = x_left_ - player_radius * cos(angle) - epsilon;
				double new_y = y_up_ + y_span_ + player_radius * sin(angle) + epsilon;
				player_moving.set_location(new_x, new_y);
			}
			else if (p_x > x_left_ + x_span_) {
				double x_dif = p_x - x_left_ - x_span_;
				double y_dif = p_y - y_up_ - y_span_;
				double angle = atan(y_dif / x_dif);
				double new_x = x_left_ + x_span_ + player_radius * cos(angle) + epsilon;
				double new_y = y_up_ + y_span_ + player_radius * sin(angle) + epsilon;
				player_moving.set_location(new_x, new_y);
			}
			else {
				player_moving.set_location(p_x, y_up_ + y_span_ + player_radius + epsilon);
			}
		}
	}
	//the player collides with the west wall
	if (line_segment_circle(wall_NW, wall_SW, player_location, player_radius)) {
		cout << "touch wall" << "\n";
		//if circle is left of wall
		if (p_x < x_left_) {
			if (p_y < y_up_) {
				double x_dif = x_left_ - p_x;
				double y_dif = y_up_ - p_y;
				double angle = atan(y_dif / x_dif);
				double new_x = x_left_ - player_radius * cos(angle) - epsilon;
				double new_y = y_up_ - player_radius * sin(angle) - epsilon;
				player_moving.set_location(new_x, new_y);
			} else if (p_y > y_up_ + y_span_) {
				double x_dif = x_left_ - p_x;
				double y_dif = p_y - y_up_ - y_span_;
				double angle = atan(y_dif / x_dif);
				double new_x = x_left_ - player_radius * cos(angle) - epsilon;
				double new_y = y_up_ + y_span_ + player_radius * sin(angle) + epsilon;
				player_moving.set_location(new_x, new_y);
			}
			else {
				player_moving.set_location(x_left_ - player_radius - epsilon, p_y);
			}
		}
	}
	//the player collides with the east wall
	if (line_segment_circle(wall_NE, wall_SE, player_location, player_radius)) {
		cout << "touch wall" << "\n";
		//if circle is right of wall
		if (p_x > x_left_ + x_span_) {
			if (p_y < y_up_) {
				double x_dif = p_x - x_left_ - x_span_;
				double y_dif = y_up_ - p_y;
				double angle = atan(y_dif / x_dif);
				double new_x = x_left_ + x_span_ + player_radius * cos(angle) + epsilon;
				double new_y = y_up_ - player_radius * sin(angle) - epsilon;
				player_moving.set_location(new_x, new_y);
			}
			else if (p_y > y_up_ + y_span_) {
				double x_dif = p_x - x_left_ - x_span_;
				double y_dif = p_y - y_up_ - y_span_;
				double angle = atan(y_dif / x_dif);
				double new_x = x_left_ + x_span_ + player_radius * cos(angle) + epsilon;
				double new_y = y_up_ + y_span_ + player_radius * sin(angle) + epsilon;
				player_moving.set_location(new_x, new_y);
			}
			else {
				player_moving.set_location(x_left_ + x_span_ + player_radius + epsilon, p_y);
			}
		}
	}
}

/*
handles collision between a wall segment and an individual shot. If the shot hits the wall "bounces" the shot in an appropriate direction.
*/
void Wall::WallSegment::bounce_shot(ShotInLevel::Shot& to_bounce) {
	//generate 6 points; two based on the shot's current and previous locations, four based on the four corners of the wall.
	//check for collision between the shot and the four sides defined by the four points of the wall segment.
	//if a bounce occurs, the remaining bounces for the shot is decreased by one.
	Point shot_before = Point(to_bounce.posx - shot_length * cos(to_bounce.angle), to_bounce.posy - shot_length * sin(to_bounce.angle));
	Point shot_now = Point(to_bounce.posx, to_bounce.posy);
	Point wall_NW = Point(x_left_, y_up_);
	Point wall_NE = Point(x_left_ + x_span_, y_up_);
	Point wall_SW = Point(x_left_, y_up_ + y_span_);
	Point wall_SE = Point(x_left_ + x_span_, y_up_ + y_span_);

	//the shot trajectory intersects the west wall
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
	//the shot trajectory intersects the east wall
	//else-if is not used here since it can be mathematically proven that every shot can only be bounced once per frame per wall segment.
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
	//the shot trajectory intersects the north wall
	if (doIntersect(shot_before, shot_now, wall_NW, wall_NE)) {
		to_bounce.bounces_remaining--;
		//if the shot is coming from the top
		if (to_bounce.angle >= 0) {
			to_bounce.posy = y_up_ * 2 - to_bounce.posy;
			to_bounce.angle = -to_bounce.angle;
		}
	}
	//the shot trajectory intersects the south wall
	if (doIntersect(shot_before, shot_now, wall_SW, wall_SE)) {
		to_bounce.bounces_remaining--;
		//if the shot is coming from the bottom
		if (to_bounce.angle <= 0) {
			to_bounce.posy = (y_up_ + y_span_) * 2 - to_bounce.posy;
			to_bounce.angle = -to_bounce.angle;
		}
	}
}

/*
add 4 wall segments into the level representing the four sides of the level, "boxing" the player in.
*/
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

/*
add a new wall into the level.
*/
void Wall::add_wall(int x_left, int y_up, int x_right, int y_down) {
	walls.push_back(WallSegment(x_left, y_up, x_right, y_down));
}

/*
draw all walls in the level calling ofDrawRectangle for each wall segment.
*/
void Wall::draw_all_walls() {
	ofSetColor(0, 0, 0);
	for (WallSegment i : walls) {
		ofDrawRectangle(i.x_left_, i.y_up_, i.x_span_, i.y_span_);
	}
}

/*
bounces shots off walls in a level. Calls bounce_shots of each wall segment for each individual shot in shots_in_level.
*/
void Wall::bounce_shots(ShotInLevel &shots_in_level) {
	//vector containing indices of the shots which have no bounces remaining; they will be deleted after the bouncing is finished.
	vector<int> to_remove;
	for (int i = 0; i < shots_in_level.shots_in_level.size(); i++) {
		for (int j = 0; j < walls.size(); j++) {
			walls[j].bounce_shot(shots_in_level.shots_in_level[i]);
			//if the shot has no bounces left and its index is not already in the to_remove array add its index.
			if (shots_in_level.shots_in_level[i].bounces_remaining <= 0 && std::find(to_remove.begin(), to_remove.end(), i) == to_remove.end()) {
				to_remove.push_back(i);
			}
		}
	}
	//remove all shots with the indices in the to_remove array; notice the backward iteration since deleting an elements shifts the indices of all those behind it.
	for (int i = to_remove.size() - 1; i > -1; i--) {
		shots_in_level.shots_in_level.erase(shots_in_level.shots_in_level.begin() + to_remove[i]);
	}
}

/*
resolves collision between the player and the walls in the level; calls collision_handler function of individual wall segments.
*/
void Wall::collision_resolver(Player &player_moving) {
	for (int i = 0; i < walls.size(); i++) {
		walls[i].collision_handler(player_moving);
	}
}