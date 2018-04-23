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
const int player_shot_cooldown = 20;

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

const int bot_change_direction_cd = 30;

const int max_name_length = 16;

/*
direction enum; used to determine the player's orientation.
*/
enum direction { STOP = 0, NORTH = 1, SOUTH = 2, EAST = 3, WEST = 4, NORTHEAST = 5, NORTHWEST = 6, SOUTHEAST = 7, SOUTHWEST = 8 };

/*
game state enum; 
*/
enum game_state { MAIN_MENU = 0, SINGLE_PARAMS = 1, IN_GAME_SINGLE = 2, PAUSE = 3, ROUND_OVER = 4, HELP = 5 };

/*
enum to determine game winner;
*/
enum winner { TIE = 0, P1_WIN = 1, P2_WIN = 2 };

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
const int params_back_to_menu = 13;
const int paused_back_to_menu = 14;
const int help_back_to_menu = 15;
const int rematch_button = 16;
const int round_over_back_to_menu = 17;

const int character_start = 32;
const int character_end = 126;