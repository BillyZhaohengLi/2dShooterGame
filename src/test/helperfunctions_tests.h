#pragma once
#include "ofMain.h"
#include "../src/const.h"
#include "../src/helpers/helperfunctions.h"
#include "UNIT_TEST.h"

inline void HELPERFUNCTIONS_TESTS() {
	UNIT_TEST HF_TEST = UNIT_TEST("helperfunction class tests");

	//point on segment test
	HF_TEST.ASSERT_EQUALS("point on segment yes", true,
		point_on_segment(Point(100, 100), Point(150, 100), Point(200, 100)));
	HF_TEST.ASSERT_EQUALS("point on segment no", false,
		point_on_segment(Point(100, 100), Point(150, 101), Point(200, 100)));
	HF_TEST.ASSERT_EQUALS("point on segment extension", false,
		point_on_segment(Point(100, 100), Point(250, 100), Point(200, 100)));

	//orientation test
	HF_TEST.ASSERT_EQUALS("orientation CW", 2,
		orientation(Point(100, 100), Point(150, 50), Point(200, 100)));
	HF_TEST.ASSERT_EQUALS("orientation CCW", 1,
		orientation(Point(100, 100), Point(200, 100), Point(150, 50)));

	//line segment intersection tests
	HF_TEST.ASSERT_EQUALS("line segment intersection tests - true", true,
		segments_intersect(Point(100, 100), Point(200, 100), Point(150, 50), Point(150, 150)));
	HF_TEST.ASSERT_EQUALS("line segment intersection tests - false", false,
		segments_intersect(Point(100, 100), Point(200, 100), Point(150, 50), Point(150, 60)));
	HF_TEST.ASSERT_EQUALS("line segment intersection tests - on extension", false,
		segments_intersect(Point(100, 100), Point(200, 100), Point(210, 50), Point(210, 150)));
	HF_TEST.ASSERT_EQUALS("line segment intersection tests - same line", true,
		segments_intersect(Point(100, 100), Point(200, 100), Point(100, 100), Point(200, 100)));
	HF_TEST.ASSERT_EQUALS("line segment intersection tests - share endpoints", true,
		segments_intersect(Point(100, 100), Point(200, 100), Point(200, 100), Point(300, 200)));

	//test line segment to circle
	HF_TEST.ASSERT_EQUALS("line segment to circle touching 1", true,
		circle_distance_to_segment(Point(100, 100), Point(200, 100), Point(150, 70), 50));
	HF_TEST.ASSERT_EQUALS("line segment to circle touching 2", true,
		circle_distance_to_segment(Point(100, 100), Point(200, 100), Point(210, 70), 50));
	HF_TEST.ASSERT_EQUALS("line segment to circle not touching", false,
		circle_distance_to_segment(Point(100, 100), Point(200, 100), Point(100, 0), 50));

	//test distance to segment
	HF_TEST.ASSERT_EQUALS("distance to segment perpendicular", 50.0,
		distance_to_segment(100, 100, 200, 100, 150, 50), kEpsilon);
	HF_TEST.ASSERT_EQUALS("distance to segment on extension", 50.0 * sqrt(2),
		distance_to_segment(100, 100, 200, 100, 250, 50), kEpsilon);
	HF_TEST.ASSERT_EQUALS("distance to segment on segment", 0.0,
		distance_to_segment(100, 100, 200, 100, 150, 100), kEpsilon);

	//test rect overlap
	HF_TEST.ASSERT_EQUALS("rect overlap, touching sides", false, rect_overlap(
		Point(100, 100), Point(200, 200), Point(100, 200), Point(200, 300)));
	HF_TEST.ASSERT_EQUALS("rect overlap, touching", true, rect_overlap(
		Point(100, 100), Point(200, 200), Point(100, 190), Point(200, 300)));
	HF_TEST.ASSERT_EQUALS("rect overlap, touching corners", false, rect_overlap(
		Point(100, 100), Point(200, 200), Point(200, 200), Point(300, 300)));
	HF_TEST.ASSERT_EQUALS("rect overlap, not touching", false, rect_overlap(
		Point(100, 100), Point(200, 200), Point(300, 300), Point(400, 400)));

	//test wall button to wall amount
	HF_TEST.ASSERT_EQUALS("wall button to wall amount", kALotWallsAmount,
		wall_button_to_wall_amount(kALotWallsButton));
	HF_TEST.ASSERT_EQUALS("wall button to wall amount invalid", 0,
		wall_button_to_wall_amount(999));

	//test serialize input
	bool keydown[255];
	keydown[kUp] = true;
	keydown[kLeft] = true;
	keydown[kDown] = false;
	keydown[kRight] = false;
	string test_string = serialize_input(keydown, true, 100, 100);
	HF_TEST.ASSERT_EQUALS("serialize input",
		std::string(std::string(kTrueBoolean) + std::string(kSmallDelimiter)) +
		std::string(std::string(kTrueBoolean) + std::string(kSmallDelimiter)) +
		std::string(std::string(kFalseBoolean) + std::string(kSmallDelimiter)) +
		std::string(std::string(kFalseBoolean) + std::string(kSmallDelimiter)) +
		std::string(std::string(kTrueBoolean) + std::string(kSmallDelimiter)) +
		"100.000000" + std::string(kSmallDelimiter) + "100.000000", test_string);

	//test deserialize input
	InputParams output = deserialize_input(test_string);
	HF_TEST.ASSERT_EQUALS("deserialize input - keys", true, (bool)output.first.first[0]);
	HF_TEST.ASSERT_EQUALS("deserialize input - mousedown", true, output.first.second);
	HF_TEST.ASSERT_EQUALS("deserialize input - position x", 100.0, output.second.first, kEpsilon);
	HF_TEST.ASSERT_EQUALS("deserialize input - position y", 100.0, output.second.second, kEpsilon);

	//test split
	test_string = "aaa~bbb~ccc~";
	vector<string> test_vector = split(test_string, "~");
	HF_TEST.ASSERT_EQUALS("split vector size", std::size_t(3), test_vector.size());
	HF_TEST.ASSERT_EQUALS("split vector contents", std::string("aaa"), test_vector[0]);	
}