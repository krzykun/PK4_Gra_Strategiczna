#pragma once
#include <iostream>
#include <string>
#include <fstream>

#include "Map.h"

class Gamestate
{
	Map terrain;
	Map ingame;
	Graphic_Object* filler; //temporary variable to have something in the map
	const Graphic_Object* null_game_object;
public:
	Gamestate(int, int, Graphic_Object*);
	Gamestate(std::ifstream &);
	~Gamestate();

	void tmp_set_filler(char znak_fillera = 'X');
	void save_Gamestate(std::ofstream &);
	std::string draw();
	void order_unit(int pos_x, int pos_y, std::string order_type);
	void action_check();
};

