#include "gametext.h"
/*
typical constructor.
*/
AllText::GameText::GameText(string content, int xpos, int ypos, bool centered, GameState to_show, ofxCenteredTrueTypeFont font) {
	content_ = content;
	xpos_ = xpos;
	ypos_ = ypos;
	centered_ = centered;
	to_show_ = to_show;
	font_ = font;
}

/*
draw the text using the allocated font.
*/
void AllText::GameText::draw_text() {
	if (centered_) {
		font_.drawStringCentered(content_, xpos_, ypos_);
	}
	else {
		font_.drawString(content_, xpos_, ypos_);
	}
}

/*
add a text snippet. Calls the GameText constructor.
*/
void AllText::add_text(string content, int xpos, int ypos, bool centered, GameState to_show, ofxCenteredTrueTypeFont font) {
	GameText temp = GameText(content, xpos, ypos, centered, to_show, font);
	text_in_game.push_back(temp);
}

/*
add a font.
*/
void AllText::add_font(ofxCenteredTrueTypeFont font) {
	fonts_in_game.push_back(font);
}

/*
draw all text in the current interface. Calls the draw methods of GameText objects.
*/
void AllText::draw_text(GameState game_current) {
	for (int i = 0; i < text_in_game.size(); i++) {
		if (game_current == text_in_game[i].to_show_) {
			text_in_game[i].draw_text();
		}
	}
}

/*
draw a string using a pre-existing font. Used to draw dynamic strings such as names and ip addresses.
*/
void AllText::draw_dynamic_text(string content, int xpos, int ypos, bool centered, int text_style) {
	ofSetColor(0, 0, 0);
	for (int i = 0; i < fonts_in_game.size(); i++) {
		if (text_style == i) {
			if (centered) {
				fonts_in_game[i].drawStringCentered(content, xpos, ypos);
			}
			else {
				fonts_in_game[i].drawString(content, xpos, ypos);
			}
		}
	}
}