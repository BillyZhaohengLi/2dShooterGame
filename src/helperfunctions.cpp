#include "helperfunctions.h"
Point::Point(double xval, double yval) {
	x = xval;
	y = yval;
}

bool onSegment(Point p, Point q, Point r)
{
	if (q.x <= std::max(p.x, r.x) && q.x >=  std::min(p.x, r.x) &&
		q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
		return true;

	return false;
}

int orientation(Point p, Point q, Point r)
{
	// See https://www.geeksforgeeks.org/orientation-3-ordered-points/
	// for details of below formula.
	double val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;  // colinear

	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

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

bool line_segment_circle(Point p1, Point p2, Point circ, double radius) {
	double dist = FindDistanceToSegment(p1.x, p1.y, p2.x, p2.y, circ.x, circ.y);
	return dist < radius;
}

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
