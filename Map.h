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
	Map(std::ifstream &);
	~Map();

	void save_Map(std::ofstream &);
	void add_object(Graphic_Object&, int, int);
	std::string & draw();

};

