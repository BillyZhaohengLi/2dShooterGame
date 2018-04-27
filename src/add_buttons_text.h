#pragma once
#include "const.h"
#include "button.h"
#include "gametext.h"
//helper class only used to add buttons and text into a level; due to the sheer amount of buttons and text it was separated from main and placed here.
void add_buttons_text(AllButtons& buttons_in_level, AllText& text_in_level);