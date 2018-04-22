#pragma once
#include "const.h"
#include "ofMain.h"
#include "ofxCenteredTrueTypeFont.h"
#include <vector>
using namespace std;
class AllButtons {
private:
	struct Button {
		int posx_;
		int posy_;
		int xspan_;
		int yspan_;
		string text_;
		game_state to_show_;
		Button(int x, int y, int width, int height, string label, game_state to_show);
		bool on_button(int x_coord, int y_coord, game_state current);
		void draw_button(ofxCenteredTrueTypeFont text);
	};
	vector<Button> buttons_in_game;
public:
	AllButtons() { vector<Button> buttons(); };
	void add_button(int x, int y, int width, int height, string label, game_state to_show);
	int on_button(int x_coord, int y_coord, game_state current);
	void draw_button(game_state current, ofxCenteredTrueTypeFont text);
};