#pragma once
#include "ofMain.h"
#include "../src/const.h"
#include "../game_assets/player.h"
#include "../game_assets/wall.h"
#include "../game_assets/shot.h"
#include "UNIT_TEST.h"

/*
unit tests for the wall class.
*/
inline void WALL_TESTS() {
	UNIT_TEST WALL_TEST = UNIT_TEST("wall object tests");
	Wall levelbounds = Wall();

	levelbounds.add_boundary();
	//test whether an empty level has a path between 2 players. We expect this to be true.
	WALL_TEST.ASSERT_EQUALS("empty level path checker", false, levelbounds.closed_path_checker());

	//add a big vertical wall in the middle of the level
	levelbounds.add_wall(kLevelWidthMultiplier * kWallWidth / 2, 0, 
		kWallWidth, kLevelHeightMultiplier * kWallWidth);
	//the level is now blocked off.
	WALL_TEST.ASSERT_EQUALS("nonempty level path checker", true, levelbounds.closed_path_checker());

	levelbounds.clear_level();
	//the level is empty again.
	WALL_TEST.ASSERT_EQUALS("test clear level", false, levelbounds.closed_path_checker());

	//test empty level serialized string
	WALL_TEST.ASSERT_EQUALS("empty level serialized string", 
		std::string(""), levelbounds.serialized_string());
	
	//test obstructed vision between players; currently there is a clear path between p1 and p2.
	Player p1 = Player(50, 150, kRedPalette, false, "test1");
	Player p2 = Player(300, 150, kRedPalette, false, "test2");

	WALL_TEST.ASSERT_EQUALS("non-obstructed line between players", 
		false, levelbounds.player_path_obstructed(p1, p2));

	//add some walls
	levelbounds.add_wall(100, 101, 102, 103);
	levelbounds.add_wall(200, 201, 202, 203);

	//there is no longer a clear path between p1 and p2.
	WALL_TEST.ASSERT_EQUALS("obstructed line between players", 
		true, levelbounds.player_path_obstructed(p1, p2));

	//test non-empty level serialized string
	WALL_TEST.ASSERT_EQUALS("non-empty level serialized string", 
		std::string("100" + std::string(kSmallDelimiter) + "101" + std::string(kSmallDelimiter) +
			"102" + std::string(kSmallDelimiter) + "103" + std::string(kSmallDelimiter) +
			"200" + std::string(kSmallDelimiter) + "201" + std::string(kSmallDelimiter) +
			"202" + std::string(kSmallDelimiter) + "203" + std::string(kSmallDelimiter)),
		levelbounds.serialized_string());

	//test deserialize string;
	Wall test_wall2 = Wall();
	test_wall2.deserialize_update_message(levelbounds.serialized_string());

	WALL_TEST.ASSERT_EQUALS("deserialize wall message test", 
		true, test_wall2.player_path_obstructed(p1, p2));

	//test intersections: touching borders
	WALL_TEST.ASSERT_EQUALS("wall intersection for touching walls",
		false, levelbounds.intersect(kWallWidth, kWallWidth, kWallWidth, kWallWidth));

	//test intersections: non-touching borders
	WALL_TEST.ASSERT_EQUALS("wall intersection for non-touching walls",
		false, levelbounds.intersect((kLevelHeightMultiplier - 3) * kWallWidth, 
			3 * kWallWidth, kWallWidth, kWallWidth));

	//test intersections: intersect with spawn area
	WALL_TEST.ASSERT_EQUALS("wall intersection for spawn area",
		true, levelbounds.intersect_with_spawn((kLevelWidthMultiplier - 3) * kWallWidth,
			3 * kWallWidth, kWallWidth, kWallWidth));

	//test intersections: overlapping walls
	WALL_TEST.ASSERT_EQUALS("wall intersection for spawn area",
		true, levelbounds.intersect(0, 0, kWallWidth, kWallWidth));

	//test player-wall collisions
	levelbounds.clear_level();
	levelbounds.add_wall(100, 100, 100, 100);

	//test collision into wall on side
	p1.set_location(100, kWallWidth + kPlayerRadius - 1);
	levelbounds.collision_resolver(p1);
	WALL_TEST.ASSERT_EQUALS("player-wall collision - side of wall",
		kWallWidth + kPlayerRadius + kEpsilon, p1.get_location().second, kEpsilon);

	//test collision into corner created by two walls
	p1.set_location(kWallWidth + kPlayerRadius - 1, kWallWidth + kPlayerRadius - 1);
	levelbounds.collision_resolver(p1);
	WALL_TEST.ASSERT_EQUALS("player-wall collision - corner of two walls x",
		kWallWidth + kPlayerRadius + kEpsilon, p1.get_location().first, kEpsilon);
	WALL_TEST.ASSERT_EQUALS("player-wall collision - corner of two walls y",
		kWallWidth + kPlayerRadius + kEpsilon, p1.get_location().second, kEpsilon);

	//test collision into corner of one wall
	p1.set_location(95, 95);
	levelbounds.collision_resolver(p1);
	WALL_TEST.ASSERT_EQUALS("player-wall collision - corner of one wall x",
		100 - kPlayerRadius / sqrt(2) - kEpsilon, p1.get_location().first, kEpsilon);
	WALL_TEST.ASSERT_EQUALS("player-wall collision - corner of one wall y",
		100 - kPlayerRadius / sqrt(2) - kEpsilon, p1.get_location().second, kEpsilon);

	//test shot-wall collision
	ShotInLevel test_shots = ShotInLevel();
	test_shots.add_shot(kWallWidth - 2, 100, 3 * kPi / 4);
	levelbounds.bounce_shots(test_shots);

	WALL_TEST.ASSERT_EQUALS("shot bouncing off side of wall - x position",
		kWallWidth + 2.0, test_shots.get_shot_parameters(0).first.first, kEpsilon);
	WALL_TEST.ASSERT_EQUALS("shot bouncing off side of wall - y position",
		100.0, test_shots.get_shot_parameters(0).first.second, kEpsilon);
	WALL_TEST.ASSERT_EQUALS("shot bouncing off side of wall - angle",
		kPi / 4, test_shots.get_shot_parameters(0).second.first, kEpsilon);
	WALL_TEST.ASSERT_EQUALS("shot bouncing off side of wall - bounces_remaining",
		kShotBounces - 1, test_shots.get_shot_parameters(0).second.second);

	//test shot-wall collision for bouncing off corner of one wall (see scenario (4) of explantions.txt)
	test_shots.add_shot(102, 103, kPi / 4);
	levelbounds.bounce_shots(test_shots);
	WALL_TEST.ASSERT_EQUALS("shot bouncing off corner of one wall - x position",
		98.0, test_shots.get_shot_parameters(1).first.first, kEpsilon);
	WALL_TEST.ASSERT_EQUALS("shot bouncing off corner of one wall - y position",
		103.0, test_shots.get_shot_parameters(1).first.second, kEpsilon);
	WALL_TEST.ASSERT_EQUALS("shot bouncing off corner of one wall - angle",
		3 * kPi / 4, test_shots.get_shot_parameters(1).second.first, kEpsilon);
	WALL_TEST.ASSERT_EQUALS("shot bouncing off corner of one wall - bounces_remaining",
		kShotBounces - 1, test_shots.get_shot_parameters(1).second.second);

	//the first shot created was not bounced this frame.
	WALL_TEST.ASSERT_EQUALS("shot not bounced - bounces_remaining",
		kShotBounces - 1, test_shots.get_shot_parameters(0).second.second);

	test_shots.clear_shots();
	levelbounds.add_wall(200, 200, 100, 100);

	//test shot-wall collision for bouncing into corner of two walls touching sides 
	//(see scenario (2) of explanations.txt)
	test_shots.add_shot(kWallWidth - 2, kWallWidth - 1, -3 * kPi / 4);
	levelbounds.bounce_shots(test_shots);
	WALL_TEST.ASSERT_EQUALS("shot bouncing off corner of two walls touching sides - x position",
		kWallWidth + 2.0, test_shots.get_shot_parameters(0).first.first, kEpsilon);
	WALL_TEST.ASSERT_EQUALS("shot bouncing off corner of two walls touching sides - y position",
		kWallWidth + 1.0, test_shots.get_shot_parameters(0).first.second, kEpsilon);
	WALL_TEST.ASSERT_EQUALS("shot bouncing off corner of two walls touching sides - angle",
		kPi / 4, test_shots.get_shot_parameters(0).second.first, kEpsilon);
	WALL_TEST.ASSERT_EQUALS("shot bouncing off corner of two walls touching sides - bounces_remaining",
		kShotBounces - 2, test_shots.get_shot_parameters(0).second.second);

	//test shot-wall collision for bouncing into corner of two walls touching corners 
	//(see scenario (3) of explanations.txt)
	test_shots.add_shot(202, 199, -kPi / 4);
	levelbounds.bounce_shots(test_shots);
	WALL_TEST.ASSERT_EQUALS("shot bouncing off corner of two walls touching corners - x position",
		198.0, test_shots.get_shot_parameters(1).first.first, kEpsilon);
	WALL_TEST.ASSERT_EQUALS("shot bouncing off corner of two walls touching corners - y position",
		201.0, test_shots.get_shot_parameters(1).first.second, kEpsilon);
	WALL_TEST.ASSERT_EQUALS("shot bouncing off corner of two walls touching corners - angle",
		3 * kPi / 4, test_shots.get_shot_parameters(1).second.first, kEpsilon);
	WALL_TEST.ASSERT_EQUALS("shot bouncing off corner of two walls touching corners - bounces_remaining",
		kShotBounces - 2, test_shots.get_shot_parameters(1).second.second);
}