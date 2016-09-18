#include <sstream>
#include <fstream>

#include "Gamestate.h"
#include "Match.h"
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

Graphic_Object* Gamestate::null_game_object;

Gamestate::Gamestate(int size_x, int size_y) : terrain(size_x, size_y, null_game_object), ingame(size_x, size_y, null_game_object) {}

Gamestate::Gamestate(std::ifstream & load_from) : terrain(load_from, 0, null_game_object), ingame(load_from, 1, null_game_object) {}

Gamestate::~Gamestate()
{
	delete null_game_object;
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
	for (int i = 0; i < ingame_tmp.length(); i++)
	{
		if (ingame_tmp[i] != ' ')
		{
			terrain_tmp[i] = ingame_tmp[i];
		}
	}
	std::string screenstring = "";
	screenstring += terrain_tmp;
	return screenstring;
}

void Gamestate::order_unit(int pos_x, int pos_y, user_action action, std::stringstream & command_stream)
{
	ingame.set_unit_order(pos_x, pos_y, action, command_stream);
}

void Gamestate::implement_turn()
{
	ingame.implement_turn();
}

std::string Gamestate::show_selection(int pos_x, int pos_y)
{
	return ingame.show_selection(pos_x, pos_y);
}