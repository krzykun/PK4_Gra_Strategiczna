#include <string>

#include "Map.h"
#include "Graphic_Object.h"

Map::Map(int size_x, int size_y, Graphic_Object* filler)
{
	mapsize_x = size_x;
	mapsize_y = size_y;
	gamefield = new Graphic_Object**[mapsize_x];
	for (int i = 0; i < mapsize_x; i++)
	{
		gamefield[i] = new Graphic_Object*[mapsize_y];
		for (int j = 0; j < mapsize_y; j++)
			gamefield[i][j] = filler;
	}
}

Map::Map(std::ifstream & load_from)
{
	load_from >> mapsize_x >> mapsize_y;
	gamefield = new Graphic_Object**[mapsize_x];
	for (int i = 0; i < mapsize_x; i++)
	{
		gamefield[i] = new Graphic_Object*[mapsize_y];
		for (int j = 0; j < mapsize_y; j++)
			gamefield[i][j] = new Graphic_Object(load_from);
	}
}

Map::~Map()
{
}

void Map::save_Map(std::ofstream & save_here)
{
	save_here << mapsize_x << ' ' << mapsize_y << ' ';
	for (int i = 0; i < mapsize_x; i++)
	{
		for (int j = 0; j < mapsize_y; j++)
		{
			save_here << gamefield[i][j]->draw() << ' ';
		}
		save_here << "\n";
	}
}

std::string & Map::draw()
{
	previous_map = "";	//clearing previous visible screen
	for (int i = 0; i < mapsize_x; i++)
	{
		for (int j = 0; j < mapsize_y; j++)
			previous_map += gamefield[i][j]->draw();
	}
	return previous_map;
}