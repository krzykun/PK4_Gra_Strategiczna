#include "Game_Obj_Tree.h"

int Game_Obj_Tree::production_time = 1;

Game_Obj_Tree::Game_Obj_Tree(int _owner, int _pos_x, int _pos_y) : Game_Object(_owner, _pos_x, _pos_y, 'T')
{
	health = 150;
	energy = 0;
	set_description("A beautifull tree.");
	set_state(idle);
}

Game_Obj_Tree::Game_Obj_Tree(std::ifstream & load_from) : Game_Object(load_from)
{
	
}

Game_Obj_Tree::~Game_Obj_Tree()
{
}

void Game_Obj_Tree::save_object(std::ofstream & save_here)
{
	Game_Object::save_object(save_here);
}