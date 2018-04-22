#pragma once
#include "const.h"
#include <vector>

class AllButtons {
private:
	struct Button {
		int posx;
		int posy;
		int xspan;
		int yspan;
		int text;
	};
	std::vector<Button> buttons;
public:
	AllButtons() { std::vector<Button> buttons(); };
};