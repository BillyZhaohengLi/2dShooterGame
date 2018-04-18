#pragma once
#include "const.h"
#include "ofMain.h"
#include <vector>
#include <math.h>
class Player {
private:
	double xpos;
	double ypos;
	int red;
	int green;
	int blue;
	bool alive;
	direction facing;
	int shot_cooldown;
public:
	Player(double x, double y, int r, int g, int b);
	pair<int, int> get_location();
	void collision_resolve(int x, int y);
	void move();
	void change_direction(direction change_to);
	bool isalive();
	void draw_player();
	double fire_shot();
	bool can_shoot();
	void cooldown_reduce();
};