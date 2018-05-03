#include "shot.h"
/*
constructor; creates a shot at the designated x and y position with a trajectory defined by an initial angle_.
*/
ShotInLevel::Shot::Shot(double x, double y, double initial_angle_) {
	xpos_ = x;
	ypos_ = y;
	angle_ = initial_angle_;
	bounces_remaining_ = kShotBounces;
}

/*
move the shot in the direction defined by its angle_; called every update.
*/
void ShotInLevel::Shot::move() {
	xpos_ = xpos_ + kShotLength * cos(angle_);
	ypos_ = ypos_ + kShotLength * sin(angle_);
}

/*
draw the shot using ofDrawCircle.
*/
void ShotInLevel::Shot::draw_shot() {
	ofSetColor(ofColor::red);
	ofDrawCircle(xpos_, ypos_, kShotRadius);
}


/*
returns an ugly data structure containing the shot parameters of this shot.
nothing is actually done with the contents of the data structure; it is only used to reset the shot by being fed back into the shot
in the reset_shot method below.
*/
pair<pair<double, double>, pair<double, int>> ShotInLevel::Shot::get_shot_parameters() {
	return pair<pair<double, double>, pair<double, int>>(pair<double, double>(xpos_, ypos_), 
		pair<double, int>(angle_, bounces_remaining_));
}

/*
set the shot's parameters based on the index and the aforementioned data structure in get_shot_parameters.
*/
void ShotInLevel::Shot::reset_shot(pair<pair<double, double>, pair<double, int>> parameters) {
	xpos_ = parameters.first.first;
	ypos_ = parameters.first.second;
	angle_ = parameters.second.first;
	bounces_remaining_ = parameters.second.second;
}


/*
add a shot at the specified location traveling in a specified angle_. Calls the Shot constructor.
*/
void ShotInLevel::add_shot(double xpos, double ypos, double initial_angle_) {
	shots_in_level.push_back(Shot(xpos, ypos, initial_angle_));
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
		if (sqrt(x_dist * x_dist + y_dist * y_dist) < (kPlayerRadius + kShotRadius)) {
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

/*
serialized string format of all shots in the level. Used in multiplayer; shots are managed at the host server and sent to the client.
*/
string ShotInLevel::serialized_string() {
	string to_return = kBigDelimiter;
	for (int i = 0; i < shots_in_level.size(); i++) {
		to_return += (to_string(shots_in_level[i].xpos_) + kSmallDelimiter + 
			to_string(shots_in_level[i].ypos_) + kSmallDelimiter + 
			to_string(shots_in_level[i].angle_) + kSmallDelimiter);
	}
	return to_return;
}

/*
deserialize an update message from the host server and adds the appropriate shots to the ShotsInLevel in the client program.
*/
void ShotInLevel::deserialize_update_message(string message) {
	shots_in_level.clear();
	vector<string> message_array = split(message.substr(0, message.size() - 1), kSmallDelimiter);
	if (message_array.size() % 3 == 0) {
		for (int i = 0; i < message_array.size(); i += 3) {
			Shot temp = Shot(stod(message_array[i]), stod(message_array[i + 1]), 
				stod(message_array[i + 2]));
			shots_in_level.push_back(temp);
		}
	}
}

/*
returns an ugly data structure containing the shot parameters of the (shot_id)th shot in the level in terms of array index.
nothing is actually done with the contents of the data structure; it is only used to reset the shot by being fed back into the reset_shot
method below this if needed in the shot-wall collision algorithm.
if the shot is not found returns all 0s.
*/
pair<pair<double, double>, pair<double, int>> ShotInLevel::get_shot_parameters(int shot_id) {
	pair<pair<double, double>, pair<double, int>> temp;
	for (int i = 0; i < shots_in_level.size(); i++) {
		if (shot_id == i) {
			return shots_in_level[i].get_shot_parameters();
		}
	}
	return temp;
}

/*
set a shot's parameters based on the index and the aforementioned data structure in get_shot_parameters.
*/
void ShotInLevel::reset_shot(int shot_id, pair<pair<double, double>, pair<double, int>> parameters) {
	for (int i = 0; i < shots_in_level.size(); i++) {
		if (shot_id == i) {
			shots_in_level[i].reset_shot(parameters);
		}
	}
}
