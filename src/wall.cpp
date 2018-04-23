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
bool Wall::WallSegment::collision_handler(Player& player_moving) {
	//get the player's coordinates
	pair<double, double> temp = player_moving.get_location();
	double p_x = temp.first;
	double p_y = temp.second;
	bool collided = false;

	//convert the player coordinates and the four corners of the wall segment into points; check for collision
	//between the player and the four sides defined by the four points of the wall segment.
	Point player_location = Point(temp.first, temp.second);
	Point wall_NW = Point(x_left_, y_up_);
	Point wall_NE = Point(x_left_ + x_span_, y_up_);
	Point wall_SW = Point(x_left_, y_up_ + y_span_);
	Point wall_SE = Point(x_left_ + x_span_, y_up_ + y_span_);
	//the player collides with the north wall
	if (line_segment_circle(wall_NW, wall_NE, player_location, player_radius)) {
		//if circle is above wall
		if (p_y < y_up_) {
			collided = true;
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
		//if circle is below wall
		if (p_y > y_up_ + y_span_) {
			collided = true;
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
		//if circle is left of wall
		if (p_x < x_left_) {
			collided = true;
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
		//if circle is right of wall
		if (p_x > x_left_ + x_span_) {
			collided = true;
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
	return collided;
}

/*
handles collision between a wall segment and an individual shot. If the shot hits the wall "bounces" the shot in an appropriate direction.
*/
bool Wall::WallSegment::bounce_shot(ShotInLevel::Shot& to_bounce) {
	if (to_bounce.bounces_remaining == 0) {
		return false;
	}
	bool bounced = false;
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
			bounced = true;
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
			bounced = true;
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
		//if the shot is coming from the top
		if (to_bounce.angle >= 0) {
			to_bounce.bounces_remaining--;
			bounced = true;
			to_bounce.posy = y_up_ * 2 - to_bounce.posy;
			to_bounce.angle = -to_bounce.angle;
		}
	}
	//the shot trajectory intersects the south wall
	if (doIntersect(shot_before, shot_now, wall_SW, wall_SE)) {
		//if the shot is coming from the bottom
		if (to_bounce.angle <= 0) {
			to_bounce.bounces_remaining--;
			bounced = true;
			to_bounce.posy = (y_up_ + y_span_) * 2 - to_bounce.posy;
			to_bounce.angle = -to_bounce.angle;
		}
	}
	return bounced;
}

/*
predict shots for bots; takes in positions of two players and returns whether the line segment between the players is obstructed by walls.
*/
bool Wall::bot_shot_predictor(Player p1, Player p2) {
	//create points based on player locations
	Point point_1 = Point(p1.get_location().first, p1.get_location().second);
	Point point_2 = Point(p2.get_location().first, p2.get_location().second);

	//if the line segment intersect one of the borders of any wall then the shot is obstructed
	for (int i = 0; i < walls.size(); i++) {
		Point wall_NW = Point(walls[i].x_left_, walls[i].y_up_);
		Point wall_NE = Point(walls[i].x_left_ + walls[i].x_span_, walls[i].y_up_);
		Point wall_SW = Point(walls[i].x_left_, walls[i].y_up_ + walls[i].y_span_);
		Point wall_SE = Point(walls[i].x_left_ + walls[i].x_span_, walls[i].y_up_ + walls[i].y_span_);
		if (doIntersect(point_1, point_2, wall_NW, wall_NE) || doIntersect(point_1, point_2, wall_NW, wall_SW)
			|| doIntersect(point_1, point_2, wall_SW, wall_SE) || doIntersect(point_1, point_2, wall_NE, wall_SE)) {
			return true;
		}
	}
	return false;
}

/*
add 4 wall segments into the level representing the four sides of the level, "boxing" the player in.
*/
void Wall::add_boundary() {
	//top wall
	walls.push_back(WallSegment(0, 0, level_width_multiplier * wall_width, wall_width));
	//bottom wall
	walls.push_back(WallSegment(0, (level_height_multiplier - 1) * wall_width, level_width_multiplier * wall_width, wall_width));
	//left wall
	walls.push_back(WallSegment(0, wall_width, wall_width, (level_height_multiplier - 2) * wall_width));
	//right wall
	walls.push_back(WallSegment((level_width_multiplier - 1) * wall_width, wall_width, wall_width, (level_height_multiplier - 2) * wall_width));
	
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
	bool bounced;
	do {
		bounced = false;
		for (int i = 0; i < shots_in_level.shots_in_level.size(); i++) {
			for (int j = 0; j < walls.size(); j++) {
				if (walls[j].bounce_shot(shots_in_level.shots_in_level[i])) {
					bounced = true;
				}
				//if the shot has no bounces left and its index is not already in the to_remove array add its index.
				if (shots_in_level.shots_in_level[i].bounces_remaining <= 0 && std::find(to_remove.begin(), to_remove.end(), i) == to_remove.end()) {
					to_remove.push_back(i);
				}
			}
		}
	} while (bounced);
	//remove all shots with the indices in the to_remove array; notice the backward iteration since deleting an elements shifts the indices of all those behind it.
	for (int i = to_remove.size() - 1; i > -1; i--) {
		shots_in_level.shots_in_level.erase(shots_in_level.shots_in_level.begin() + to_remove[i]);
	}
}

/*
resolves collision between the player and the walls in the level; calls collision_handler function of individual wall segments.
*/
void Wall::collision_resolver(Player &player_moving) {
	bool collided;
	do {
		collided = false;
		for (int i = 0; i < walls.size(); i++) {
			if (walls[i].collision_handler(player_moving)) {
				collided = true;
			}
		}
	} while (collided);
}

/*
randomly generates walls in the level. Generates the specified amount of wall segments while ensuring that none of the walls overlap with each other,
spawn near the player spawns or block off the players by splitting the map into two.
*/
void Wall::random_level_generator(int wall_count) {
	//count how many walls have been generated so far.
	int generated_count = 0;
	while (generated_count < wall_count) {
		//roll to determine whether a horizontal or vertical wall is generated.
		int hor_vert = rand() % 100;
		int newx = (rand() % (level_width_multiplier - 2) + 1) * wall_width;
		int newy = (rand() % (level_height_multiplier - 2) + 1) * wall_width;
		int newwidth;
		int newheight;
		//horizontal wall
		if (hor_vert < 50) {
			newwidth = wall_width;
			newheight = (rand() % (level_width_multiplier / 3) + 2) * wall_width;
		}
		//vertical wall
		else {
			newwidth = (rand() % (level_height_multiplier / 3) + 2) * wall_width;
			newheight = wall_width;
		}
		//only add the wall if it does not intersect with any existing walls; otherwise reroll the wall parameters.
		if (!intersect_with_spawn(newx, newy, newwidth, newheight)) {
			add_wall(newx, newy, newwidth, newheight);
			//if the addition of the current wall splits the map, remove it and reroll the wall parameters.
			if (closed_path_checker()) {
				walls.pop_back();
			}
			//increment the counter; a new wall has been successfully generated
			else {
				generated_count++;
			}
		}
	}
}

/*
checks whether there is a valid path between the two players. Uses a maze traversal algorithm.
*/
bool Wall::closed_path_checker() {
	//start from bottom left hand corner, hug the right wall
	int current_x = 1;
	int current_y = level_height_multiplier - 2;
	direction facing = EAST;
	while (true) {
		switch (facing) {
		//checks valid directions one by one; there is no convienient "can go forward" check as in CS125 labs so these disgusting nested if statements
		//are necessary.
		//e.g. facing east, first check south (right), then check east (front), then check north (left), then turn back if its a dead end
		//same for the other 3 cases.
		case EAST: 
			if (intersect(wall_width * current_x, wall_width * (current_y + 1), wall_width, wall_width)) {
				if (intersect(wall_width * (current_x + 1), wall_width * current_y, wall_width, wall_width)) {
					if (intersect(wall_width * current_x, wall_width * (current_y - 1), wall_width, wall_width)) {
						current_x--;
						facing = WEST;
					}
					else {
						current_y--;
						facing = NORTH;
					}
				}
				else {
					current_x++;
					facing = EAST;
				}
			}
			else {
				current_y++;
				facing = SOUTH;
			}
			break;
		case NORTH:
			if (intersect(wall_width * (current_x + 1), wall_width * current_y, wall_width, wall_width)) {
				if (intersect(wall_width * current_x, wall_width * (current_y - 1), wall_width, wall_width)) {
					if (intersect(wall_width * (current_x - 1), wall_width * current_y, wall_width, wall_width)) {
						current_y++;
						facing = SOUTH;
					}
					else {
						current_x--;
						facing = WEST;
					}
				}
				else {
					current_y--;
					facing = NORTH;
				}
			}
			else {
				current_x++;
				facing = EAST;
			}
			break;
		case WEST:
			if (intersect(wall_width * current_x, wall_width * (current_y - 1), wall_width, wall_width)) {
				if (intersect(wall_width * (current_x - 1), wall_width * current_y, wall_width, wall_width)) {
					if (intersect(wall_width * current_x, wall_width * (current_y + 1), wall_width, wall_width)) {
						current_x++;
						facing = EAST;
					}
					else {
						current_y++;
						facing = SOUTH;
					}
				}
				else {
					current_x--;
					facing = WEST;
				}
			}
			else {
				current_y--;
				facing = NORTH;
			}
			break;
		case SOUTH:
			if (intersect(wall_width * (current_x - 1), wall_width * current_y, wall_width, wall_width)) {
				if (intersect(wall_width * current_x, wall_width * (current_y + 1), wall_width, wall_width)) {
					if (intersect(wall_width * (current_x + 1), wall_width * current_y, wall_width, wall_width)) {
						current_y--;
						facing = NORTH;
					}
					else {
						current_x++;
						facing = EAST;
					}
				}
				else {
					current_y++;
					facing = SOUTH;
				}
			}
			else {
				current_x--;
				facing = WEST;
			}
		}
		if (current_x == 1 && current_y == level_height_multiplier - 2) {
			return true;
		}
		if (current_x == level_width_multiplier - 2 && current_y == 1) {
			return false;
		}
	}
}

/*
check whether the given wall segment intersects with any existing wall segments.
*/
bool Wall::intersect(int newx, int newy, int newwidth, int newheight) {
	//create points defining the new wall segment
	Point new_wall_1 = Point(newx, newy);
	Point new_wall_2 = Point(newx + newwidth, newy + newheight);
	for (int i = 0; i < walls.size(); i++) {
		//create points defining existing wall segments
		Point current_wall_1 = Point(walls[i].x_left_, walls[i].y_up_);
		Point current_wall_2 = Point(walls[i].x_left_ + walls[i].x_span_, walls[i].y_up_ + walls[i].y_span_);
		if (rectOverlap(new_wall_1, new_wall_2, current_wall_1, current_wall_2)) {
			return true;
		}
	}
	return false;
}

/*
check whether the given wall segment intersects with any existing wall segments and the player spawn boxes.
*/
bool Wall::intersect_with_spawn(int newx, int newy, int newwidth, int newheight) {
	//create points defining the new wall segment
	Point new_wall_1 = Point(newx, newy);
	Point new_wall_2 = Point(newx + newwidth, newy + newheight);
	for (int i = 0; i < walls.size(); i++) {
		//create points defining existing wall segments
		Point current_wall_1 = Point(walls[i].x_left_, walls[i].y_up_);
		Point current_wall_2 = Point(walls[i].x_left_ + walls[i].x_span_, walls[i].y_up_ + walls[i].y_span_);
		if (rectOverlap(new_wall_1, new_wall_2, current_wall_1, current_wall_2)) {
			return true;
		}
	}
	//create points defining player spawn boxes
	Point p1_spawn_1 = Point(wall_width, (level_height_multiplier - 4) * wall_width);
	Point p1_spawn_2 = Point(wall_width * 4, (level_height_multiplier - 1) * wall_width);
	Point p2_spawn_1 = Point((level_width_multiplier - 4) * wall_width, wall_width);
	Point p2_spawn_2 = Point((level_width_multiplier - 1) * wall_width, wall_width * 4);
	if (rectOverlap(new_wall_1, new_wall_2, p1_spawn_1, p1_spawn_2) || rectOverlap(new_wall_1, new_wall_2, p2_spawn_1, p2_spawn_2)) {
		return true;
	}
	return false;
}

/*
clears the level; removes all non-boundary walls
*/
void Wall::clear_level() {
	while (walls.size() > 4) {
		walls.pop_back();
	}
}