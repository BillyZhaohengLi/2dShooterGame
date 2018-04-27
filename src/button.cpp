#include "button.h"
/*
button constructor.
*/
AllButtons::Button::Button(int x, int y, int width, int height, 
	int red, int green, int blue, string label, vector<game_state> to_show) {
	posx_ = x;
	posy_ = y;
	xspan_ = width;
	yspan_ = height;
	red_ = red;
	green_ = green;
	blue_ = blue;
	text_ = label;
	to_show_ = to_show;
	ticked_ = false;
}

/*
check whether the point (x,y) is on a button. Also checks whether the interface the button is in matches the one the player is currently in.
*/
bool AllButtons::Button::on_button(int x_coord, int y_coord, game_state current) {
	if (x_coord >= posx_ && x_coord <= posx_ + xspan_ &&
		y_coord >= posy_ && y_coord <= posy_ + yspan_) {
		for (int i = 0; i < to_show_.size(); i++) {
			if (to_show_[i] == current) {
				return true;
			}
		}
	}
	return false;
}

/*
draw the button with the specified font style.
*/
void AllButtons::Button::draw_button(ofxCenteredTrueTypeFont text) {
	//roll over
	if (ofGetMouseX() >= posx_ && ofGetMouseX() <= posx_ + xspan_ 
		&& ofGetMouseY() >= posy_ && ofGetMouseY() <= posy_ + yspan_) {
		ofSetColor(127 + red_ / 2, 127 + green_ / 2, 127 + blue_ / 2);
	}
	else {
		ofSetColor(red_, green_, blue_);
	}
	ofDrawRectangle(posx_, posy_, xspan_, yspan_);
	ofSetColor(0, 0, 0);
	ofSetLineWidth(4);
	ofDrawLine(posx_, posy_, posx_, posy_ + yspan_);
	ofDrawLine(posx_, posy_, posx_ + xspan_, posy_);
	ofDrawLine(posx_ + xspan_, posy_, posx_ + xspan_, posy_ + yspan_);
	ofDrawLine(posx_, posy_ + yspan_, posx_ + xspan_, posy_ + yspan_);
	if (ticked_) {
		ofDrawLine(posx_, posy_, posx_ + xspan_, posy_ + yspan_);
		ofDrawLine(posx_, posy_ + yspan_, posx_ + xspan_, posy_);
	}
	text.drawStringCentered(text_, posx_ + xspan_ / 2, posy_ + yspan_ / 2);
}

/*
add a button. Calls the button constructor.
*/
void AllButtons::add_button(int x, int y, int width, int height, int red, int green, int blue, string label, vector<game_state> to_show) {
	Button temp = Button(x, y, width, height, red, green, blue, label, to_show);
	buttons_in_game.push_back(temp);
}

/*
detects whether the user's cursor is over a button. Returns the cell number of the button if it is, returns -1 otherwise.
*/
int AllButtons::on_button(int x_coord, int y_coord, game_state current) {
	for (int i = 0; i < buttons_in_game.size(); i++) {
		if (buttons_in_game[i].on_button(x_coord, y_coord, current)) {
			return i;
		}
	}
	return -1;
}

/*
draw all the buttons in the current screen.
*/
void AllButtons::draw_button(game_state current, ofxCenteredTrueTypeFont text) {
	for (int i = 0; i < buttons_in_game.size(); i++) {
		for (int j = 0; j < buttons_in_game[i].to_show_.size(); j++) {
			if (buttons_in_game[i].to_show_[j] == current) {
				buttons_in_game[i].draw_button(text);
				break;
			}
		}
	}
}

/*
tick a button; sets the button's ticked parameter to true and every other button in the screen's ticked to false.
*/
void AllButtons::tick_button(int button) {
	for (int i = 0; i < buttons_in_game.size(); i++) {
		if (i == button) {
			buttons_in_game[i].ticked_ = true;
		}
	}
}

void AllButtons::untick_button(int button) {
	for (int i = 0; i < buttons_in_game.size(); i++) {
		if (i == button) {
			buttons_in_game[i].ticked_ = false;
		}
	}
}