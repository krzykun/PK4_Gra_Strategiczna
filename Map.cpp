#include <string>

#include "Map.h"
#include "Graphic_Object.h"
#include "Game_Object.h"
#include "Game_Obj_Tree.h"
#include "Unit_Knight.h"

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

Map::Map(std::ifstream & load_from, int map_type)
{
	if (!map_type)
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
	else
	{
		load_from >> mapsize_x >> mapsize_y;
		gamefield = new Graphic_Object**[mapsize_x];
		for (int i = 0; i < mapsize_x; i++)
		{
			gamefield[i] = new Graphic_Object*[mapsize_y];
			for (int j = 0; j < mapsize_y; j++)
			{
				char tmp_char;
				int owner;
				load_from >> tmp_char >> owner;
				switch (tmp_char)
				{
				case 'T':
				{
					gamefield[i][j] = new Game_Obj_Tree(owner,i, j);
					break;
				}
				case 'K':
				{
					gamefield[i][j] = new Unit_Knight(owner, i, j);
				}
				}

			}
				
				
				
				//gamefield[i][j] = new Game_Object(load_from);

			//TODO: a function recognizing which element needs to be created
			//bc element can be larger than 1 square, we check if it is repeated above or
			//just before our field. if it is, we tie it to that. if its not, we create a new one
			//TODO: a list of symbols that need to be checked
		}
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
			gamefield[i][j]->save_object(save_here);
		}
		save_here << "\n";
	}
}

void Map::implement_turn()
{
	for (int i = 0; i < mapsize_x; i++)
	{
		for (int j = 0; j < mapsize_y; j++)
		{
			//THROW control block, if the move/attack action does not succeed
			if (typeid(Unit) == typeid(gamefield[i][j]))
			{
				Unit* pUnit = reinterpret_cast<Unit*> (gamefield[i][j]);
				game_obj_state tmp_state = pUnit->get_state();
				if ( tmp_state == move)
				{
					unit_wants_to_move(i, j, pUnit->get_target_x(), pUnit->get_target_y() );
				}
				else if (tmp_state == attack)
				{
					unit_wants_to_attack(i, j, pUnit->get_target_x(), pUnit->get_target_y());
				}
			}
		}
	}
}

void Map::unit_wants_to_move(int, int, int, int)
{
	//todo
}


void Map::unit_wants_to_attack(int, int, int, int)
{
	//todo
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

std::string Map::show_selection(int pos_x, int pos_y)
{
	return gamefield[pos_x][pos_y]->print_me();
}