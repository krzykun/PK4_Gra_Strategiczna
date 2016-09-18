#include "Game_Object.h"


Game_Object::Game_Object(int _owner, int _pos_x, int _pos_y, char _symbol) : Graphic_Object(_symbol)
{
	owner = _owner;
	pos_x = _pos_x;
	pos_y = _pos_y;
	state = idle;
	description = "This object is not meant to exist in this form.";
}

Game_Object::Game_Object(std::ifstream & load_from) : Graphic_Object(load_from)
{
	load_from >> owner;
	load_from >> health;
	load_from >> energy;
	state = idle;
}

Game_Object::~Game_Object()
{
}

void Game_Object::set_description(std::string new_desc)
{
	description = new_desc;
}

void Game_Object::set_name(std::string new_name)
{
	object_name = new_name;
}

void Game_Object::save_object(std::ofstream & save_here)
{
	save_here << Graphic_Object::draw();
	save_here << owner << ' ' << health << ' ' << energy << ' '; //add state
}

std::string Game_Object::print_me()
{
	std::stringstream tmp_str;
	tmp_str << ' ' << object_name << ' ' << state << ' ' << health << ' ' << description << ' ';
	return tmp_str.str();
}