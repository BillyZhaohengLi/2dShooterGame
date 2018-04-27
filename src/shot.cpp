#include "shot.h"
/*
constructor; creates a shot at the designated x and y position with a trajectory defined by an initial angle.
*/
ShotInLevel::Shot::Shot(double x, double y, double initial_angle) {
	xpos_ = x;
	ypos_ = y;
	angle = initial_angle;
	bounces_remaining = shot_bounces;
}

/*
move the shot in the direction defined by its angle; called every update.
*/
void ShotInLevel::Shot::move() {
	xpos_ = xpos_ + shot_length * cos(angle);
	ypos_ = ypos_ + shot_length * sin(angle);
}

/*
draw the shot using ofDrawCircle.
*/
void ShotInLevel::Shot::draw_shot() {
	ofSetColor(255, 0, 0);
	ofDrawCircle(xpos_, ypos_, shot_radius);
}

/*
add a shot at the specified location traveling in a specified angle. Calls the Shot constructor.
*/
void ShotInLevel::add_shot(double xpos, double ypos, double initial_angle) {
	shots_in_level.push_back(Shot(xpos, ypos, initial_angle));
}

/*
moves all shots in the level; calls the move function for each individual shot.
*/
void ShotInLevel::move() {
	for (int i = 0; i < shots_in_level.size(); i++) {
		shots_in_level[i].move();
	}
}

/*
draws all shots in the level; calls the draw function for each individual shot.
*/
void ShotInLevel::draw_shot() {
	for (int i = 0; i < shots_in_level.size(); i++) {
		shots_in_level[i].draw_shot();
	}
}

/*
checks whether a player is hit by any given shot within the level. If the player gets hit call the kill_player function of the player.
*/
void ShotInLevel::hit_player(Player &player_to_check) {
	pair<double, double> player_location = player_to_check.get_location();
	//easy pre-calc content; the player is hit by a shot if the distance between the player and the shot is less than the sum of the two radii.
	for (int i = 0; i < shots_in_level.size(); i++) {
		double x_dist = shots_in_level[i].xpos_ - player_location.first;
		double y_dist = shots_in_level[i].ypos_ - player_location.second;
		if (sqrt(x_dist * x_dist + y_dist * y_dist) < (player_radius + shot_radius)) {
			player_to_check.kill_player();
		}
	}
}

/*
removes all current shots in the level.
*/
void ShotInLevel::clear_shots() {
	shots_in_level.clear();
}