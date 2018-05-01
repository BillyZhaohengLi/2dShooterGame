#pragma once
#include "add_buttons_text.h"
void add_buttons_text(AllButtons& buttons_in_level, AllText& text_in_level) {
	//create font used for buttons and text in game
	ofxCenteredTrueTypeFont game_title_text;
	ofxCenteredTrueTypeFont button_text;
	ofxCenteredTrueTypeFont character_name;

	//load text for generic buttons
	button_text.loadFont("verdana.ttf", kWallWidth);
	button_text.setLineHeight(18.0f);
	button_text.setLetterSpacing(1.037);

	//load text for titles
	game_title_text.loadFont("verdana.ttf", kWallWidth * 2);
	game_title_text.setLineHeight(18.0f);
	game_title_text.setLetterSpacing(1.037);

	//load text for character name
	character_name.loadFont("verdana.ttf", kWallWidth * 0.6);
	character_name.setLineHeight(18.0f);
	character_name.setLetterSpacing(1.037);

	//DRAW BUTTONS
	//MAIN MENU BUTTONS
	//start game button
	buttons_in_level.add_button(kLevelWidthMultiplier * kWallWidth * 0.35, kLevelHeightMultiplier * kWallWidth * 0.76,
		kLevelWidthMultiplier * kWallWidth * 0.3, kLevelHeightMultiplier * kWallWidth * 0.1, ofColor::green, "Start game",
		vector<GameState> {MAIN_MENU, MULTI_MENU}, button_text);

	//multiplayer button (doesn't do anything yet)
	buttons_in_level.add_button(kLevelWidthMultiplier * kWallWidth * 0.68, kLevelHeightMultiplier * kWallWidth * 0.76,
		kLevelWidthMultiplier * kWallWidth * 0.3, kLevelHeightMultiplier * kWallWidth * 0.1, ofColor::green, "Multiplayer",
		vector<GameState> {MAIN_MENU}, button_text);

	//help button; takes the player to the help interface
	buttons_in_level.add_button(kLevelWidthMultiplier * kWallWidth * 0.35, kLevelHeightMultiplier * kWallWidth * 0.89,
		kLevelWidthMultiplier * kWallWidth * 0.3, kLevelHeightMultiplier * kWallWidth * 0.1, ofColor::green, "Help",
		vector<GameState> {MAIN_MENU}, button_text);

	//exit button; exits the game
	buttons_in_level.add_button(kLevelWidthMultiplier * kWallWidth * 0.68, kLevelHeightMultiplier * kWallWidth * 0.89,
		kLevelWidthMultiplier * kWallWidth * 0.3, kLevelHeightMultiplier * kWallWidth * 0.1, ofColor::green, "Exit",
		vector<GameState> {MAIN_MENU}, button_text);

	//red color palette
	buttons_in_level.add_button(kLevelWidthMultiplier * kWallWidth * 0.75, kLevelHeightMultiplier * kWallWidth * 0.4,
		kLevelWidthMultiplier * kWallWidth * 0.03, kLevelHeightMultiplier * kWallWidth * 0.03, ofColor::red, "", 
		vector<GameState> {MAIN_MENU, MULTI_MENU}, button_text);

	//green color palette
	buttons_in_level.add_button(kLevelWidthMultiplier * kWallWidth * 0.8, kLevelHeightMultiplier * kWallWidth * 0.4,
		kLevelWidthMultiplier * kWallWidth * 0.03, kLevelHeightMultiplier * kWallWidth * 0.03, ofColor::green, "",
		vector<GameState> {MAIN_MENU, MULTI_MENU}, button_text);

	//blue color palette
	buttons_in_level.add_button(kLevelWidthMultiplier * kWallWidth * 0.85, kLevelHeightMultiplier * kWallWidth * 0.4,
		kLevelWidthMultiplier * kWallWidth * 0.03, kLevelHeightMultiplier * kWallWidth * 0.03, ofColor::blue, "", 
		vector<GameState> {MAIN_MENU, MULTI_MENU}, button_text);

	//yellow color palette
	buttons_in_level.add_button(kLevelWidthMultiplier * kWallWidth * 0.75, kLevelHeightMultiplier * kWallWidth * 0.44,
		kLevelWidthMultiplier * kWallWidth * 0.03, kLevelHeightMultiplier * kWallWidth * 0.03, ofColor::yellow, "", 
		vector<GameState> {MAIN_MENU, MULTI_MENU}, button_text);

	//magenta color palette
	buttons_in_level.add_button(kLevelWidthMultiplier * kWallWidth * 0.8, kLevelHeightMultiplier * kWallWidth * 0.44,
		kLevelWidthMultiplier * kWallWidth * 0.03, kLevelHeightMultiplier * kWallWidth * 0.03, ofColor::magenta, "", 
		vector<GameState> {MAIN_MENU, MULTI_MENU}, button_text);

	//cyan color palette
	buttons_in_level.add_button(kLevelWidthMultiplier * kWallWidth * 0.85, kLevelHeightMultiplier * kWallWidth * 0.44,
		kLevelWidthMultiplier * kWallWidth * 0.03, kLevelHeightMultiplier * kWallWidth * 0.03, ofColor::cyan, "", 
		vector<GameState> {MAIN_MENU, MULTI_MENU}, button_text);

	//few wall settings
	buttons_in_level.add_button(kLevelWidthMultiplier * kWallWidth * 0.2, kLevelHeightMultiplier * kWallWidth * 0.52,
		kLevelWidthMultiplier * kWallWidth * 0.03, kLevelHeightMultiplier * kWallWidth * 0.03, ofColor::green, "", 
		vector<GameState> {MAIN_MENU, MULTI_MENU}, button_text);

	//medium wall settings
	buttons_in_level.add_button(kLevelWidthMultiplier * kWallWidth * 0.2, kLevelHeightMultiplier * kWallWidth * 0.57,
		kLevelWidthMultiplier * kWallWidth * 0.03, kLevelHeightMultiplier * kWallWidth * 0.03, ofColor::yellow, "", 
		vector<GameState> {MAIN_MENU, MULTI_MENU}, button_text);

	//lots of walls settings
	buttons_in_level.add_button(kLevelWidthMultiplier * kWallWidth * 0.2, kLevelHeightMultiplier * kWallWidth * 0.62,
		kLevelWidthMultiplier * kWallWidth * 0.03, kLevelHeightMultiplier * kWallWidth * 0.03, ofColor::red, "", 
		vector<GameState> {MAIN_MENU, MULTI_MENU}, button_text);

	//PAUSED BUTTONS
	//back to main menu
	buttons_in_level.add_button(kLevelWidthMultiplier * kWallWidth * 0.3, kLevelHeightMultiplier * kWallWidth * 0.55,
		kLevelWidthMultiplier * kWallWidth * 0.4, kLevelHeightMultiplier * kWallWidth * 0.08, ofColor::green, "Return to menu",
		vector<GameState> {PAUSE}, button_text);

	//HELP BUTTONS
	//back to main menu
	buttons_in_level.add_button(kLevelWidthMultiplier * kWallWidth * 0.35, kLevelHeightMultiplier * kWallWidth * 0.8,
		kLevelWidthMultiplier * kWallWidth * 0.3, kLevelHeightMultiplier * kWallWidth * 0.1, ofColor::green, "Back",
		vector<GameState> {HELP}, button_text);

	//ROUND OVER BUTTONS
	//rematch
	buttons_in_level.add_button(kLevelWidthMultiplier * kWallWidth * 0.35, kLevelHeightMultiplier * kWallWidth * 0.92,
		kLevelWidthMultiplier * kWallWidth * 0.22, kLevelHeightMultiplier * kWallWidth * 0.04, ofColor::green, "Rematch",
		vector<GameState> {ROUND_OVER}, character_name);
	//back to main menu
	buttons_in_level.add_button(kLevelWidthMultiplier * kWallWidth * 0.6, kLevelHeightMultiplier * kWallWidth * 0.92,
		kLevelWidthMultiplier * kWallWidth * 0.22, kLevelHeightMultiplier * kWallWidth * 0.04, ofColor::green, "Return to menu",
		vector<GameState> {ROUND_OVER}, character_name);

	//MULTIPLAYER BUTTONS
	//connect button
	buttons_in_level.add_button(kLevelWidthMultiplier * kWallWidth * 0.35, kLevelHeightMultiplier * kWallWidth * 0.59,
		kLevelWidthMultiplier * kWallWidth * 0.3, kLevelHeightMultiplier * kWallWidth * 0.1, ofColor::green, "Connect",
		vector<GameState> {MULTI_CONNECT}, button_text);

	//start server button; instantiates the server in the program
	buttons_in_level.add_button(kLevelWidthMultiplier * kWallWidth * 0.35, kLevelHeightMultiplier * kWallWidth * 0.72,
		kLevelWidthMultiplier * kWallWidth * 0.3, kLevelHeightMultiplier * kWallWidth * 0.1, ofColor::green, "Create server",
		vector<GameState> {MULTI_CONNECT}, button_text);

	//back button; returns to main menu
	buttons_in_level.add_button(kLevelWidthMultiplier * kWallWidth * 0.35, kLevelHeightMultiplier * kWallWidth * 0.85,
		kLevelWidthMultiplier * kWallWidth * 0.3, kLevelHeightMultiplier * kWallWidth * 0.1, ofColor::green, "Back",
		vector<GameState> {MULTI_CONNECT}, button_text);

	//MULTIPLAYER MENU BUTTONS
	//disconnect button; disconnects from the multiplayer session.
	buttons_in_level.add_button(kLevelWidthMultiplier * kWallWidth * 0.68, kLevelHeightMultiplier * kWallWidth * 0.89,
		kLevelWidthMultiplier * kWallWidth * 0.3, kLevelHeightMultiplier * kWallWidth * 0.1, ofColor::green, "Disconnect",
		vector<GameState> {MULTI_MENU}, button_text);

	//DISCONNECTED MENU BUTTONS
	//confirmation button which shows up after the user gets disconnected from a multiplayer session.
	buttons_in_level.add_button(kLevelWidthMultiplier * kWallWidth * 0.35, kLevelHeightMultiplier * kWallWidth * 0.85,
		kLevelWidthMultiplier * kWallWidth * 0.3, kLevelHeightMultiplier * kWallWidth * 0.1, ofColor::green, "OK",
		vector<GameState> {DISCONNECTED, DISCONNECTED_BY_HOST}, button_text);

	//DRAW TEXT
	//text for main menu
	text_in_level.add_text("Player name:", kLevelWidthMultiplier * kWallWidth * 0.1, kLevelHeightMultiplier * kWallWidth * 0.35, 
		false, MAIN_MENU, character_name);
	text_in_level.add_text("Player color:", kLevelWidthMultiplier * kWallWidth * 0.75, kLevelHeightMultiplier * kWallWidth * 0.35, 
		false, MAIN_MENU, character_name);
	text_in_level.add_text("Wall settings:", kLevelWidthMultiplier * kWallWidth * 0.1, kLevelHeightMultiplier * kWallWidth * 0.5, 
		false, MAIN_MENU, character_name);
	text_in_level.add_text("Few", kLevelWidthMultiplier * kWallWidth * 0.1, kLevelHeightMultiplier * kWallWidth * 0.55, 
		false, MAIN_MENU, character_name);
	text_in_level.add_text("Some", kLevelWidthMultiplier * kWallWidth * 0.1, kLevelHeightMultiplier * kWallWidth * 0.60, 
		false, MAIN_MENU, character_name);
	text_in_level.add_text("A lot", kLevelWidthMultiplier * kWallWidth * 0.1, kLevelHeightMultiplier * kWallWidth * 0.65, 
		false, MAIN_MENU, character_name);
	text_in_level.add_text("2D Shooter Game", kLevelWidthMultiplier * kWallWidth * 0.5, kLevelHeightMultiplier * kWallWidth * 0.15, 
		true, MAIN_MENU, game_title_text);

	//text for paused interface
	text_in_level.add_text("Game paused", kLevelWidthMultiplier * kWallWidth * 0.5, kLevelHeightMultiplier * kWallWidth * 0.3, 
		true, PAUSE, character_name);
	text_in_level.add_text("Press P to unpause", kLevelWidthMultiplier * kWallWidth * 0.5, kLevelHeightMultiplier * kWallWidth * 0.35, 
		true, PAUSE, character_name);

	//text for help interface
	text_in_level.add_text("Help", kLevelWidthMultiplier * kWallWidth * 0.5, kLevelHeightMultiplier * kWallWidth * 0.15, 
		true, HELP, game_title_text);
	text_in_level.add_text("Move: WASD keys", kLevelWidthMultiplier * kWallWidth * 0.2, kLevelHeightMultiplier * kWallWidth * 0.35, 
		false, HELP, character_name);
	text_in_level.add_text("Fire: mouse button", kLevelWidthMultiplier * kWallWidth * 0.2, kLevelHeightMultiplier * kWallWidth * 0.45, 
		false, HELP, character_name);
	text_in_level.add_text("Pause: P (single player only)", kLevelWidthMultiplier * kWallWidth * 0.2, kLevelHeightMultiplier * kWallWidth * 0.55, 
		false, HELP, character_name);

	//text for multiplayer connect interface
	text_in_level.add_text("Multiplayer connect", kLevelWidthMultiplier * kWallWidth * 0.5, kLevelHeightMultiplier * kWallWidth * 0.15,
		true, MULTI_CONNECT, game_title_text);
	text_in_level.add_text("Enter an IP address to LAN connect to or wait for a Connection:", kLevelWidthMultiplier * kWallWidth * 0.1, kLevelHeightMultiplier * kWallWidth * 0.35,
		false, MULTI_CONNECT, character_name);

	//text for multiplayer menu interface
	text_in_level.add_text("Player name:", kLevelWidthMultiplier * kWallWidth * 0.1, kLevelHeightMultiplier * kWallWidth * 0.35,
		false, MULTI_MENU, character_name);
	text_in_level.add_text("Player color:", kLevelWidthMultiplier * kWallWidth * 0.75, kLevelHeightMultiplier * kWallWidth * 0.35,
		false, MULTI_MENU, character_name);
	text_in_level.add_text("Wall settings:", kLevelWidthMultiplier * kWallWidth * 0.1, kLevelHeightMultiplier * kWallWidth * 0.5,
		false, MULTI_MENU, character_name);
	text_in_level.add_text("Few", kLevelWidthMultiplier * kWallWidth * 0.1, kLevelHeightMultiplier * kWallWidth * 0.55,
		false, MULTI_MENU, character_name);
	text_in_level.add_text("Some", kLevelWidthMultiplier * kWallWidth * 0.1, kLevelHeightMultiplier * kWallWidth * 0.60,
		false, MULTI_MENU, character_name);
	text_in_level.add_text("A lot", kLevelWidthMultiplier * kWallWidth * 0.1, kLevelHeightMultiplier * kWallWidth * 0.65,
		false, MULTI_MENU, character_name);
	text_in_level.add_text("2D Shooter Game", kLevelWidthMultiplier * kWallWidth * 0.5, kLevelHeightMultiplier * kWallWidth * 0.15,
		true, MULTI_MENU, game_title_text);

	//text for disconnected interface
	text_in_level.add_text("Your multiplayer session has ended.", kLevelWidthMultiplier * kWallWidth * 0.1, kLevelHeightMultiplier * kWallWidth * 0.35,
		false, DISCONNECTED, character_name);

	text_in_level.add_text("There is already another user connected to this server.", kLevelWidthMultiplier * kWallWidth * 0.1, kLevelHeightMultiplier * kWallWidth * 0.35,
		false, DISCONNECTED_BY_HOST, character_name);

	//add the fonts to the text object to be used in game
	text_in_level.add_font(game_title_text);
	text_in_level.add_font(button_text);
	text_in_level.add_font(character_name);
}