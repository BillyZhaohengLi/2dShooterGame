#pragma once
#include "add_buttons_text.h"
void add_buttons_text(AllButtons& buttons_in_level, AllText& text_in_level) {
	//create font used for buttons and text in game
	ofxCenteredTrueTypeFont game_title_text;
	ofxCenteredTrueTypeFont button_text;
	ofxCenteredTrueTypeFont character_name;

	//load text for generic buttons
	button_text.loadFont("verdana.ttf", wall_width);
	button_text.setLineHeight(18.0f);
	button_text.setLetterSpacing(1.037);

	//load text for titles
	game_title_text.loadFont("verdana.ttf", wall_width * 2);
	game_title_text.setLineHeight(18.0f);
	game_title_text.setLetterSpacing(1.037);

	//load text for character name
	character_name.loadFont("verdana.ttf", wall_width * 0.6);
	character_name.setLineHeight(18.0f);
	character_name.setLetterSpacing(1.037);

	//DRAW BUTTONS
	//MAIN MENU BUTTONS
	//start game button
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.35, level_height_multiplier * wall_width * 0.76,
		level_width_multiplier * wall_width * 0.3, level_height_multiplier * wall_width * 0.1, 0, 255, 0, "Start game",
		vector<game_state> {MAIN_MENU, MULTI_MENU}, button_text);

	//multiplayer button (doesn't do anything yet)
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.68, level_height_multiplier * wall_width * 0.76,
		level_width_multiplier * wall_width * 0.3, level_height_multiplier * wall_width * 0.1, 0, 255, 0, "Multiplayer", 
		vector<game_state> {MAIN_MENU}, button_text);

	//help button; takes the player to the help interface
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.35, level_height_multiplier * wall_width * 0.89,
		level_width_multiplier * wall_width * 0.3, level_height_multiplier * wall_width * 0.1, 0, 255, 0, "Help", 
		vector<game_state> {MAIN_MENU}, button_text);

	//exit button; exits the game
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.68, level_height_multiplier * wall_width * 0.89,
		level_width_multiplier * wall_width * 0.3, level_height_multiplier * wall_width * 0.1, 0, 255, 0, "Exit", 
		vector<game_state> {MAIN_MENU}, button_text);

	//red color palette
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.75, level_height_multiplier * wall_width * 0.4,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 255, 0, 0, "", 
		vector<game_state> {MAIN_MENU, MULTI_MENU}, button_text);

	//blue color palette
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.8, level_height_multiplier * wall_width * 0.4,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 0, 255, 0, "", 
		vector<game_state> {MAIN_MENU, MULTI_MENU}, button_text);

	//green color palette
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.85, level_height_multiplier * wall_width * 0.4,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 0, 0, 255, "", 
		vector<game_state> {MAIN_MENU, MULTI_MENU}, button_text);

	//yellow color palette
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.75, level_height_multiplier * wall_width * 0.44,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 255, 255, 0, "", 
		vector<game_state> {MAIN_MENU, MULTI_MENU}, button_text);

	//magenta color palette
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.8, level_height_multiplier * wall_width * 0.44,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 255, 0, 255, "", 
		vector<game_state> {MAIN_MENU, MULTI_MENU}, button_text);

	//cyan color palette
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.85, level_height_multiplier * wall_width * 0.44,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 0, 255, 255, "", 
		vector<game_state> {MAIN_MENU, MULTI_MENU}, button_text);

	//few wall settings
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.2, level_height_multiplier * wall_width * 0.52,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 0, 255, 0, "", 
		vector<game_state> {MAIN_MENU, MULTI_MENU}, button_text);

	//medium wall settings
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.2, level_height_multiplier * wall_width * 0.57,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 255, 255, 0, "", 
		vector<game_state> {MAIN_MENU, MULTI_MENU}, button_text);

	//lots of walls settings
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.2, level_height_multiplier * wall_width * 0.62,
		level_width_multiplier * wall_width * 0.03, level_height_multiplier * wall_width * 0.03, 255, 0, 0, "", 
		vector<game_state> {MAIN_MENU, MULTI_MENU}, button_text);

	//PAUSED BUTTONS
	//back to main menu
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.3, level_height_multiplier * wall_width * 0.55,
		level_width_multiplier * wall_width * 0.4, level_height_multiplier * wall_width * 0.08, 0, 255, 0, "Return to menu", 
		vector<game_state> {PAUSE}, button_text);

	//HELP BUTTONS
	//back to main menu
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.35, level_height_multiplier * wall_width * 0.8,
		level_width_multiplier * wall_width * 0.3, level_height_multiplier * wall_width * 0.1, 0, 255, 0, "Back", 
		vector<game_state> {HELP}, button_text);

	//ROUND OVER BUTTONS
	//rematch
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.35, level_height_multiplier * wall_width * 0.92,
		level_width_multiplier * wall_width * 0.22, level_height_multiplier * wall_width * 0.04, 0, 255, 0, "Rematch", 
		vector<game_state> {ROUND_OVER}, character_name);
	//back to main menu
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.6, level_height_multiplier * wall_width * 0.92,
		level_width_multiplier * wall_width * 0.22, level_height_multiplier * wall_width * 0.04, 0, 255, 0, "Return to menu", 
		vector<game_state> {ROUND_OVER}, character_name);

	//MULTIPLAYER BUTTONS
	//connect button
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.35, level_height_multiplier * wall_width * 0.59,
		level_width_multiplier * wall_width * 0.3, level_height_multiplier * wall_width * 0.1, 0, 255, 0, "Connect", 
		vector<game_state> {MULTI_CONNECT}, button_text);

	//start server button; instantiates the server in the program
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.35, level_height_multiplier * wall_width * 0.72,
		level_width_multiplier * wall_width * 0.3, level_height_multiplier * wall_width * 0.1, 0, 255, 0, "Create server", 
		vector<game_state> {MULTI_CONNECT}, button_text);

	//back button; returns to main menu
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.35, level_height_multiplier * wall_width * 0.85,
		level_width_multiplier * wall_width * 0.3, level_height_multiplier * wall_width * 0.1, 0, 255, 0, "Back",
		vector<game_state> {MULTI_CONNECT}, button_text);

	//MULTIPLAYER MENU BUTTONS
	//disconnect button; disconnects from the multiplayer session.
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.68, level_height_multiplier * wall_width * 0.89,
		level_width_multiplier * wall_width * 0.3, level_height_multiplier * wall_width * 0.1, 0, 255, 0, "Disconnect", 
		vector<game_state> {MULTI_MENU}, button_text);

	//back button; returns to main menu
	buttons_in_level.add_button(level_width_multiplier * wall_width * 0.35, level_height_multiplier * wall_width * 0.85,
		level_width_multiplier * wall_width * 0.3, level_height_multiplier * wall_width * 0.1, 0, 255, 0, "OK",
		vector<game_state> {DISCONNECTED}, button_text);

	//DRAW TEXT
	//text for main menu
	text_in_level.add_text("Player name:", level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.35, 
		false, MAIN_MENU, character_name);
	text_in_level.add_text("Player color:", level_width_multiplier * wall_width * 0.75, level_height_multiplier * wall_width * 0.35, 
		false, MAIN_MENU, character_name);
	text_in_level.add_text("Wall settings:", level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.5, 
		false, MAIN_MENU, character_name);
	text_in_level.add_text("Few", level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.55, 
		false, MAIN_MENU, character_name);
	text_in_level.add_text("Some", level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.60, 
		false, MAIN_MENU, character_name);
	text_in_level.add_text("A lot", level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.65, 
		false, MAIN_MENU, character_name);
	text_in_level.add_text("2D Shooter Game", level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.15, 
		true, MAIN_MENU, game_title_text);

	//text for paused interface
	text_in_level.add_text("Game paused", level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.3, 
		true, PAUSE, character_name);
	text_in_level.add_text("Press P to unpause", level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.35, 
		true, PAUSE, character_name);

	//text for help interface
	text_in_level.add_text("Help", level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.15, 
		true, HELP, game_title_text);
	text_in_level.add_text("Move: WASD keys", level_width_multiplier * wall_width * 0.2, level_height_multiplier * wall_width * 0.35, 
		false, HELP, character_name);
	text_in_level.add_text("Fire: mouse button", level_width_multiplier * wall_width * 0.2, level_height_multiplier * wall_width * 0.45, 
		false, HELP, character_name);
	text_in_level.add_text("Pause: P (single player only)", level_width_multiplier * wall_width * 0.2, level_height_multiplier * wall_width * 0.55, 
		false, HELP, character_name);

	//text for multiplayer connect interface
	text_in_level.add_text("Multiplayer connect", level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.15,
		true, MULTI_CONNECT, game_title_text);
	text_in_level.add_text("Enter an IP address to LAN connect to or wait for a connection:", level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.35,
		false, MULTI_CONNECT, character_name);

	//text for multiplayer menu interface
	text_in_level.add_text("Player name:", level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.35,
		false, MULTI_MENU, character_name);
	text_in_level.add_text("Player color:", level_width_multiplier * wall_width * 0.75, level_height_multiplier * wall_width * 0.35,
		false, MULTI_MENU, character_name);
	text_in_level.add_text("Wall settings:", level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.5,
		false, MULTI_MENU, character_name);
	text_in_level.add_text("Few", level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.55,
		false, MULTI_MENU, character_name);
	text_in_level.add_text("Some", level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.60,
		false, MULTI_MENU, character_name);
	text_in_level.add_text("A lot", level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.65,
		false, MULTI_MENU, character_name);
	text_in_level.add_text("2D Shooter Game", level_width_multiplier * wall_width * 0.5, level_height_multiplier * wall_width * 0.15,
		true, MULTI_MENU, game_title_text);

	text_in_level.add_text("Your multiplayer session has ended.", level_width_multiplier * wall_width * 0.1, level_height_multiplier * wall_width * 0.35,
		false, DISCONNECTED, character_name);

	//add the fonts to the text object to be used in game
	text_in_level.add_font(game_title_text);
	text_in_level.add_font(button_text);
	text_in_level.add_font(character_name);
}