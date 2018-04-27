#pragma once
#include "add_buttons.h"
void add_buttons(AllButtons& buttons_in_level) {
	//MAIN MENU BUTTONS
	//start game button
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.35, level_height_multiplier * wall_width * 0.76,
		level_width_multiplier * wall_width * 0.3, level_height_multiplier * wall_width * 0.1, 0, 255, 0, "Start game",
		vector<game_state> {MAIN_MENU});

	//multiplayer button (doesn't do anything yet)
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.68, level_height_multiplier * wall_width * 0.76,
		level_width_multiplier * wall_width * 0.3, level_height_multiplier * wall_width * 0.1, 0, 255, 0, "Multiplayer", 
		vector<game_state> {MAIN_MENU});

	//help button; takes the player to the help interface
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.35, level_height_multiplier * wall_width * 0.89,
		level_width_multiplier * wall_width * 0.3, level_height_multiplier * wall_width * 0.1, 0, 255, 0, "Help", 
		vector<game_state> {MAIN_MENU});

	//exit button; exits the game
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.68, level_height_multiplier * wall_width * 0.89,
		level_width_multiplier * wall_width * 0.3, level_height_multiplier * wall_width * 0.1, 0, 255, 0, "Exit", 
		vector<game_state> {MAIN_MENU});

	//red color palette
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.75, level_height_multiplier * wall_width * 0.4,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 255, 0, 0, "", 
		vector<game_state> {MAIN_MENU});

	//blue color palette
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.8, level_height_multiplier * wall_width * 0.4,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 0, 255, 0, "", 
		vector<game_state> {MAIN_MENU});

	//green color palette
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.85, level_height_multiplier * wall_width * 0.4,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 0, 0, 255, "", 
		vector<game_state> {MAIN_MENU});

	//yellow color palette
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.75, level_height_multiplier * wall_width * 0.44,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 255, 255, 0, "", 
		vector<game_state> {MAIN_MENU});

	//magenta color palette
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.8, level_height_multiplier * wall_width * 0.44,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 255, 0, 255, "", 
		vector<game_state> {MAIN_MENU});

	//cyan color palette
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.85, level_height_multiplier * wall_width * 0.44,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 0, 255, 255, "", 
		vector<game_state> {MAIN_MENU});

	//few wall settings
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.2, level_height_multiplier * wall_width * 0.52,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 0, 255, 0, "", 
		vector<game_state> {MAIN_MENU});

	//medium wall settings
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.2, level_height_multiplier * wall_width * 0.57,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 255, 255, 0, "", 
		vector<game_state> {MAIN_MENU});

	//lots of walls settings
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.2, level_height_multiplier * wall_width * 0.62,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 255, 0, 0, "", 
		vector<game_state> {MAIN_MENU});

	//PAUSED BUTTONS
	//back to main menu
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.3, level_height_multiplier * wall_width * 0.55,
		level_width_multiplier * wall_width * 0.4, level_height_multiplier * wall_width * 0.08, 0, 255, 0, "Return to menu", 
		vector<game_state> {PAUSE});

	//HELP BUTTONS
	//back to main menu
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.35, level_height_multiplier * wall_width * 0.8,
		level_width_multiplier * wall_width * 0.3, level_height_multiplier * wall_width * 0.1, 0, 255, 0, "Back", 
		vector<game_state> {HELP});

	//ROUND OVER BUTTONS
	//rematch
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.35, level_height_multiplier * wall_width * 0.92,
		level_width_multiplier * wall_width * 0.22, level_height_multiplier * wall_width * 0.04, 0, 255, 0, "Rematch", 
		vector<game_state> {ROUND_OVER});
	//back to main menu
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.6, level_height_multiplier * wall_width * 0.92,
		level_width_multiplier * wall_width * 0.22, level_height_multiplier * wall_width * 0.04, 0, 255, 0, "Return to menu", 
		vector<game_state> {ROUND_OVER});

	//MULTIPLAYER BUTTONS
	//connect button
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.35, level_height_multiplier * wall_width * 0.7,
		level_width_multiplier * wall_width * 0.3, level_height_multiplier * wall_width * 0.1, 0, 255, 0, "Connect", 
		vector<game_state> {MULTI_CONNECT});

	//back button; returns to main menu
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.35, level_height_multiplier * wall_width * 0.85,
		level_width_multiplier * wall_width * 0.3, level_height_multiplier * wall_width * 0.1, 0, 255, 0, "Back", 
		vector<game_state> {MULTI_CONNECT});

	//MULTIPLAYER MENU BUTTONS
	//start game button
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.35, level_height_multiplier * wall_width * 0.76,
		level_width_multiplier * wall_width * 0.3, level_height_multiplier * wall_width * 0.1, 0, 255, 0, "Start game", 
		vector<game_state> {MULTI_MENU});

	//exit button; exits the game
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.68, level_height_multiplier * wall_width * 0.89,
		level_width_multiplier * wall_width * 0.3, level_height_multiplier * wall_width * 0.1, 0, 255, 0, "Disconnect", 
		vector<game_state> {MULTI_MENU});

	//red color palette
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.75, level_height_multiplier * wall_width * 0.4,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 255, 0, 0, "", 
		vector<game_state> {MULTI_MENU});

	//blue color palette
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.8, level_height_multiplier * wall_width * 0.4,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 0, 255, 0, "", 
		vector<game_state> {MULTI_MENU});

	//green color palette
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.85, level_height_multiplier * wall_width * 0.4,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 0, 0, 255, "", 
		vector<game_state> {MULTI_MENU});

	//yellow color palette
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.75, level_height_multiplier * wall_width * 0.44,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 255, 255, 0, "", 
		vector<game_state> {MULTI_MENU});

	//magenta color palette
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.8, level_height_multiplier * wall_width * 0.44,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 255, 0, 255, "", 
		vector<game_state> {MULTI_MENU});

	//cyan color palette
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.85, level_height_multiplier * wall_width * 0.44,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 0, 255, 255, "", 
		vector<game_state> {MULTI_MENU});

	//few wall settings
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.2, level_height_multiplier * wall_width * 0.52,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 0, 255, 0, "", 
		vector<game_state> {MULTI_MENU});

	//medium wall settings
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.2, level_height_multiplier * wall_width * 0.57,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 255, 255, 0, "", 
		vector<game_state> {MULTI_MENU});

	//lots of walls settings
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.2, level_height_multiplier * wall_width * 0.62,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 255, 0, 0, "", 
		vector<game_state> {MULTI_MENU});
}