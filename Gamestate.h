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
public:
	static Graphic_Object* null_game_object;
	Gamestate(int, int);
	Gamestate(std::ifstream &);
	~Gamestate();

	void tmp_set_filler(char znak_fillera = 'X');
	void save_Gamestate(std::ofstream &);
	std::string draw();

	void order_unit(int, int, user_action, std::stringstream &);
	void implement_turn();

	std::string show_selection(int, int);
};

