#pragma once
/*
code from https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/. Used to detect whether two line segments intersect; used to bounce shots off walls
*/
#include <algorithm>
#include "ofMain.h"
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
bool onSegment(Point p, Point q, Point r);

/*
returns the orientation of triangle pqr defined as whether tracing the triangle in such a manner is CW or CCW motion.
*/
int orientation(Point p, Point q, Point r);

/*
detect whether line segments p1q1 and p2q2 intersect.
*/
bool doIntersect(Point p1, Point q1, Point p2, Point q2);

/*
detect whether the line segment p1p2 and circle centered at point circ with a specified radius intersect.
*/
bool line_segment_circle(Point p1, Point p2, Point circ, double radius);

/*
find distance of (pointX, pointY) to line segment((x1, y1), (x2, y2)).
*/
double FindDistanceToSegment(double x1, double y1, double x2, double y2, double pointX, double pointY);

/*
find whether two rectangles with corner points (l1, r1) and (l2, r2) intersect.
by convention "l" is the upper lefthand corner, r is the lower righthand corner.
*/
bool rectOverlap(Point l1, Point r1, Point l2, Point r2);