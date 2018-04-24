#pragma once
#include "const.h"
#include "ofMain.h"
#include "ofxCenteredTrueTypeFont.h"
#include <vector>
using namespace std;
class AllButtons {
private:
	struct Button {
		/*
		rectangular properties of the button.
		*/
		int posx_;
		int posy_;
		int xspan_;
		int yspan_;

		/*
		rgb values of the value.
		*/
		int red_;
		int green_;
		int blue_;

		/*
		whether the button was "ticked"; used for color palettes.
		*/
		bool ticked_;

		/*
		text to show on the button.
		*/
		string text_;

		/*
		the screen the button is on (main menu, etc).
		*/
		game_state to_show_;

		/*
		conventional constructor. Ticked defaults to false.
		*/
		Button(int x, int y, int width, int height, int red, int green, int blue, string label, game_state to_show);

		/*
		check whether the point (x,y) is on a button. Also checks whether the interface the button is in matches the one the player is currently in.
		*/
		bool on_button(int x_coord, int y_coord, game_state current);

		/*
		draw the button with the specified font style.
		*/
		void draw_button(ofxCenteredTrueTypeFont text);
	};
	vector<Button> buttons_in_game;
public:
	/*
	default constructor.
	*/
	AllButtons() { vector<Button> buttons(); };

	/*
	add a button. Calls the button constructor.
	*/
	void add_button(int x, int y, int width, int height, int red, int green, int blue, string label, game_state to_show);

	/*
	detects whether the user's cursor is over a button. Returns the cell number of the button if it is, returns -1 otherwise.
	*/
	int on_button(int x_coord, int y_coord, game_state current);

	/*
	draw all the buttons in the current screen.
	*/
	void draw_button(game_state current, ofxCenteredTrueTypeFont text);

	/*
	tick a button; sets the button's ticked parameter to true and every other button in the screen's ticked to false.
	*/
	void tick_button(int button);
};