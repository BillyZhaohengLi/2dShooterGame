#pragma once
#include "ofMain.h"
#include "const.h"
#include "ofxCenteredTrueTypeFont.h"
//class for all text in the game.
class AllText {
private:
	//internal struct for individual text snippets.
	struct GameText {
		/*
		content of the text. Self explanatory.
		*/
		string content_;

		/*
		x and y coordinates of the text.
		*/
		int xpos_;
		int ypos_;

		/*
		whether the text is center aligned.
		*/
		bool centered_;

		/*
		the interface the text is in.
		*/
		game_state to_show_;

		/*
		the font the text is in.
		*/
		ofxCenteredTrueTypeFont font_;

		/*
		typical constructor.
		*/
		GameText(string content, int xpos, int ypos, bool centered, game_state to_show, ofxCenteredTrueTypeFont font);

		/*
		draw the text using the allocated font.
		*/
		void draw_text();
	};

	/*
	vector containing all individual text snippets in the program.
	*/
	vector<GameText> text_in_game;

	/*
	vector containing all fonts used in the program.
	*/
	vector<ofxCenteredTrueTypeFont> fonts_in_game;
public:
	/*
	add a text snippet. Calls the GameText constructor.
	*/
	void add_text(string content, int xpos, int ypos, bool centered, game_state to_show, ofxCenteredTrueTypeFont font);

	/*
	add a font.
	*/
	void add_font(ofxCenteredTrueTypeFont font);

	/*
	draw all text in the current interface. Calls the draw methods of GameText objects.
	*/
	void draw_text(game_state game_current);

	/*
	draw a string using a pre-existing font. Used to draw dynamic strings such as names and ip addresses.
	*/
	void draw_dynamic_text(string content, int xpos, int ypos, bool centered, int text_style);
};