#include "button.h"
/*
button constructor.
*/
AllButtons::Button::Button(int x, int y, int width, int height, 
	ofColor color, string label, vector<GameState> to_show, ofxCenteredTrueTypeFont font) {
	xpos_ = x;
	ypos_ = y;
	xspan_ = width;
	yspan_ = height;
	color_ = color;
	label_ = label;
	to_show_ = to_show;
	ticked_ = false;
	font_ = font;
}

/*
check whether the point (x,y) is on a button. Also checks whether the interface the button is in 
matches the one the player is currently in.
*/
bool AllButtons::Button::on_button(int x_coord, int y_coord, GameState current) {
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
	//rolling over the button will cause it to be drawn in a lighter color.
	if (ofGetMouseX() >= xpos_ && ofGetMouseX() <= xpos_ + xspan_ 
		&& ofGetMouseY() >= ypos_ && ofGetMouseY() <= ypos_ + yspan_) {
		ofSetColor(color_ + ofColor::gray);
	}
	else {
		ofSetColor(color_);
	}

	//draw the button body
	ofDrawRectangle(xpos_, ypos_, xspan_, yspan_);

	//button outline
	ofSetColor(ofColor::black);
	ofSetLineWidth(4);
	ofDrawLine(xpos_, ypos_, xpos_, ypos_ + yspan_);
	ofDrawLine(xpos_, ypos_, xpos_ + xspan_, ypos_);
	ofDrawLine(xpos_ + xspan_, ypos_, xpos_ + xspan_, ypos_ + yspan_);
	ofDrawLine(xpos_, ypos_ + yspan_, xpos_ + xspan_, ypos_ + yspan_);

	//if the button is ticked draw a cross on it
	if (ticked_) {
		ofDrawLine(xpos_, ypos_, xpos_ + xspan_, ypos_ + yspan_);
		ofDrawLine(xpos_, ypos_ + yspan_, xpos_ + xspan_, ypos_);
	}

	//draw the text of the button
	font_.drawStringCentered(label_, xpos_ + xspan_ / 2, ypos_ + yspan_ / 2);
}

/*
add a button. Calls the button constructor.
*/
void AllButtons::add_button(int x, int y, int width, int height, ofColor color, string label, 
	vector<GameState> to_show, ofxCenteredTrueTypeFont font) {
	Button temp = Button(x, y, width, height, color, label, to_show, font);
	buttons_in_game.push_back(temp);
}

/*
detects whether the user's cursor is over a button. Returns the cell number of the button if it is, 
returns -1 otherwise.
*/
int AllButtons::on_button(int x_coord, int y_coord, GameState current) {
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
void AllButtons::draw_button(GameState current) {
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
tick a button; sets the button's ticked parameter to true.
*/
void AllButtons::tick_button(int button) {
	for (int i = 0; i < buttons_in_game.size(); i++) {
		if (i == button) {
			buttons_in_game[i].ticked_ = true;
		}
	}
}

/*
untick a button; sets the button's ticked parameter to false.
*/
void AllButtons::untick_button(int button) {
	for (int i = 0; i < buttons_in_game.size(); i++) {
		if (i == button) {
			buttons_in_game[i].ticked_ = false;
		}
	}
}