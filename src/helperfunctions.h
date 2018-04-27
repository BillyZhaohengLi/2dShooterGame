#pragma once
#include <algorithm>
#include <regex>
#include "ofMain.h"
#include "const.h"
/*
struct used to calculate intersections.
*/
struct Point
{
	/*
	x coordinate.
	*/
	double x;

	/*
	y coordinate.
	*/
	double y;

	/*
	constructor; construct a new point (x,y).
	*/
	Point(double xval, double yval);
};

/*
check whether point r is on line segment pq.
*/
//code from https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/.
bool onSegment(Point p, Point q, Point r);

/*
returns the orientation of triangle pqr defined as whether tracing the triangle in such a manner is CW or CCW motion.
*/
//code from https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/.
int orientation(Point p, Point q, Point r);

/*
detect whether line segments p1q1 and p2q2 intersect.
*/
//code from https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/.
bool doIntersect(Point p1, Point q1, Point p2, Point q2);

/*
detect whether the line segment p1p2 and circle centered at point circ with a specified radius intersect.
*/
bool line_segment_circle(Point p1, Point p2, Point circ, double radius);

/*
find distance of (pointX, pointY) to line segment((x1, y1), (x2, y2)).
*/
//from http://www.cprogramto.com/c-program-to-find-shortest-distance-between-point-and-line-segment/.
double FindDistanceToSegment(double x1, double y1, double x2, double y2, double pointX, double pointY);

/*
find whether two rectangles with corner points (l1, r1) and (l2, r2) intersect.
by convention "l" is the upper lefthand corner, r is the lower righthand corner.
*/
bool rectOverlap(Point l1, Point r1, Point l2, Point r2);

/*
helper function for entering name called in update. Takes in the keys pressed, whether the name was altered in the previous frame and the player's name
and returns whether the name was altered and the new name.
*/
pair<bool, string> enter_name(bool entered, string player_name, bool keydown[255]);

/*
helper function for entering ip address called in update. Takes in the keys pressed, whether the ip address was altered in the previous frame and the player's name
and returns whether the name was altered and the new ip address.
*/
pair<bool, string> enter_ip(bool entered, string ip_address, bool keydown[255]);

/*
helper function to convert the wall setting pressed to the actual amount of walls.
*/
int wall_button_to_wall_amount(int wall_button);

/*
splits a string into an array by a delimiter. taken from https://stackoverflow.com/questions/9435385/split-a-string-using-c11.
*/
std::vector<std::string> split(const string& input, const string& regex);

/*
serialize player input consisting of keys pressed, whether the mouse button is held and the mouse position into a string to send through a connection.
*/
string serialize_input(bool keydown[255], bool mouse_down, double mouse_x, double mouse_y);

/*
deserialize a player input string consisting of keys pressed, whether the mouse button is held and the mouse position received through a connection.
returns an ugly data structure, with the contents being the following in this order:
1. boolean vector of keys pressed
2. boolean of whether the mouse is pressed
3. the mouse's x position
4. the mouse's y position
*/
pair<pair<vector<bool>, bool>, pair<double, double>> deserialize_input(string message);