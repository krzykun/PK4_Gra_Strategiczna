#pragma once
#include "Game_Object.h"
#include "armor_wood.h"
class Game_Obj_Tree :
	public Game_Object, public armor_wood
{
protected:
	static int production_time;
public:
	Game_Obj_Tree(int, int, int);
	Game_Obj_Tree(int, int, std::ifstream &);
	~Game_Obj_Tree();

	void save_object(std::ofstream &);
};

