#pragma once
#include <iostream>
#include <string>
#include <fstream>

#include "Graphic_Object.h"

class Map
{
	int mapsize_x, mapsize_y;
	std::string previous_map;
	Graphic_Object*** gamefield;
	Graphic_Object* null_elem;
public:
	Map(int, int, Graphic_Object*);
	Map(std::ifstream &, int);	//int is the choice between terrain 0 or unit layer 1
	~Map();

	void save_Map(std::ofstream &);

	void add_object(Graphic_Object&, int, int);
	void implement_turn();
	void unit_wants_to_move(int, int, int, int);
	void unit_wants_to_attack(int, int, int, int);

	std::string & draw();
	std::string show_selection(int, int);

};

