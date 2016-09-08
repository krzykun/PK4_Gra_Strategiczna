#include "Gamestate.h"
#include "Graphic_Object.h"
#include <sstream>


/*
Gamestate();
Gamestate(std::istream&);
~Gamestate();

void save_Gamestate(std::ostream&);
std::string draw(int pos_x, int pos_y);
void order_unit(int pos_x, int pos_y, std::string order_type);
void action_check();
*/

Gamestate::Gamestate(int size_x, int size_y, Graphic_Object* null_object) : terrain(size_x, size_y, filler), ingame(size_x, size_y, filler), filler(null_object)
{
}


Gamestate::~Gamestate()
{
	//this->terrain.~Map();
	//this->ingame.~Map();
}

void Gamestate::tmp_set_filler(char znak_fillera)
{
	this->filler = new Graphic_Object(znak_fillera);
	return;
}

std::string Gamestate::draw()
{
	std::string terrain_tmp = terrain.draw();
	std::string ingame_tmp = ingame.draw();
	for (int i = 0; i < 100; i++)
	{
		if (ingame_tmp[i])
		{
			terrain_tmp[i] = ingame_tmp[i];
		}
	}
	std::string screenstring = "";
	screenstring += terrain_tmp;
	return screenstring;
}