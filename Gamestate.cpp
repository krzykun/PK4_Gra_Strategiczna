#include <sstream>
#include <fstream>

#include "Gamestate.h"
#include "Graphic_Object.h"

/*
Gamestate();
Gamestate(std::istream&);
~Gamestate();

void save_Gamestate(std::ostream&);
std::string draw(int pos_x, int pos_y);
void order_unit(int pos_x, int pos_y, std::string order_type);
void action_check();
*/

Gamestate::Gamestate(int size_x, int size_y, Graphic_Object* null_object) : terrain(size_x, size_y, null_object), ingame(size_x, size_y, null_object), null_game_object(null_object)
{
}

Gamestate::Gamestate(std::ifstream & load_from) : terrain(load_from), ingame(load_from)
{
}

Gamestate::~Gamestate()
{
}

void Gamestate::tmp_set_filler(char znak_fillera)
{
	this->filler = new Graphic_Object(znak_fillera);
	return;
}

void Gamestate::save_Gamestate(std::ofstream & save_here)
{
	terrain.save_Map(save_here);
	ingame.save_Map(save_here);
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