#pragma once
#include <iostream>
#include <string>

#include "Map.h"

class Gamestate
{
	Map terrain;
	Map ingame;
	Graphic_Object* filler;
public:
	Gamestate(int, int, Graphic_Object*);
	Gamestate(std::istream&);
	~Gamestate();

	void tmp_set_filler(char znak_fillera = 'X');
	void save_Gamestate(std::ostream&);
	std::string draw();
	void order_unit(int pos_x, int pos_y, std::string order_type);
	void action_check();
};

