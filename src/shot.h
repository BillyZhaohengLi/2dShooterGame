#pragma once
#include "ofMain.h"
#include "const.h"
#include <math.h>
class ShotInLevel {
private:
	
public:
	struct Shot {
		double posx;
		double posy;
		double angle;
		int bounces_remaining;
		Shot(double x, double y, double initial_angle);
		void move();
		void draw_shot();
	};
	vector<Shot> shots_in_level;
	ShotInLevel() { vector<Shot> shots_in_level; };
	void add_shot(double angle, double posx, double posy);
	void move();
	void draw_shot();
};