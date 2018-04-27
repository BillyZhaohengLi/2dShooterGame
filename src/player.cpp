#include "player.h"
/*
constructor; create a player at the specified x and y coordinates with color rgb.
*/
Player::Player(double x, double y, int palette, bool bot, string text) {
	xpos = x;
	ypos = y;
	set_color(palette);
	alive = true;
	facing = STOP;
	shot_cooldown = 10;
	set_name(text);
	is_bot = bot;
	facing_x = 0;
	facing_y = 0;
	change_direction_cd = 0;
}

/*
returns the player's location as a pair of doubles.
*/
pair<double, double> Player::get_location() {
	return pair<double, double>(xpos, ypos);
}

/*
set's the player's location; used to handle collisions with walls
*/
void Player::set_location(double new_x, double new_y) {
	xpos = new_x;
	ypos = new_y;
}

/*
returns whether the player is alive.
*/
bool Player::isalive() {
	return alive;
}

/*
change the direction the player is facing; called when the player enters some sort of combination of WASD keys.
*/
void Player::change_direction(direction change_to) {
	facing = change_to;
}

/*
moves the player. Called at every update function; modifies player coordinates based on the direction they are facing.
*/
void Player::move() {
	//only move the player if they are alive (duh).
	if (alive) {
		switch (facing) {
		case STOP:
			break;
		case WEST:
			xpos -= player_velocity;
			break;
		case EAST:
			xpos += player_velocity;
			break;
		case NORTH:
			ypos -= player_velocity;
			break;
		case SOUTH:
			ypos += player_velocity;
			break;
		case NORTHWEST:
			xpos -= (player_velocity * (sqrt(2) / 2));
			ypos -= (player_velocity * (sqrt(2) / 2));
			break;
		case NORTHEAST:
			xpos += (player_velocity * (sqrt(2) / 2));
			ypos -= (player_velocity * (sqrt(2) / 2));
			break;
		case SOUTHWEST:
			xpos -= (player_velocity * (sqrt(2) / 2));
			ypos += (player_velocity * (sqrt(2) / 2));
			break;
		case SOUTHEAST:
			xpos += (player_velocity * (sqrt(2) / 2));
			ypos += (player_velocity * (sqrt(2) / 2));
			break;
		}
	}
}

/*
kills the player (sets alive to false). Called when the player gets hit by a shot.
*/
void Player::kill_player() {
	alive = false;
}

/*
revives the player (sets alive to true) at a given location and puts their weapon on cooldown (basically prepared for a new game).
*/
void Player::reset_player(double new_x, double new_y) {
	alive = true;
	shot_cooldown = player_shot_cooldown / 2;
	xpos = new_x;
	ypos = new_y;
}

/*
updates the direction the player is facing (used to draw the player's gun). Has different outcomes based on whether the player is a bot.
*/
void Player::update_player_facing(int mouse_x, int mouse_y, Player opponent) {
	//if the player isn't a bot then the player faces towards the mouse direction
	if (!is_bot) {
		facing_y = mouse_y;
		facing_x = mouse_x;
	}
	//if the player is a bot then the player faces towards their opponent
	else {
		facing_y = opponent.ypos;
		facing_x = opponent.xpos;
	}
}
/*
draws the player using ofDrawCircle.
*/
void Player::draw_player() {
	ofSetColor(red, green, blue);
	name_font.drawStringCentered(name, xpos, ypos - player_radius * 1.8);
	if (alive) {
		ofSetColor(red, green, blue);

		//draw the player circle corresponding with the hitbox
		ofDrawCircle(xpos, ypos, player_radius);
		ofSetColor(0, 0, 0);
		ofSetLineWidth(4);

		//draw a smiley face on the player
		ofDrawCircle(xpos - cos(pi / 4) * player_radius * 0.5, ypos - cos(pi / 4) * player_radius * 0.5, player_radius * 0.2);
		ofDrawCircle(xpos + cos(pi / 4) * player_radius * 0.5, ypos - cos(pi / 4) * player_radius * 0.5, player_radius * 0.2);
		ofDrawLine(xpos - cos(pi / 4) * player_radius * 0.75, ypos + cos(pi / 4) * player_radius * 0.5, xpos - cos(pi / 4) * player_radius * 0.5, ypos + cos(pi / 4) * player_radius * 0.75);
		ofDrawLine(xpos + cos(pi / 4) * player_radius * 0.75, ypos + cos(pi / 4) * player_radius * 0.5, xpos + cos(pi / 4) * player_radius * 0.5, ypos + cos(pi / 4) * player_radius * 0.75);
		ofDrawLine(xpos - cos(pi / 4) * player_radius * 0.5, ypos + cos(pi / 4) * player_radius * 0.75, xpos + cos(pi / 4) * player_radius * 0.5, ypos + cos(pi / 4) * player_radius * 0.75);
		double gun_angle = atan2(facing_y - ypos, facing_x - xpos);
		//draw the gun; if the player is firing add a firing effect.
		if (shot_cooldown >= player_shot_cooldown * 0.9) {
			ofDrawLine(xpos + cos(gun_angle) * player_radius, ypos + sin(gun_angle) * player_radius, xpos + cos(gun_angle) * player_radius * 1.25, ypos + sin(gun_angle) * player_radius * 1.25);
			ofSetColor(255, 255, 0, 128);
			ofDrawCircle(xpos + cos(gun_angle) * player_radius * 1.25, ypos + sin(gun_angle) * player_radius * 1.25, 6);
		}
		else {
			ofDrawLine(xpos + cos(gun_angle) * player_radius, ypos + sin(gun_angle) * player_radius, xpos + cos(gun_angle) * player_radius * 1.5, ypos + sin(gun_angle) * player_radius * 1.5);
		}
	}
	//if the player is dead draw them in black.
	else {
		ofSetColor(red, green, blue);

		//draw the player circle
		ofDrawCircle(xpos, ypos, player_radius);
		ofSetColor(0, 0, 0);
		ofSetLineWidth(3);

		//draw a sad face on the player
		ofDrawLine(xpos - cos(pi / 4) * player_radius * 0.15, ypos - cos(pi / 4) * player_radius * 0.15, xpos - cos(pi / 4) * player_radius * 0.85, ypos - cos(pi / 4) * player_radius * 0.85);
		ofDrawLine(xpos + cos(pi / 4) * player_radius * 0.15, ypos - cos(pi / 4) * player_radius * 0.15, xpos + cos(pi / 4) * player_radius * 0.85, ypos - cos(pi / 4) * player_radius * 0.85);
		ofDrawLine(xpos - cos(pi / 4) * player_radius * 0.15, ypos - cos(pi / 4) * player_radius * 0.85, xpos - cos(pi / 4) * player_radius * 0.85, ypos - cos(pi / 4) * player_radius * 0.15);
		ofDrawLine(xpos + cos(pi / 4) * player_radius * 0.15, ypos - cos(pi / 4) * player_radius * 0.85, xpos + cos(pi / 4) * player_radius * 0.85, ypos - cos(pi / 4) * player_radius * 0.15);
		ofDrawLine(xpos - cos(pi / 4) * player_radius * 0.75, ypos + cos(pi / 4) * player_radius * 0.75, xpos - cos(pi / 4) * player_radius * 0.5, ypos + cos(pi / 4) * player_radius * 0.5);
		ofDrawLine(xpos + cos(pi / 4) * player_radius * 0.75, ypos + cos(pi / 4) * player_radius * 0.75, xpos + cos(pi / 4) * player_radius * 0.5, ypos + cos(pi / 4) * player_radius * 0.5);
		ofDrawLine(xpos - cos(pi / 4) * player_radius * 0.5, ypos + cos(pi / 4) * player_radius * 0.5, xpos + cos(pi / 4) * player_radius * 0.5, ypos + cos(pi / 4) * player_radius * 0.5);
	}
}

/*
fires a shot; returns the angle at which the shot was fired and sets cooldown to a designated value.
*/
double Player::fire_shot() {
	shot_cooldown = player_shot_cooldown;
	return atan2(facing_y - ypos, facing_x - xpos);
}

/*
returns a boolean based on whether the player can fire a shot. True if cooldown is 0; false if otherwise.
*/
bool Player::can_shoot() {
	return shot_cooldown == 0;
}

/*
reduces the player's cooldown by 1 if its not 0. Called every update.
*/
void Player::cooldown_reduce() {
	if (shot_cooldown != 0) {
		shot_cooldown--;
	}
}

/*
set the player's name. Also alters font size based on the new name's length.
*/
void Player::set_name(string new_name) {
	name = new_name;
	if (new_name.length() < 8) {
		name_font.loadFont("verdana.ttf", player_radius * 0.8);
	}
	else if (new_name.length() < 12) {
		name_font.loadFont("verdana.ttf", player_radius * 0.7);
	}
	else {
		name_font.loadFont("verdana.ttf", player_radius * 0.6);
	}
	name_font.setLineHeight(18.0f);
	name_font.setLetterSpacing(1.037);
}

/*
getter for the player's name.
*/
string Player::get_name() {
	return name;
}

/*
sets the player's color via a color palette.
*/
void Player::set_color(int color_palette) {
	switch (color_palette) {
		//red
	case (red_button):
		red = 255;
		blue = 0;
		green = 0;
		break;
		//blue
	case (blue_button):
		red = 0;
		blue = 255;
		green = 0;
		break;
		//green
	case (green_button):
		red = 0;
		blue = 0;
		green = 255;
		break;
		//yellow
	case (yellow_button):
		red = 255;
		blue = 0;
		green = 255;
		break;
		//magenta
	case (magenta_button):
		red = 255;
		blue = 255;
		green = 0;
		break;
		//cyan
	case (cyan_button):
		red = 0;
		blue = 255;
		green = 255;
		break;
	}
}

int Player::get_color() {
	if (red == 255 && green == 0 && blue == 0) {
		return red_color;
	}
	else if (red == 0 && green == 255 && blue == 0) {
		return green_color;
	}
	else if (red == 0 && green == 0 && blue == 255) {
		return blue_color;
	}
	else if (red == 255 && green == 255 && blue == 0) {
		return yellow_color;
	}
	else if (red == 255 && green == 0 && blue == 255) {
		return magenta_color;
	}
	else if (red == 0 && green == 255 && blue == 255) {
		return cyan_color;
	}
	else {
		return -1;
	}
}

pair<int, int> Player::get_facing() {
	return pair<int, int>(facing_x, facing_y);
}

/*
changes the player's direction based on what keys are held down. Has different outcomes based on whether the player is a bot.
*/
void Player::change_direction(bool keydown[255]) {
	//if the player is not a bot change direction according to held keys
	if (!is_bot) {
		int vert_displacement = 0;
		int hor_displacement = 0;
		if (keydown['W']) {
			vert_displacement--;
		}
		if (keydown['S']) {
			vert_displacement++;
		}
		if (keydown['A']) {
			hor_displacement--;
		}
		if (keydown['D']) {
			hor_displacement++;
		}

		//sets the player's new direction based on the keys held down.
		if (vert_displacement == -1) {
			if (hor_displacement == -1) {
				change_direction(NORTHWEST);
			}
			else if (hor_displacement == 0) {
				change_direction(NORTH);
			}
			else {
				change_direction(NORTHEAST);
			}
		}
		else if (vert_displacement == 0) {
			if (hor_displacement == -1) {
				change_direction(WEST);
			}
			else if (hor_displacement == 0) {
				change_direction(STOP);
			}
			else {
				change_direction(EAST);
			}
		}
		else {
			if (hor_displacement == -1) {
				change_direction(SOUTHWEST);
			}
			else if (hor_displacement == 0) {
				change_direction(SOUTH);
			}
			else {
				change_direction(SOUTHEAST);
			}
		}
	}
	//otherwise change direction randomly (yes better algorithms can be written but this is not the focus of the project - at least for now).
	else {
		//if the bot is ready to change directions then roll a new direction to go in.
		if (change_direction_cd == 0) {
			int new_direction = rand() % 8 + 1;
			switch (new_direction) {
			case (1):
				facing = NORTH;
				break;
			case (2):
				facing = WEST;
				break;
			case (3):
				facing = SOUTH;
				break;
			case (4):
				facing = EAST;
				break;
			case (5):
				facing = NORTHWEST;
				break;
			case (6):
				facing = NORTHEAST;
				break;
			case (7):
				facing = SOUTHWEST;
				break;
			case (8):
				facing = SOUTHEAST;
				break;
			}
			change_direction_cd = (rand() % 3 + 1) * bot_change_direction_cd;
		}
		else {
			change_direction_cd--;
		}
	}
}

/*
prompts the player to shoot a bullet. Has different outcomes based on whether the player is a bot.
the return value is a very ugly data structure consisting of the values in the following order:
1. whether the player decides to fire a shot (bool); if this is false none of the following return values matter.
2. the angle of the shot (double)
3. the starting x position of the shot (double)
4. the starting 7 position of the shot (double)
*/
pair<pair<bool, double>, pair<double, double>> Player::shoot_prompt(bool mouse_down, bool clear_shot) {
	//if the player is not a bot base whether to fire a shot on whether the mouse is held.
	if (!is_bot) {
		//if the mouse is held, the shot cooldown is ready and the player is alive then fire a shot.
		if (mouse_down && shot_cooldown == 0 && alive) {
			double shot_angle = fire_shot();

			//return the values as specified above.
			return pair<pair<bool, double>, pair<double, double>>(pair<bool, double>(true, shot_angle), pair<double, double>(
				xpos + (player_radius - shot_length + shot_radius + epsilon) * cos(shot_angle), 
				ypos + (player_radius - shot_length + shot_radius + epsilon) * sin(shot_angle)));
		}
		else {
			return pair<pair<bool, double>, pair<double, double>>(pair<bool, double>(false, 0), pair<double, double>(0, 0));
		}
	}
	else {
		//if there is a clear path between the bot and the opponent, the shot cooldown is ready and the bot is alive then fire a shot.
		if (shot_cooldown == 0 && !clear_shot && alive) {
			double shot_angle = fire_shot();

			//return the values as specified above.
			return pair<pair<bool, double>, pair<double, double>>(pair<bool, double>(true, shot_angle), pair<double, double>(
				xpos + (player_radius * 0.9) * cos(shot_angle), ypos + (player_radius * 0.9) * sin(shot_angle)));
		}
		return pair<pair<bool, double>, pair<double, double>>(pair<bool, double>(false, 0), pair<double, double>(0, 0));
	}
}

/*
sets randomized names for bots. Hmm, I wonder what these names are?
*/
void Player::randomize_name() {
	int roll_dice = rand() % 5;
	string new_name;
	switch (roll_dice) {
	case(0):
		new_name.push_back(char(69));
		new_name.push_back(char(118));
		new_name.push_back(char(97));
		new_name.push_back(char(110));
		new_name.push_back(char(115));
		set_name(new_name);
		break;
	case(1):
		new_name.push_back(char(77));
		new_name.push_back(char(101));
		new_name.push_back(char(115));
		new_name.push_back(char(101));
		new_name.push_back(char(103));
		new_name.push_back(char(117));
		new_name.push_back(char(101));
		new_name.push_back(char(114));
		set_name(new_name);
		break;
	case(2):
		new_name.push_back(char(70));
		new_name.push_back(char(108));
		new_name.push_back(char(101));
		new_name.push_back(char(99));
		new_name.push_back(char(107));
		set_name(new_name);
		break;
	case(3):
		new_name.push_back(char(67));
		new_name.push_back(char(104));
		new_name.push_back(char(97));
		new_name.push_back(char(108));
		new_name.push_back(char(108));
		new_name.push_back(char(101));
		new_name.push_back(char(110));
		set_name(new_name);
		break;
	case(4):
		new_name.push_back(char(65));
		new_name.push_back(char(110));
		new_name.push_back(char(103));
		new_name.push_back(char(114));
		new_name.push_back(char(97));
		new_name.push_back(char(118));
		new_name.push_back(char(101));
		set_name(new_name);
		break;
	}
}

/*
sets randomized colors for bots.
*/
void Player::randomize_color() {
	set_color(rand() % 6 + red_button);
}

/*
set whether the player is a bot.
*/
void Player::set_bot(bool bot) {
	is_bot = bot;
}

/*
deserialize a message sent over a multiplayer connection and update a player accordingly.
*/
void Player::deserialize_update_message(string message) {
	vector<string> message_array = split(message.substr(6), "~");
	//set the player's new color based on the color received.
	switch (stoi(message_array[0])) {
	case (red_color):
		red = 255;
		green = 0;
		blue = 0;
		break;
	case (green_color):
		red = 0;
		green = 255;
		blue = 0;
		break;
	case (blue_color):
		red = 0;
		green = 0;
		blue = 255;
		break;
	case (yellow_color):
		red = 255;
		green = 255;
		blue = 0;
		break;
	case (magenta_color):
		red = 255;
		green = 0;
		blue = 255;
		break;
	case (cyan_color):
		red = 0;
		green = 255;
		blue = 255;
		break;
	}
	//interpret the rest of the message; consists of the name, the x and y coordinates the player is facing separated by 2 ~ characters.
	set_name(message_array[1]);
	facing_x = stoi(message_array[2]);
	facing_y = stoi(message_array[3]);
}

/*
send a player over the connection as a serialized string.
*/
string Player::serialized_string() {
	string to_send = "PLAYER" + to_string(get_color()) + "~" + name + "~" + to_string(facing_x) + "~" + to_string(facing_y);
	return to_send;
}