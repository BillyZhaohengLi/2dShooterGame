#pragma once
const double pi = 3.14159265359;
const int level_width = 1024;
const int level_height = 768;
const int wall_width = 32;
const int player_radius = 16;
const int player_velocity = 4;
const int player_shot_cooldown = 20;
const int shot_length = 12;
enum direction { STOP = 0, NORTH = 1, SOUTH = 2, EAST = 3, WEST = 4, NORTHEAST = 5, NORTHWEST = 6, SOUTHEAST = 7, SOUTHWEST = 8 };