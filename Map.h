#pragma once
#include <iostream>
#include <string>
#include "Graphic_Object.h"

class Map
{
	int mapsize_x, mapsize_y;
	std::string previous_map;
	Graphic_Object*** gamefield;
	Graphic_Object* null_elem;
public:
	Map(int, int, Graphic_Object*);
	Map(std::istream&);
	~Map();

	void save_Map(std::ostream&);
	void add_object(Graphic_Object&, int, int);
	std::string & draw();

};

