#pragma once
#include "ofMain.h"
#include "../src/const.h"
#include "../game_assets/player.h"
#include "../game_assets/wall.h"
#include "../game_assets/shot.h"
#include "UNIT_TEST.h"

/*
unit tests for the player class.
*/
inline void PLAYER_TESTS() {
	/*
	PLAYER TESTS
	*/
	UNIT_TEST PLAYER_TEST = UNIT_TEST("player class functions tests");
	Player p1 = Player(100, 200, kRedPalette, false, "Default");

	//test location
	PLAYER_TEST.ASSERT_EQUALS("test location X", 100.0, p1.get_location().first, kEpsilon);
	PLAYER_TEST.ASSERT_EQUALS("test location Y", 200.0, p1.get_location().second, kEpsilon);
	PLAYER_TEST.ASSERT_EQUALS("test aliveness", true, p1.isalive());
	PLAYER_TEST.ASSERT_EQUALS("test initial weapon cooldown", false, p1.can_shoot());
	PLAYER_TEST.ASSERT_EQUALS("test color", 0, p1.get_color());
	PLAYER_TEST.ASSERT_EQUALS("test name", std::string("Default"), p1.get_name());

	//this might sometimes fail due to double precision error.
	PLAYER_TEST.ASSERT_EQUALS("test serialized game string",
		std::string("G100.000000~200.000000~0~0~15~T"), p1.serialized_game_string());
	PLAYER_TEST.ASSERT_EQUALS("test serialized model string",
		std::string("PLAYER0~Default~0~0"), p1.serialized_model_string());

	//test deserialize strings
	Player p2 = Player(400, 500, kCyanPalette, false, "aaa");
	p2.deserialize_update_game_message(p1.serialized_game_string().substr(1));
	p2.deserialize_update_model_message(p1.serialized_model_string());

	//p2 is now the same as p1.
	PLAYER_TEST.ASSERT_EQUALS("test location X p2", 100.0, p2.get_location().first, kEpsilon);
	PLAYER_TEST.ASSERT_EQUALS("test location Y p2", 200.0, p2.get_location().second, kEpsilon);
	PLAYER_TEST.ASSERT_EQUALS("test aliveness p2", true, p2.isalive());
	PLAYER_TEST.ASSERT_EQUALS("test initial weapon cooldown p2", false, p2.can_shoot());
	PLAYER_TEST.ASSERT_EQUALS("test color p2", 0, p2.get_color());
	PLAYER_TEST.ASSERT_EQUALS("test name p2", std::string("Default"), p2.get_name());

	//cooldown the player's weapon
	for (int i = 0; i < kPlayerShotCooldown; i++) {
		p1.cooldown_reduce();
	}
	PLAYER_TEST.ASSERT_EQUALS("test weapon cooldown function", true, p1.can_shoot());

	//test move
	p1.move();
	PLAYER_TEST.ASSERT_EQUALS("move location X - stop", 100.0, p1.get_location().first, kEpsilon);
	PLAYER_TEST.ASSERT_EQUALS("move location Y - stop", 200.0, p1.get_location().second, kEpsilon);

	//moving in a cardinal direction
	p1.change_direction({ true, false, false, false });
	p1.move();
	PLAYER_TEST.ASSERT_EQUALS("move location X - up", 100.0, p1.get_location().first, kEpsilon);
	PLAYER_TEST.ASSERT_EQUALS("move location Y - up", 
		200.0 - kPlayerVelocity, p1.get_location().second, kEpsilon);

	//moving in a diagonal direction
	p1.change_direction({ true, true, false, false });
	p1.move();
	PLAYER_TEST.ASSERT_EQUALS("move location X - up&left", 
		100 - kPlayerVelocity / sqrt(2), p1.get_location().first, kEpsilon);
	PLAYER_TEST.ASSERT_EQUALS("move location Y - up&left", 
		200 - kPlayerVelocity - kPlayerVelocity / sqrt(2), p1.get_location().second, kEpsilon);

	//holding down opposite buttons cancel each other out
	p1.change_direction({ true, false, true, false });
	p1.move();
	PLAYER_TEST.ASSERT_EQUALS("move location X - cancel", 
		100 - kPlayerVelocity / sqrt(2), p1.get_location().first, kEpsilon);
	PLAYER_TEST.ASSERT_EQUALS("move location Y - cancel", 
		200 - kPlayerVelocity - kPlayerVelocity / sqrt(2), p1.get_location().second, kEpsilon);

	p1.kill_player();
	PLAYER_TEST.ASSERT_EQUALS("test kill player", false, p1.isalive());

	//revive the player at the given location
	//this does not revive the player.
	p1.set_location(100, 100);
	PLAYER_TEST.ASSERT_EQUALS("test set location revive", false, p1.isalive());

	//this does;
	p1.reset_player(100, 100);
	PLAYER_TEST.ASSERT_EQUALS("test reset player revive", true, p1.isalive());
	PLAYER_TEST.ASSERT_EQUALS("test reset player shot cooldown", false, p1.can_shoot());

	//update aim and try to fire a shot; fails because weapon on cooldown
	p1.update_player_facing(200, 100, p1);
	pair<pair<bool, double>, pair<double, double>> shot_params = p1.shoot_prompt(true, false);
	PLAYER_TEST.ASSERT_EQUALS("test shooting on cooldown", false, shot_params.first.first);

	//cooldown the player's weapon
	for (int i = 0; i < kPlayerShotCooldown; i++) {
		p1.cooldown_reduce();
	}

	//the player fires a shot to the east
	shot_params = p1.shoot_prompt(true, false);
	PLAYER_TEST.ASSERT_EQUALS("test shooting off cooldown", true, shot_params.first.first);
	PLAYER_TEST.ASSERT_EQUALS("test shot angle", 0.0, shot_params.first.second, kEpsilon);
	PLAYER_TEST.ASSERT_EQUALS("test shot x position", 100 + kPlayerRadius - kShotLength +
		kShotRadius + kEpsilon, shot_params.second.first, kEpsilon);
	PLAYER_TEST.ASSERT_EQUALS("test shot y position", 100.0, shot_params.second.second, kEpsilon);

	//set the player to be a bot and test on what conditions the bot fires
	for (int i = 0; i < kPlayerShotCooldown; i++) {
		p1.cooldown_reduce();
	}
	p1.set_bot(true);

	//create an enemy for the bot
	Player p3 = Player(200, 200, kRedPalette, false, "Default");
	p1.update_player_facing(0, 0, p3);

	//the bot does not fire a shot if there are obstacles between the players - obstructed is true
	shot_params = p1.shoot_prompt(false, true);
	PLAYER_TEST.ASSERT_EQUALS("test shooting off cooldown bot - no clear shot", 
		false, shot_params.first.first);

	//however the bot shoots regardless of whether the mouse is held down or not
	//the bot fires diagonally at the opponent
	shot_params = p1.shoot_prompt(false, false);
	PLAYER_TEST.ASSERT_EQUALS("test shooting off cooldown bot - clear shot", 
		true, shot_params.first.first);
	PLAYER_TEST.ASSERT_EQUALS("test bot shot angle at opponent", 
		kPi / 4, shot_params.first.second, kEpsilon);
}