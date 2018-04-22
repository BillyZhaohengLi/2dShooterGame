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
const int shot_bounces = 10;

/*
direction enum; used to determine the player's orientation.
*/
enum direction { STOP = 0, NORTH = 1, SOUTH = 2, EAST = 3, WEST = 4, NORTHEAST = 5, NORTHWEST = 6, SOUTHEAST = 7, SOUTHWEST = 8 };