#pragma once
#include "const.h"
#include "ofMain.h"
#include "ofxCenteredTrueTypeFont.h"
#include <vector>
using namespace std;
//class for buttons in the level.
class AllButtons {
private:
	//internal struct; individual buttons.
	struct Button {
		/*
		rectangular properties of the button.
		*/
		int xpos_;
		int ypos_;
		int xspan_;
		int yspan_;

		/*
		rgb values of the button.
		*/
		ofColor color_;

		/*
		whether the button was "ticked"; used for color palettes.
		*/
		bool ticked_;

		/*
		text to show on the button.
		*/
		string label_;

		/*
		the screen the button is on (main menu, etc).
		*/
		vector<GameState> to_show_;

		/*
		the font to be used for the text on the button.
		*/
		ofxCenteredTrueTypeFont font_;

		/*
		conventional constructor. Ticked defaults to false.
		*/
		Button(int x, int y, int width, int height, ofColor color, string label, vector<GameState> to_show, ofxCenteredTrueTypeFont font);

		/*
		check whether the point (x,y) is on a button. Also checks whether the interface the button is in matches the one the player is currently in.
		*/
		bool on_button(int x_coord, int y_coord, GameState current);

		/*
		draw the button with the specified font style.
		*/
		void draw_button();
	};
	vector<Button> buttons_in_game;
public:
	/*
	add a button. Calls the button constructor.
	*/
	void add_button(int x, int y, int width, int height, ofColor color, string label, vector<GameState> to_show, ofxCenteredTrueTypeFont font);

	/*
	detects whether the user's cursor is over a button. Returns the cell number of the button if it is, returns -1 otherwise.
	*/
	int on_button(int x_coord, int y_coord, GameState current);

	/*
	draw all the buttons in the current screen.
	*/
	void draw_button(GameState current);

	/*
	tick a button; sets the button's ticked parameter to true.
	*/
	void tick_button(int button);

	/*
	untick a button; sets the button's ticked parameter to false.
	*/
	void untick_button(int button);
};