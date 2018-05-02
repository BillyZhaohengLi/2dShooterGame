#pragma once
#include "ofMain.h"
#include "../src/const.h"
#include "../game_addons/button.h"
#include "../game_addons/ofxCenteredTrueTypeFont.h"
#include "unit_test.h"

inline void BUTTON_TESTS() {
	UNIT_TEST BUTTON_TEST = UNIT_TEST("button class functions tests");
	AllButtons test_buttons = AllButtons();
	ofxCenteredTrueTypeFont test_font;
	test_buttons.add_button(100, 100, 100, 100, ofColor::black, "test", vector<GameState>{MAIN_MENU, MULTI_MENU}, test_font);

	//pressing outside the range of any button in the current screen returns -1.
	BUTTON_TEST.ASSERT_EQUALS("pressing outside button range", -1, test_buttons.on_button(0, 0, MAIN_MENU));

	//pressing in the range of a button not in the current screen also returns -1.
	BUTTON_TEST.ASSERT_EQUALS("pressing outside button range", -1, test_buttons.on_button(150, 150, IN_GAME_SINGLE));

	//pressing in the range of a button in the current screen returns the index of the button.
	BUTTON_TEST.ASSERT_EQUALS("pressing on button", 0, test_buttons.on_button(150, 150, MAIN_MENU));

	test_buttons.add_button(100, 100, 100, 100, ofColor::black, "test", vector<GameState>{MAIN_MENU, MULTI_MENU}, test_font);

	//if two buttons overlap in the same screen (which shouldn't happen), the function will return the index of the first button
	//to be created. (the one with the lower index).
	BUTTON_TEST.ASSERT_EQUALS("pressing on button", 0, test_buttons.on_button(150, 150, MAIN_MENU));
}