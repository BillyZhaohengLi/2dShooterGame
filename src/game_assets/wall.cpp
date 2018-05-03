#include "wall.h"
/*
constructor; create a wall segment at the specified location with specified width and height.
*/
Wall::WallSegment::WallSegment(int xpos, int ypos, int xspan, int yspan) {
	xpos_ = xpos;
	xspan_ = xspan;
	ypos_ = ypos;
	yspan_ = yspan;
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
	Point wall_NW = Point(xpos_, ypos_);
	Point wall_NE = Point(xpos_ + xspan_, ypos_);
	Point wall_SW = Point(xpos_, ypos_ + yspan_);
	Point wall_SE = Point(xpos_ + xspan_, ypos_ + yspan_);
	//the player collides with the north wall
	if (line_segment_circle(wall_NW, wall_NE, player_location, kPlayerRadius)) {
		//if circle is above wall
		if (p_y < ypos_) {
			collided = true;
			//touching wall at corner; trig knowledge alert
			//resolves the collision by pushing the player in the direction that requires the least distance moved to resolve the collision.
			if (p_x < xpos_) {
				double x_dif = xpos_ - p_x;
				double y_dif = ypos_ - p_y;
				double angle_ = atan(y_dif / x_dif);
				double new_x = xpos_ - kPlayerRadius * cos(angle_) - kEpsilon;
				double new_y = ypos_ - kPlayerRadius * sin(angle_) - kEpsilon;
				player_moving.set_location(new_x, new_y);
			}
			else if (p_x > xpos_ + xspan_) {
				double x_dif = p_x - xpos_ - xspan_;
				double y_dif = ypos_ - p_y;
				double angle_ = atan(y_dif / x_dif);
				double new_x = xpos_ + xspan_ + kPlayerRadius * cos(angle_) + kEpsilon;
				double new_y = ypos_ - kPlayerRadius * sin(angle_) - kEpsilon;
				player_moving.set_location(new_x, new_y);
			}
			//touching wall at side. Pushes the player outwards.
			else {
				player_moving.set_location(p_x, ypos_ - kPlayerRadius - kEpsilon);
			}
		}
	}
	//the player collides with the south wall
	if (line_segment_circle(wall_SW, wall_SE, player_location, kPlayerRadius)) {
		//if circle is below wall
		if (p_y > ypos_ + yspan_) {
			collided = true;
			//touching wall at corner; trig knowledge alert
			if (p_x < xpos_) {
				double x_dif = xpos_ - p_x;
				double y_dif = p_y - ypos_ - yspan_;
				double angle_ = atan(y_dif / x_dif);
				double new_x = xpos_ - kPlayerRadius * cos(angle_) - kEpsilon;
				double new_y = ypos_ + yspan_ + kPlayerRadius * sin(angle_) + kEpsilon;
				player_moving.set_location(new_x, new_y);
			}
			else if (p_x > xpos_ + xspan_) {
				double x_dif = p_x - xpos_ - xspan_;
				double y_dif = p_y - ypos_ - yspan_;
				double angle_ = atan(y_dif / x_dif);
				double new_x = xpos_ + xspan_ + kPlayerRadius * cos(angle_) + kEpsilon;
				double new_y = ypos_ + yspan_ + kPlayerRadius * sin(angle_) + kEpsilon;
				player_moving.set_location(new_x, new_y);
			}
			else {
				player_moving.set_location(p_x, ypos_ + yspan_ + kPlayerRadius + kEpsilon);
			}
		}
	}
	//the player collides with the west wall
	if (line_segment_circle(wall_NW, wall_SW, player_location, kPlayerRadius)) {
		//if circle is left of wall
		if (p_x < xpos_) {
			collided = true;
			if (p_y < ypos_) {
				double x_dif = xpos_ - p_x;
				double y_dif = ypos_ - p_y;
				double angle_ = atan(y_dif / x_dif);
				double new_x = xpos_ - kPlayerRadius * cos(angle_) - kEpsilon;
				double new_y = ypos_ - kPlayerRadius * sin(angle_) - kEpsilon;
				player_moving.set_location(new_x, new_y);
			} else if (p_y > ypos_ + yspan_) {
				double x_dif = xpos_ - p_x;
				double y_dif = p_y - ypos_ - yspan_;
				double angle_ = atan(y_dif / x_dif);
				double new_x = xpos_ - kPlayerRadius * cos(angle_) - kEpsilon;
				double new_y = ypos_ + yspan_ + kPlayerRadius * sin(angle_) + kEpsilon;
				player_moving.set_location(new_x, new_y);
			}
			else {
				player_moving.set_location(xpos_ - kPlayerRadius - kEpsilon, p_y);
			}
		}
	}
	//the player collides with the east wall
	if (line_segment_circle(wall_NE, wall_SE, player_location, kPlayerRadius)) {
		//if circle is right of wall
		if (p_x > xpos_ + xspan_) {
			collided = true;
			if (p_y < ypos_) {
				double x_dif = p_x - xpos_ - xspan_;
				double y_dif = ypos_ - p_y;
				double angle_ = atan(y_dif / x_dif);
				double new_x = xpos_ + xspan_ + kPlayerRadius * cos(angle_) + kEpsilon;
				double new_y = ypos_ - kPlayerRadius * sin(angle_) - kEpsilon;
				player_moving.set_location(new_x, new_y);
			}
			else if (p_y > ypos_ + yspan_) {
				double x_dif = p_x - xpos_ - xspan_;
				double y_dif = p_y - ypos_ - yspan_;
				double angle_ = atan(y_dif / x_dif);
				double new_x = xpos_ + xspan_ + kPlayerRadius * cos(angle_) + kEpsilon;
				double new_y = ypos_ + yspan_ + kPlayerRadius * sin(angle_) + kEpsilon;
				player_moving.set_location(new_x, new_y);
			}
			else {
				player_moving.set_location(xpos_ + xspan_ + kPlayerRadius + kEpsilon, p_y);
			}
		}
	}
	return collided;
}

/*
handles collision between a wall segment and an individual shot. If the shot hits the wall "bounces" the shot in an appropriate direction.
*/
pair<bool, int> Wall::WallSegment::bounce_shot(ShotInLevel::Shot& to_bounce) {
	if (to_bounce.bounces_remaining_ == 0) {
		return pair<bool, int> (false, kNotBounced);
	}
	bool bounced = false;
	int bounced_direction = kNotBounced;
	//generate 6 points; two based on the shot's current and previous locations, four based on the four corners of the wall.
	//check for collision between the shot and the four sides defined by the four points of the wall segment.
	//if a bounce occurs, the remaining bounces for the shot is decreased by one.
	Point shot_before = Point(to_bounce.xpos_ - kShotLength * cos(to_bounce.angle_), 
		to_bounce.ypos_ - kShotLength * sin(to_bounce.angle_));
	Point shot_now = Point(to_bounce.xpos_, to_bounce.ypos_);
	Point wall_NW = Point(xpos_, ypos_);
	Point wall_NE = Point(xpos_ + xspan_, ypos_);
	Point wall_SW = Point(xpos_, ypos_ + yspan_);
	Point wall_SE = Point(xpos_ + xspan_, ypos_ + yspan_);

	//if the shot trajectory intersects the west wall and comes from the left
	if (doIntersect(shot_before, shot_now, wall_NW, wall_SW) && 
		(to_bounce.angle_ >= -kPi / 2 && to_bounce.angle_ <= kPi / 2)) {
		to_bounce.bounces_remaining_--;
		bounced = true;
		bounced_direction = kBouncedLeft;
		to_bounce.xpos_ = xpos_ * 2 - to_bounce.xpos_;
		if (to_bounce.angle_ <= 0) {
			to_bounce.angle_ = -kPi - to_bounce.angle_;
		}
		else {
			to_bounce.angle_ = kPi - to_bounce.angle_;
		}
	}
	//if the shot trajectory intersects the east wall and comes from the right
	else if (doIntersect(shot_before, shot_now, wall_NE, wall_SE) && 
		(to_bounce.angle_ <= -kPi / 2 || to_bounce.angle_ >= kPi / 2)) {
		to_bounce.bounces_remaining_--;
		bounced = true;
		bounced_direction = kBouncedRight;
		to_bounce.xpos_ = (xpos_ + xspan_) * 2 - to_bounce.xpos_;
		if (to_bounce.angle_ <= -kPi / 2) {
			to_bounce.angle_ = -kPi - to_bounce.angle_;
		}
		else {
			to_bounce.angle_ = kPi - to_bounce.angle_;
		}
	}
	//if the shot trajectory intersects the north wall and comes from the top
	else if (doIntersect(shot_before, shot_now, wall_NW, wall_NE) && (to_bounce.angle_ >= 0)) {
		to_bounce.bounces_remaining_--;
		bounced = true;
		bounced_direction = kBouncedTop;
		to_bounce.ypos_ = ypos_ * 2 - to_bounce.ypos_;
		to_bounce.angle_ = -to_bounce.angle_;
	}
	//if the shot trajectory intersects the south wall and comes from the bottom
	else if (doIntersect(shot_before, shot_now, wall_SW, wall_SE) && (to_bounce.angle_ <= 0)) {
		to_bounce.bounces_remaining_--;
		bounced = true;
		bounced_direction = kBouncedBottom;
		to_bounce.ypos_ = (ypos_ + yspan_) * 2 - to_bounce.ypos_;
		to_bounce.angle_ = -to_bounce.angle_;
	}
	return pair<bool, int> (bounced, bounced_direction);
}

/*
predict shots for bots; takes in positions of two players and returns whether the line segment between the players is obstructed by walls.
*/
bool Wall::player_path_obstructed(Player p1, Player p2) {
	//create points based on player locations
	Point point_1 = Point(p1.get_location().first, p1.get_location().second);
	Point point_2 = Point(p2.get_location().first, p2.get_location().second);

	//if the line segment intersect one of the borders of any wall then the shot is obstructed
	for (int i = 0; i < walls.size(); i++) {
		Point wall_NW = Point(walls[i].xpos_, walls[i].ypos_);
		Point wall_NE = Point(walls[i].xpos_ + walls[i].xspan_, walls[i].ypos_);
		Point wall_SW = Point(walls[i].xpos_, walls[i].ypos_ + walls[i].yspan_);
		Point wall_SE = Point(walls[i].xpos_ + walls[i].xspan_, walls[i].ypos_ + walls[i].yspan_);
		if (doIntersect(point_1, point_2, wall_NW, wall_NE) || 
			doIntersect(point_1, point_2, wall_NW, wall_SW)	|| 
			doIntersect(point_1, point_2, wall_SW, wall_SE) || 
			doIntersect(point_1, point_2, wall_NE, wall_SE)) {
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
	walls.push_back(WallSegment(0, 0, kLevelWidthMultiplier * kWallWidth, kWallWidth));
	//bottom wall
	walls.push_back(WallSegment(0, (kLevelHeightMultiplier - 1) * 
		kWallWidth, kLevelWidthMultiplier * kWallWidth, kWallWidth));
	//left wall
	walls.push_back(WallSegment(0, kWallWidth, kWallWidth, (kLevelHeightMultiplier - 2) * kWallWidth));
	//right wall
	walls.push_back(WallSegment((kLevelWidthMultiplier - 1) * 
		kWallWidth, kWallWidth, kWallWidth, (kLevelHeightMultiplier - 2) * kWallWidth));
	
}

/*
add a new wall into the level.
*/
void Wall::add_wall(int xpos, int ypos, int xspan, int yspan) {
	walls.push_back(WallSegment(xpos, ypos, xspan, yspan));
}

/*
draw all walls in the level calling ofDrawRectangle_ for each wall segment.
*/
void Wall::draw_all_walls() {
	ofSetColor(ofColor::black);
	for (WallSegment i : walls) {
		ofDrawRectangle(i.xpos_, i.ypos_, i.xspan_, i.yspan_);
	}
}

/*
bounces shots off walls in a level. Calls bounce_shots of each wall segment for each individual shot in shots_in_level.
*/
void Wall::bounce_shots(ShotInLevel &shots_in_level) {
	//vector containing indices of the shots which have no bounces remaining; they will be deleted after the bouncing is finished.
	//the algorithm below is rather complicated; refer to the detailed explanation in the explanations.txt file in the source folder.
	vector<int> to_remove;
	//repeat resolving collisions until no shots are colliding with walls
	bool bounced;
	for (int i = 0; i < shots_in_level.shots_in_level.size(); i++) {
		//take note of the shot's position before any modifications; this is used to reset bounces if things go ugly
		pair<pair<double, double>, pair<double, int>> parameters = 
			shots_in_level.get_shot_parameters(i);

		//previous bounced direction (see (2) in the diagram in the explanations.txt file)
		int bounce_direction = kNotBounced;

		//whether to traverse the wall array from the back to handle collisions (takes care of bugs caused by resolving collisions of wall segments in the wrong order)
		bool reverse_array = false;

		//how many times this shot has been bounced (see (3) in the diagram in the explanations.txt file)
		int bounce_times = 0;

		//the wall id that the shot just bounced off of. Mathematically proven that a shot should not bounce off the same wall two times consecutively; used to break loops.
		//(see(4) in the diagram in the explanations.txt file)
		int bounced_wall_id = -1;
		do {
			//if a shot has already bounced twice, then it shouldn't bounce a third time; break a loop (see diagram).
			if (bounce_times >= 2) {
				break;
			}
			bounced = false;
			for (int j = 0; j < walls.size(); j++) {
				//do not resolve collision for a wall that the shot had already collided with in the same frame.
				if (j == bounced_wall_id) {
					continue;
				}
				pair<bool, int> bounce_results = walls[j].bounce_shot(shots_in_level.shots_in_level[i]);
				if (bounce_results.first) {
					//increment times bounced and set the last wall bounced to this one
					bounce_times++;
					bounced_wall_id = j;
					//if a shot's consecutive bounces are in opposite cardinal direction (top and bottom, left and right), then something's wrong (see diagram);
					//reset the shot, reverse the order of traversal of the wallsement array and resolve the collisions again.
					if (bounce_results.second == -bounce_direction) {
						reverse_array = true;
						bounced = false;
						shots_in_level.reset_shot(i, parameters);
						break;
					}
					bounced = true;
					//record the bounced direction
					bounce_direction = bounce_results.second;
				}
			}
		} while (bounced);
		//resolve bounces in reverse order if needed; the process here is completely analogus to what happens above.
		if (reverse_array) {
			int bounce_times = 0;
			int bounced_wall_id = -1;
			do {
				if (bounce_times >= 2) {
					break;
				}
				bounced = false;
				for (int j = walls.size() - 1; j >= 0; j--) {
					if (j == bounced_wall_id) {
						continue;
					}
					pair<bool, int> bounce_results = walls[j].bounce_shot(shots_in_level.shots_in_level[i]);
					if (bounce_results.first) {
						bounced_wall_id = j;
						bounce_times++;
						bounced = true;
					}
				}
			} while (bounced);
		}

		//if the shot has no bounces left and its index is not already in the to_remove array add its index.
		if (shots_in_level.shots_in_level[i].bounces_remaining_ <= 0 && 
			std::find(to_remove.begin(), to_remove.end(), i) == to_remove.end()) {
			to_remove.push_back(i);
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
		int newx = (rand() % (kLevelWidthMultiplier - 2) + 1) * kWallWidth;
		int newy = (rand() % (kLevelHeightMultiplier - 2) + 1) * kWallWidth;
		int newwidth;
		int newheight;
		//horizontal wall
		if (hor_vert < 50) {
			newwidth = kWallWidth;
			newheight = (rand() % (kLevelWidthMultiplier / 3) + 2) * kWallWidth;
		}
		//vertical wall
		else {
			newwidth = (rand() % (kLevelHeightMultiplier / 3) + 2) * kWallWidth;
			newheight = kWallWidth;
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
	int current_y = kLevelHeightMultiplier - 2;
	Direction facing = EAST;
	while (true) {
		switch (facing) {
		//checks valid directions one by one; there is no convienient "can go forward" check as in CS125 labs so these disgusting nested if statements
		//are necessary.
		//e.g. facing east, first check south (right), then check east (front), then check north (left), then turn back if its a dead end
		//same for the other 3 cases.
		case EAST: 
			if (intersect(kWallWidth * current_x, kWallWidth * (current_y + 1), kWallWidth, kWallWidth)) {
				if (intersect(kWallWidth * (current_x + 1), kWallWidth * current_y, kWallWidth, kWallWidth)) {
					if (intersect(kWallWidth * current_x, kWallWidth * (current_y - 1), kWallWidth, kWallWidth)) {
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
			if (intersect(kWallWidth * (current_x + 1), kWallWidth * current_y, kWallWidth, kWallWidth)) {
				if (intersect(kWallWidth * current_x, kWallWidth * (current_y - 1), kWallWidth, kWallWidth)) {
					if (intersect(kWallWidth * (current_x - 1), kWallWidth * current_y, kWallWidth, kWallWidth)) {
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
			if (intersect(kWallWidth * current_x, kWallWidth * (current_y - 1), kWallWidth, kWallWidth)) {
				if (intersect(kWallWidth * (current_x - 1), kWallWidth * current_y, kWallWidth, kWallWidth)) {
					if (intersect(kWallWidth * current_x, kWallWidth * (current_y + 1), kWallWidth, kWallWidth)) {
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
			if (intersect(kWallWidth * (current_x - 1), kWallWidth * current_y, kWallWidth, kWallWidth)) {
				if (intersect(kWallWidth * current_x, kWallWidth * (current_y + 1), kWallWidth, kWallWidth)) {
					if (intersect(kWallWidth * (current_x + 1), kWallWidth * current_y, kWallWidth, kWallWidth)) {
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
		if (current_x == 1 && current_y == kLevelHeightMultiplier - 2) {
			return true;
		}
		if (current_x == kLevelWidthMultiplier - 2 && current_y == 1) {
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
		Point current_wall_1 = Point(walls[i].xpos_, walls[i].ypos_);
		Point current_wall_2 = Point(walls[i].xpos_ + walls[i].xspan_, walls[i].ypos_ + walls[i].yspan_);
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
		Point current_wall_1 = Point(walls[i].xpos_, walls[i].ypos_);
		Point current_wall_2 = Point(walls[i].xpos_ + walls[i].xspan_, walls[i].ypos_ + walls[i].yspan_);
		if (rectOverlap(new_wall_1, new_wall_2, current_wall_1, current_wall_2)) {
			return true;
		}
	}
	//create points defining player spawn boxes
	Point p1_spawn_1 = Point(kWallWidth, (kLevelHeightMultiplier - 4) * kWallWidth);
	Point p1_spawn_2 = Point(kWallWidth * 4, (kLevelHeightMultiplier - 1) * kWallWidth);
	Point p2_spawn_1 = Point((kLevelWidthMultiplier - 4) * kWallWidth, kWallWidth);
	Point p2_spawn_2 = Point((kLevelWidthMultiplier - 1) * kWallWidth, kWallWidth * 4);
	if (rectOverlap(new_wall_1, new_wall_2, p1_spawn_1, p1_spawn_2) || 
		rectOverlap(new_wall_1, new_wall_2, p2_spawn_1, p2_spawn_2)) {
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

/*
serialized string format of all wall segments in the level. Used in multiplayer; walls are generated at the host server and sent to the client.
*/
string Wall::serialized_string() {
	string to_return;
	//the boundary walls are omitted as they are the same for any instance of the program, hence the for loop starting at 4.
	for (int i = 4; i < walls.size(); i++) {
		to_return += (to_string(walls[i].xpos_) + kSmallDelimiter + to_string(walls[i].ypos_) +
			kSmallDelimiter + to_string(walls[i].xspan_) + kSmallDelimiter + 
			to_string(walls[i].yspan_) + kSmallDelimiter);
	}
	return to_return;
}

/*
deserialize an update message from the host server and adds the appropriate wall segments to the wall object in the client program.
*/
void Wall::deserialize_update_message(string message) {
	if (walls.size() <= 4) {
		vector<string> message_array = split(message.substr(0, message.size() - 1), kSmallDelimiter);
		for (int i = 0; i < message_array.size(); i += 4) {
			WallSegment temp = WallSegment(stoi(message_array[i]), stoi(message_array[i + 1]), 
				stoi(message_array[i + 2]), stoi(message_array[i + 3]));
			walls.push_back(temp);
		}
	}
}
