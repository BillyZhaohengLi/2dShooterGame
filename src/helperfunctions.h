#pragma once
/*
code from https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/. Used to detect whether two line segments intersect; used to bounce shots off walls
*/
#include <algorithm>
struct Point
{
	double x;
	double y;
	Point(double xval, double yval);
};
bool onSegment(Point p, Point q, Point r);
int orientation(Point p, Point q, Point r);
bool doIntersect(Point p1, Point q1, Point p2, Point q2);