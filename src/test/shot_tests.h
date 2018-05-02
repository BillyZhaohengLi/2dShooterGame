#pragma once
#include "ofMain.h"
#include "../src/const.h"
#include "../game_assets/player.h"
#include "../game_assets/wall.h"
#include "../game_assets/shot.h"
#include "unit_test.h"

inline void SHOT_TESTS() {
	/*
	SHOT TESTS
	*/
	UNIT_TEST SHOT_TEST = UNIT_TEST("shot class functions tests");
	ShotInLevel test_shots = ShotInLevel();

	//since there are no shots by default in the object, the get_shot_parameters function returns the default value.
	SHOT_TEST.ASSERT_EQUALS("ShotInLevel starts out empty",
		0.0, test_shots.get_shot_parameters(0).first.first, kEpsilon);

	//add a shot aimed at the east direction
	test_shots.add_shot(100, 100, 0);

	//now there is a shot, check whether the x value from get_shot_parameters match our expectations.
	SHOT_TEST.ASSERT_EQUALS("ShotInLevel get shot parameter of first shot",
		100.0, test_shots.get_shot_parameters(0).first.first, kEpsilon);
	//out of bounds index returns the default value
	SHOT_TEST.ASSERT_EQUALS("ShotInLevel get shot parameter out of bounds",
		0.0, test_shots.get_shot_parameters(1).first.first, kEpsilon);

	//add a shot aimed at the west direction
	test_shots.add_shot(200, 200, -kPi);
	test_shots.move();

	//get the new positions of the shots
	SHOT_TEST.ASSERT_EQUALS("Shot move east",
		112.0, test_shots.get_shot_parameters(0).first.first, kEpsilon);
	SHOT_TEST.ASSERT_EQUALS("Shot move west",
		188.0, test_shots.get_shot_parameters(1).first.first, kEpsilon);

	//test serialized string
	string data = test_shots.serialized_string();
	SHOT_TEST.ASSERT_EQUALS("serialized shot string",
		std::string("G112.000000~100.000000~0.000000~188.000000~200.000000~-3.141593~"), data);

	//test deserialize string
	ShotInLevel test_shot2 = ShotInLevel();
	test_shot2.add_shot(999, 999, kPi / 2);

	//deserializing a message overrides whatever was in the ShotInLevel object.
	test_shot2.deserialize_update_message(data.substr(1));

	//get the new positions of the shots
	SHOT_TEST.ASSERT_EQUALS("deserialize shot 1 x position",
		112.0, test_shot2.get_shot_parameters(0).first.first, kEpsilon);
	SHOT_TEST.ASSERT_EQUALS("deserialize shot 1 y position",
		100.0, test_shot2.get_shot_parameters(0).first.second, kEpsilon);
	SHOT_TEST.ASSERT_EQUALS("deserialize shot 1 angle",
		0.0, test_shot2.get_shot_parameters(0).second.first, kEpsilon);

	//deserialized shots always start with the maximum bounces remaining (since they are not handled in the client anyways)
	SHOT_TEST.ASSERT_EQUALS("deserialize shot 1 bounces remaining",
		kShotBounces, test_shot2.get_shot_parameters(0).second.second, kEpsilon);

	SHOT_TEST.ASSERT_EQUALS("deserialize shot 2",
		188.0, test_shot2.get_shot_parameters(1).first.first, kEpsilon);

	//test shot - player collision
	Player p1 = Player(100, 100, kRedPalette, false, "test");
	p1.set_location(112.0, 100.0);
	test_shots.hit_player(p1);
	SHOT_TEST.ASSERT_EQUALS("shot hitting player", false, p1.isalive());

	//test clear shots
	test_shots.clear_shots();
	SHOT_TEST.ASSERT_EQUALS("ShotInLevel cleared",
		0.0, test_shots.get_shot_parameters(0).first.first, kEpsilon);
}