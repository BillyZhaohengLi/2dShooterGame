#include "objecthelperfunctions.h"
/*
resets both players to opposite corners in the map. Appears so many times in the main game engine that it deserves to be a standalone helper method.
*/
void reset_game(Player& p1, Player& p2, ShotInLevel& shots_in_level, bool keydown[255]) {
	//clear all shots in the level.
	shots_in_level.clear_shots();

	//randomly assign the players to each of the opposite corners to make things more interesting.
	int pos = rand() % 100;
	if (pos > 50) {
		p1.reset_player(kWallWidth * 2.5, (kLevelHeightMultiplier - 2.5) * kWallWidth);
		p2.reset_player((kLevelWidthMultiplier - 2.5) * kWallWidth, kWallWidth * 2.5);
	}
	else {
		p2.reset_player(kWallWidth * 2.5, (kLevelHeightMultiplier - 2.5) * kWallWidth);
		p1.reset_player((kLevelWidthMultiplier - 2.5) * kWallWidth, kWallWidth * 2.5);
	}

	//clear all pressed keys
	for (int i = 0; i < 255; i++) {
		keydown[i] = false;
	}
}

/*
resets both players to appropriate locations in the menu, clear the level (wall segments and shots) and reset the keys held.
Called every time the main menu is entered.
*/
void reset_to_menu(Player& p1, Player& p2, ShotInLevel& shots_in_level, Wall& walls_in_level, Connection status, bool keydown[255]) {
	//clear shots and walls
	shots_in_level.clear_shots();
	walls_in_level.clear_level();

	switch (status) {
	//singleplayer; set p1 to the middle and p2 to any applicable position (since p2 isn't shown in the singleplayer menu anyways)
	case NONE:
		p1.reset_player(kLevelWidthMultiplier * kWallWidth * 0.5, kLevelHeightMultiplier * kWallWidth * 0.4);
		p2.reset_player((kLevelWidthMultiplier - 2.5) * kWallWidth, kWallWidth * 2.5);
		p2.set_bot(true);
		break;
	//host; p1 to the left and p2 to the right
	case HOST:
		p1.set_location(kLevelWidthMultiplier * kWallWidth * 0.45, kLevelHeightMultiplier * kWallWidth * 0.4);
		p2.set_location(kLevelWidthMultiplier * kWallWidth * 0.55, kLevelHeightMultiplier * kWallWidth * 0.4);
		p2.set_bot(false);
		break;
	//client; p1 to the right and p2 to the left
	case CLIENT:
		p1.set_location(kLevelWidthMultiplier * kWallWidth * 0.55, kLevelHeightMultiplier * kWallWidth * 0.4);
		p2.set_location(kLevelWidthMultiplier * kWallWidth * 0.45, kLevelHeightMultiplier * kWallWidth * 0.4);
		p2.set_bot(false);
		break;
	}

	//clear all pressed keys
	for (int i = 0; i < 255; i++) {
		keydown[i] = false;
	}
}

/*
generates the text on the game over screen signifying the outcome of the match.
*/
string generate_game_over_message(Player p1, Player p2) {
	if (!p1.isalive() && !p2.isalive()) {
		return "It's a tie.";
	}
	else if (!p1.isalive()) {
		return p2.get_name() + " wins!";
	}
	else if (!p2.isalive()) {
		return p1.get_name() + " wins!";
	}
	return "";
}