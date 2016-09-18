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
	null_elem = filler;
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
					Unit* pUnit = (reinterpret_cast<Unit*>(gamefield[i][j]));
					pUnit->set_target(pUnit);
					break;
				}
				default:
				{
					gamefield[i][j] = null_elem;
					break;
				}
				}

			}
			//FUTURE TODO: bc element can be larger than 1 square, we check if it is repeated above or
			//just before our field. if it is, we tie it to that. if its not, we create a new one
			//FUTURE TODO: a list of symbols that need to be checked
		}
	}
}

Map::~Map()
{
	delete[] gamefield;
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
			//THROW control block?? not needed
			if (typeid(Unit) == typeid(gamefield[i][j]))
			{
				Unit* pUnit = reinterpret_cast<Unit*> (gamefield[i][j]);
				Game_Object* target = pUnit->get_target();
				if ((pUnit->get_x() == pUnit->get_target_x()) && (pUnit->get_y() == pUnit->get_target_y()))
					pUnit->set_state(idle);

				game_obj_state tmp_state = pUnit->get_state();
				if ( tmp_state == move)
				{
					unit_wants_to_move(pUnit);
				}
				else if ( tmp_state == attack )
				{
					int tmp_x = target->get_x();
					int tmp_y = target->get_y();
					Game_Object* pG_Obj = reinterpret_cast <Game_Object*> (gamefield[tmp_x][tmp_y]);
					unit_wants_to_attack(pUnit, pG_Obj);
				}
			}
		}
	}
}

void Map::unit_wants_to_move(Unit* move_me)
{
	bool direction[2];	// tells us if the unit wants to move forward or backward
	int curr_x = move_me->get_x();
	int dest_x = move_me->get_target_x();
	int curr_y = move_me->get_y();
	int dest_y = move_me->get_target_y();
	int unit_speed = move_me->get_unit_speed();

	direction[0] = ((dest_x - curr_x) > 0);	//1 forward 0 backward
	direction[1] = ((dest_y - curr_y) > 0);

	int new_x, new_y;
	if (direction[0]) new_x = curr_x + unit_speed; else new_x = curr_x - unit_speed;
	if (direction[1]) new_y = curr_y + unit_speed; else new_y = curr_y - unit_speed;

	if (gamefield[new_x][new_y] != null_elem)
	{	//if the field is taken (null element not occuping it), dont move
		return;
	}
	//everything fine, time to swap the object with null_elem
	gamefield[new_x][new_y] = reinterpret_cast<Graphic_Object*> (move_me);
	gamefield[curr_x][curr_y] = null_elem;
	move_me->set_dxdy(new_x, new_y);
}


void Map::unit_wants_to_attack(Unit* src_unit, Game_Object* dest_obj)
{
	if ( src_unit->try_to_attack() )
	{	//value of 1 means that the target was out of range
		src_unit->set_dxdy(dest_obj->get_x(), dest_obj->get_y());	//get the coordinates of target
		unit_wants_to_move(src_unit);	//try to move closer to target current destination
	}
}

std::string & Map::draw()
{
	previous_map = "";	//clearing previous visible screen
	for (int i = 0; i < mapsize_x; i++)
	{
		for (int j = 0; j < mapsize_y; j++)
			if (gamefield[i][j] != null_elem)
			previous_map += gamefield[i][j]->draw();
	}
	return previous_map;
}

std::string Map::show_selection(int pos_x, int pos_y)
{
	std::string tmp(" Nothing to show. ");
	if (gamefield[pos_x][pos_y] == null_elem)
		return tmp;
	else
		return gamefield[pos_x][pos_y]->print_me();
}