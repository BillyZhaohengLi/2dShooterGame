#include "button.h"
AllButtons::Button::Button(int x, int y, int width, int height, string label, game_state to_show) {
	posx_ = x;
	posy_ = y;
	xspan_ = width;
	yspan_ = height;
	text_ = label;
	to_show_ = to_show;
}

bool AllButtons::Button::on_button(int x_coord, int y_coord, game_state current) {
	return (x_coord >= posx_ && x_coord <= posx_ + xspan_ && y_coord >= posy_ && y_coord <= posy_ + yspan_ && current == to_show_);
}

void AllButtons::Button::draw_button(ofxCenteredTrueTypeFont text) {
	//roll overe
	if (ofGetMouseX() >= posx_ && ofGetMouseX() <= posx_ + xspan_ && ofGetMouseY() >= posy_ && ofGetMouseY() <= posy_ + yspan_) {
		ofSetColor(0, 255, 0);
	}
	else {
		ofSetColor(128, 255, 128);
	}
	ofDrawRectangle(posx_, posy_, xspan_, yspan_);
	ofSetColor(0, 0, 0);
	ofSetLineWidth(4);
	ofDrawLine(posx_, posy_, posx_, posy_ + yspan_);
	ofDrawLine(posx_, posy_, posx_ + xspan_, posy_);
	ofDrawLine(posx_ + xspan_, posy_, posx_ + xspan_, posy_ + yspan_);
	ofDrawLine(posx_, posy_ + yspan_, posx_ + xspan_, posy_ + yspan_);
	text.drawStringCentered(text_, posx_ + xspan_ / 2, posy_ + yspan_ / 2);
}

void AllButtons::add_button(int x, int y, int width, int height, string label, game_state to_show) {
	Button temp = Button(x, y, width, height, label, to_show);
	buttons_in_game.push_back(temp);
}

int AllButtons::on_button(int x_coord, int y_coord, game_state current) {
	for (int i = 0; i < buttons_in_game.size(); i++) {
		if (buttons_in_game[i].on_button(x_coord, y_coord, current)) {
			return i;
		}
	}
	return -1;
}

void AllButtons::draw_button(game_state current, ofxCenteredTrueTypeFont text) {
	for (int i = 0; i < buttons_in_game.size(); i++) {
		if (buttons_in_game[i].to_show_ == current) {
			buttons_in_game[i].draw_button(text);
		}
	}
}