#pragma once
/*
pi. self-explanatory.
*/
const double pi = 3.14159265359;

/*
width of the level; not necessarily the window width.
*/
const int level_width_multiplier = 32;

/*
height of the level; not necessarily the window height.
*/
const int level_height_multiplier = 24;

/*
guideline width for creating wall segments.
*/
const int wall_width = 32;

/*
radius of the player (who is a circle).
*/
const int player_radius = 15;

/*
radius of shots.
*/
const int shot_radius = 3;

/*
velocity of the player.
*/
const int player_velocity = 4;

/*
cooldown between firing shots in ticks.
*/
const int player_shot_cooldown = 30;

/*
the "length" of a shot; only used in shot-wall collisions to calculate trajectory; has nothing to do with shot-player collisions.
*/
const int shot_length = 12;

/*
buffer value used in resolving collisions.
*/
const double epsilon = 0.00005;

/*
amount of times a shot can bounce.
*/
const int shot_bounces = 6;

/*
the cooldown between the bot changing directions. Unused by players.
*/
const int bot_change_direction_cd = 30;

/*
the maximum name length of the player.
*/
const int max_name_length = 16;

const int max_ip_length = 15;
/*
direction enum; used to determine the player's orientation.
*/
enum direction { STOP = 0, NORTH = 1, SOUTH = 2, EAST = 3, WEST = 4, NORTHEAST = 5, NORTHWEST = 6, SOUTHEAST = 7, SOUTHWEST = 8 };

/*
game state enum; 
*/
enum game_state { MAIN_MENU = 0, IN_GAME_SINGLE = 2, PAUSE = 3, ROUND_OVER = 4, HELP = 5,
	MULTI_CONNECT = 6 , MULTI_MENU = 7, IN_GAME_MULTI = 8, MULTI_ROUND_OVER = 9};

/*
enum to determine game winner;
*/
enum winner { TIE = 0, P1_WIN = 1, P2_WIN = 2 };

/*
indices of Buttons in the AllButtons object.
*/
const int start_singleplayer_button = 0;
const int start_multiplayer_button = 1;
const int help_button = 2;
const int exit_button = 3;
const int red_button = 4;
const int green_button = 5;
const int blue_button = 6;
const int yellow_button = 7;
const int magenta_button = 8;
const int cyan_button = 9;
const int few_walls = 10;
const int medium_walls = 11;
const int a_lot_walls = 12;
const int paused_back_to_menu = 13;
const int help_back_to_menu = 14;
const int rematch_button = 15;
const int round_over_back_to_menu = 16;
const int multi_connect_button = 17;
const int multi_connect_back_to_menu = 18;

/*
start and end of printable ascii character range.
*/
const int character_start = 32;
const int character_end = 126;

const int integer_start = 48;
const int integer_end = 57;

const int backspace_ascii = 8;
const int period_ascii = 46;

const int multiplayer_port = 11999;