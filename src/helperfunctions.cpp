#include "helperfunctions.h"
/*
constructor; construct a new point (x,y).
*/
Point::Point(double xval, double yval) {
	x = xval;
	y = yval;
}

/*
check whether point r is on line segment pq.
*/
//code from https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/.
bool onSegment(Point p, Point q, Point r)
{
	if (q.x <= std::max(p.x, r.x) && q.x >=  std::min(p.x, r.x) &&
		q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
		return true;

	return false;
}

/*
returns the orientation of triangle pqr defined as whether tracing the triangle in such a manner is CW or CCW motion.
*/
//code from https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/.
int orientation(Point p, Point q, Point r)
{
	// See https://www.geeksforgeeks.org/orientation-3-ordered-points/
	// for details of below formula.
	double val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;  // colinear

	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

/*
detect whether line segments p1q1 and p2q2 intersect.
*/
//code from https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/.
bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
	// Find the four orientations needed for general and
	// special cases
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// p1, q1 and p2 are colinear and p2 lies on segment p1q1
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and q2 are colinear and q2 lies on segment p1q1
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are colinear and p1 lies on segment p2q2
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are colinear and q1 lies on segment p2q2
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases
}

/*
detect whether the line segment p1p2 and circle centered at point circ with a specified radius intersect.
*/
bool line_segment_circle(Point p1, Point p2, Point circ, double radius) {
	double dist = FindDistanceToSegment(p1.x, p1.y, p2.x, p2.y, circ.x, circ.y);
	return dist < radius;
}

/*
find distance of (pointX, pointY) to line segment((x1, y1), (x2, y2)).
*/
//from http://www.cprogramto.com/c-program-to-find-shortest-distance-between-point-and-line-segment/.
double FindDistanceToSegment(double x1, double y1, double x2, double y2, double pointX, double pointY)
{
	double diffX = x2 - x1;
	float diffY = y2 - y1;
	if ((diffX == 0) && (diffY == 0))
	{
		diffX = pointX - x1;
		diffY = pointY - y1;
		return sqrt(diffX * diffX + diffY * diffY);
	}

	float t = ((pointX - x1) * diffX + (pointY - y1) * diffY) / (diffX * diffX + diffY * diffY);

	if (t < 0)
	{
		//point is nearest to the first point i.e x1 and y1
		diffX = pointX - x1;
		diffY = pointY - y1;
	}
	else if (t > 1)
	{
		//point is nearest to the end point i.e x2 and y2
		diffX = pointX - x2;
		diffY = pointY - y2;
	}
	else
	{
		//if perpendicular line intersect the line segment.
		diffX = pointX - (x1 + t * diffX);
		diffY = pointY - (y1 + t * diffY);
	}

	//returning shortest distance
	return sqrt(diffX * diffX + diffY * diffY);
}

//from https://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other.
/*
find whether two rectangles with corner points (l1, r1) and (l2, r2) intersect.
by convention "l" is the upper lefthand corner, r is the lower righthand corner.
*/
bool rectOverlap(Point l1, Point r1, Point l2, Point r2)
{
	// If one rectangle is on left side of other
	if (l1.x >= r2.x || l2.x >= r1.x)
		return false;

	// If one rectangle is above other
	if (l1.y >= r2.y || l2.y >= r1.y)
		return false;

	return true;
}

/*
helper function for entering name called in update. Takes in the keys pressed, whether the name was altered in the previous frame and the player's name
and returns whether the name was altered and the new name.
*/
pair<bool, string> enter_name(bool entered, string player_name, bool keydown[255]) {
	//enter name
	bool something_pressed = false;
	for (int i = character_start; i < character_end; i++) {
		if (keydown[i]) {
			something_pressed = true;
			//only one letter can be entered per update; also disables entering when the name goes over the maximum name length.
			if (player_name.length() < max_name_length && !entered) {
				player_name += i;
			}
		}
	}
	//8 is the backspace button; if it is pressed pop the last letter the player entered.
	if (keydown[backspace_ascii]) {
		something_pressed = true;
		if (player_name.length() > 0 && !entered) {
			player_name.pop_back();
		}
	}
	//boolean variable to prevent multiple letters entered with one key press due to how fast update is called
	if (something_pressed) {
		entered = true;
	}
	else {
		entered = false;
	}
	return pair<bool, string>(entered, player_name);
}

/*
helper function for entering ip address called in update. Takes in the keys pressed, whether the ip address was altered in the previous frame and the player's name
and returns whether the name was altered and the new ip address.
*/
pair<bool, string> enter_ip(bool entered, string ip_address, bool keydown[255]) {
	//enter name
	bool something_pressed = false;
	if (keydown[period_ascii]) {
		something_pressed = true;
		//only one letter can be entered per update; also disables entering when the name goes over the maximum name length.
		if (ip_address.length() < max_ip_length && !entered) {
			ip_address += '.';
		}
	}
	for (int i = integer_start; i <= integer_end; i++) {
		if (keydown[i]) {
			something_pressed = true;
			//only one letter can be entered per update; also disables entering when the name goes over the maximum name length.
			if (ip_address.length() < max_ip_length && !entered) {
				ip_address += i;
			}
		}
	}
	//8 is the backspace button; if it is pressed pop the last letter the player entered.
	if (keydown[backspace_ascii]) {
		something_pressed = true;
		if (ip_address.length() > 0 && !entered) {
			ip_address.pop_back();
		}
	}
	//boolean variable to prevent multiple letters entered with one key press due to how fast update is called
	if (something_pressed) {
		entered = true;
	}
	else {
		entered = false;
	}
	return pair<bool, string>(entered, ip_address);
}

/*
helper function to convert the wall setting pressed to the actual amount of walls.
*/
int wall_button_to_wall_amount(int wall_button) {
	switch (wall_button) {
	case (few_walls):
		return few_walls_amount;
		break;
	case (medium_walls):
		return medium_walls_amount;
		break;
	case (a_lot_walls):
		return a_lot_walls_amount;
		break;
	}
}

/*
splits a string into an array by a delimiter. taken from https://stackoverflow.com/questions/9435385/split-a-string-using-c11.
*/
std::vector<std::string> split(const string& input, const string& regex) {
	// passing -1 as the submatch index parameter performs splitting
	std::regex re(regex);
	std::sregex_token_iterator
		first{ input.begin(), input.end(), re, -1 },
		last;
	return { first, last };
}

/*
serialize player input consisting of keys pressed, whether the mouse button is held and the mouse position into a string to send through a connection.
*/
string serialize_input(bool keydown[255], bool mouse_down, double mouse_x, double mouse_y) {
	string to_send;
	if (keydown['W']) {
		to_send += "T";
	}
	else {
		to_send += "F";
	}
	to_send += "~";
	if (keydown['A']) {
		to_send += "T";
	}
	else {
		to_send += "F";
	}
	to_send += "~";
	if (keydown['S']) {
		to_send += "T";
	}
	else {
		to_send += "F";
	}
	to_send += "~";
	if (keydown['D']) {
		to_send += "T";
	}
	else {
		to_send += "F";
	}
	to_send += "~";
	if (mouse_down) {
		to_send += "T";
	}
	else {
		to_send += "F";
	}
	to_send += "~";
	to_send += to_string(mouse_x);
	to_send += "~";
	to_send += to_string(mouse_y);
	return to_send;
}

/*
deserialize a player input string consisting of keys pressed, whether the mouse button is held and the mouse position received through a connection.
returns an ugly data structure, with the contents being the following in this order:
1. boolean vector of keys pressed
2. boolean of whether the mouse is pressed
3. the mouse's x position
4. the mouse's y position
*/
pair<pair<vector<bool>, bool>, pair<double, double>> deserialize_input(string message) {
	vector<string> message_array = split(message, "~");
	vector<bool> key_down;
	for (int i = 0; i < 4; i++) {
		if (message_array[i] == "T") {
			key_down.push_back(true);
		}
		else {
			key_down.push_back(false);
		}
	}
	bool mouse_down;
	if (message_array[4] == "T") {
		mouse_down = true;
	}
	else {
		mouse_down = false;
	}
	double mouse_x = stoi(message_array[5]);
	double mouse_y = stoi(message_array[6]);
	return pair<pair<vector<bool>, bool>, pair<double, double>>(pair<vector<bool>, bool> (key_down, mouse_down), pair<double, double>(mouse_x, mouse_y));
}