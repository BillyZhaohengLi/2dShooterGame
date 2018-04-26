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

enum connection { NONE = 0, HOST = 1, CLIENT = 2 };

/*
indices of Buttons in the AllButtons object.
*/
//single player menu buttons
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

//paused buttons
const int paused_back_to_menu = 13;

//help buttons
const int help_back_to_menu = 14;

//round over buttons
const int rematch_button = 15;
const int round_over_back_to_menu = 16;

//multiplayer connect buttons
const int multi_connect_button = 17;
const int multi_connect_back_to_menu = 18;

//multiplayer menu buttons
const int multi_start_game_button = 19;
const int multi_disconnect_button = 20;
const int red_button_m = 21;
const int green_button_m = 22;
const int blue_button_m = 23;
const int yellow_button_m = 24;
const int magenta_button_m = 25;
const int cyan_button_m = 26;
const int few_walls_m = 27;
const int medium_walls_m = 28;
const int a_lot_walls_m = 29;

/*
constants for the amount of walls to be generated in a level; corresponds to the wall setting buttons.
*/
const int few_walls_amount = 8;
const int medium_walls_amount = 16;
const int a_lot_walls_amount = 32;

/*
start and end of printable ascii character range.
*/
const int character_start = 32;
const int character_end = 126;

/*
start and end of printable integer character range.
*/
const int integer_start = 48;
const int integer_end = 57;

/*
ascii value of backspace button.
*/
const int backspace_ascii = 8;

/*
ascii value of period.
*/
const int period_ascii = 46;

/*
port number used for multiplayer connections. (Fixing this makes so that only one multiplayer server can be started per ip address).
*/
const int multiplayer_port = 11999;

