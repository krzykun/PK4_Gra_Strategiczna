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
	std::vector<int> buffs; //TODO
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
	Game_Object(std::ifstream &);
	virtual ~Game_Object();

	//funtions to manipulate the object with
	int modify_health(int modifier) { health += modifier; }
	int modify_energy(int modifier) { return energy += modifier; }
	void save_object(std::ofstream &);
	std::string print_me();
	game_obj_state get_state(){ return state; }
};

