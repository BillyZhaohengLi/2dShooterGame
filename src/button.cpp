#include "button.h"
/*
button constructor.
*/
AllButtons::Button::Button(int x, int y, int width, int height, 
	int red, int green, int blue, string label, vector<game_state> to_show, ofxCenteredTrueTypeFont font) {
	xpos_ = x;
	ypos_ = y;
	xspan_ = width;
	yspan_ = height;
	red_ = red;
	green_ = green;
	blue_ = blue;
	label_ = label;
	to_show_ = to_show;
	ticked_ = false;
	font_ = font;
}

/*
check whether the point (x,y) is on a button. Also checks whether the interface the button is in matches the one the player is currently in.
*/
bool AllButtons::Button::on_button(int x_coord, int y_coord, game_state current) {
	if (x_coord >= xpos_ && x_coord <= xpos_ + xspan_ &&
		y_coord >= ypos_ && y_coord <= ypos_ + yspan_) {
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
void AllButtons::Button::draw_button() {
	//roll over
	if (ofGetMouseX() >= xpos_ && ofGetMouseX() <= xpos_ + xspan_ 
		&& ofGetMouseY() >= ypos_ && ofGetMouseY() <= ypos_ + yspan_) {
		ofSetColor(127 + red_ / 2, 127 + green_ / 2, 127 + blue_ / 2);
	}
	else {
		ofSetColor(red_, green_, blue_);
	}
	ofDrawRectangle(xpos_, ypos_, xspan_, yspan_);
	ofSetColor(0, 0, 0);
	ofSetLineWidth(4);
	ofDrawLine(xpos_, ypos_, xpos_, ypos_ + yspan_);
	ofDrawLine(xpos_, ypos_, xpos_ + xspan_, ypos_);
	ofDrawLine(xpos_ + xspan_, ypos_, xpos_ + xspan_, ypos_ + yspan_);
	ofDrawLine(xpos_, ypos_ + yspan_, xpos_ + xspan_, ypos_ + yspan_);
	if (ticked_) {
		ofDrawLine(xpos_, ypos_, xpos_ + xspan_, ypos_ + yspan_);
		ofDrawLine(xpos_, ypos_ + yspan_, xpos_ + xspan_, ypos_);
	}
	font_.drawStringCentered(label_, xpos_ + xspan_ / 2, ypos_ + yspan_ / 2);
}

/*
add a button. Calls the button constructor.
*/
void AllButtons::add_button(int x, int y, int width, int height, int red, int green, int blue, string label, vector<game_state> to_show, ofxCenteredTrueTypeFont font) {
	Button temp = Button(x, y, width, height, red, green, blue, label, to_show, font);
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
void AllButtons::draw_button(game_state current) {
	for (int i = 0; i < buttons_in_game.size(); i++) {
		for (int j = 0; j < buttons_in_game[i].to_show_.size(); j++) {
			if (buttons_in_game[i].to_show_[j] == current) {
				buttons_in_game[i].draw_button();
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