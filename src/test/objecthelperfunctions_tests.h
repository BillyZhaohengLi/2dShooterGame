#pragma once
#include "ofMain.h"
#include "../src/const.h"
#include "../src/helpers/helperfunctions.h"
#include "UNIT_TEST.h"

//tests for functions in the objecthelperfunctions file
inline void OBJECTHELPERFUNCTIONS_TESTS() {
	UNIT_TEST OBJECTHF_TEST = UNIT_TEST("helperfunction class tests");

	//add players and kill them
	Player p1 = Player(100, 100, kRedPalette, false, "default");
	Player p2 = Player(100, 100, kRedPalette, false, "default2");
	p1.kill_player();
	p2.kill_player();

	//add level elements to mimic a game
	ShotInLevel test_shots = ShotInLevel();
	Wall levelbounds = Wall();
	test_shots.add_shot(100, 100, 0);
	levelbounds.add_boundary();
	levelbounds.add_wall(100, 100, 100, 100);

	bool keydown[255];
	keydown[kUp] = true;

	//test reset_game
	reset_game(p1, p2, test_shots, keydown);

	OBJECTHF_TEST.ASSERT_EQUALS("reset_game - revive player", true, p1.isalive());
	OBJECTHF_TEST.ASSERT_EQUALS("reset_game - clear shots", 0.0, 
		test_shots.get_shot_parameters(0).first.first, kEpsilon);
	OBJECTHF_TEST.ASSERT_EQUALS("reset_game - clear keys", false, keydown[kUp]);
	OBJECTHF_TEST.ASSERT_EQUALS("reset_game - don't clear walls", true,
		levelbounds.intersect(100,100,100,100));

	//recreate the scenario and test reset_to_menu
	p1.kill_player();
	p2.kill_player();
	test_shots.add_shot(100, 100, 0);
	keydown[kUp] = true;
	reset_to_menu(p1, p2, test_shots, levelbounds, HOST, keydown);

	OBJECTHF_TEST.ASSERT_EQUALS("reset_to_menu - revive player", true, p1.isalive());
	OBJECTHF_TEST.ASSERT_EQUALS("reset_to_menu - player position", 
		kLevelWidthMultiplier * kWallWidth * 0.45, p1.get_location().first, kEpsilon);
	OBJECTHF_TEST.ASSERT_EQUALS("reset_to_menu - clear shots", 0.0,
		test_shots.get_shot_parameters(0).first.first, kEpsilon);
	OBJECTHF_TEST.ASSERT_EQUALS("reset_to_menu - clear keys", false, keydown[kUp]);
	OBJECTHF_TEST.ASSERT_EQUALS("reset_to_menu - clear walls", false,
		levelbounds.intersect(100, 100, 100, 100));

	//test round over messages
	//nothing is generated if both players are alive, but the function is never called
	//if the players are in this state.
	OBJECTHF_TEST.ASSERT_EQUALS("gameover message - both players alive",
		std::string(""), generate_game_over_message(p1, p2));
	p1.kill_player();
	OBJECTHF_TEST.ASSERT_EQUALS("gameover message - one player dead",
		std::string("default2 wins!"), generate_game_over_message(p1, p2));
	p2.kill_player();
	OBJECTHF_TEST.ASSERT_EQUALS("gameover message - both players dead",
		std::string("It's a tie."), generate_game_over_message(p1, p2));

}