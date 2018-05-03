#pragma once
#include <vector>
#include "../ofMain.h"
#include "../const.h"
#include "../game_assets/player.h"
#include "../game_assets/shot.h"
#include "../game_assets/wall.h"
#include "helperfunctions.h"
//class for object manipulation helper functions which represent combinations which 
//appear so many times in the main game engine that they deserve to be standalone helper methods.

/*
resets both players to opposite corners in the map, clear all shots in the level 
and reset the keys held.
Called at round start and rematch.
*/
void reset_game(Player& p1, Player& p2, ShotInLevel& shots_in_level, bool keydown[255]);

/*
resets both players to appropriate locations in the menu, clear the level 
(wall segments and shots) and reset the keys held.
Called every time the main menu is entered.
*/
void reset_to_menu(Player& p1, Player& p2, ShotInLevel& shots_in_level, Wall& walls_in_level, 
	Connection status, bool keydown[255]);

/*
generates the text on the game over screen signifying the outcome of the match.
*/
string generate_game_over_message(Player p1, Player p2);
