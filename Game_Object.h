#pragma once
#include <string>
#include <vector>

#include "local_types_definitions.h"
#include "Graphic_Object.h"
class Game_Object :
	public Graphic_Object
{
	//these variables are modified by Game_Object
	int owner;	//player that can control this object
	int pos_x, pos_y;	//position of object
	//std::vector<int> buffs; FUTURE TODO
	std::string object_name;
	std::string description;
	game_obj_state state; //protected ?
protected:
	//these variables are modified by objects that inherit Game_Object
	int health;	// usuallly different than 0
	int energy;	//might be 0
	void set_description(std::string);
	void set_name(std::string);

public:
	Game_Object(int, int, int, char);
	Game_Object(int, int, std::ifstream &);
	virtual ~Game_Object();

	//funtions to manipulate the object with
	void modify_health(int modifier) { health += modifier; }
	void modify_energy(int modifier) { energy += modifier; }
	int get_x(){ return pos_x; }
	void set_x(int x) { pos_x = x; }
	int get_y(){ return pos_y; }
	void set_y(int y) { pos_y = y; }
	void save_object(std::ofstream &);
	std::string print_me();
	game_obj_state get_state(){ return state; }
	void set_state(game_obj_state _s){ state = _s; }
};

