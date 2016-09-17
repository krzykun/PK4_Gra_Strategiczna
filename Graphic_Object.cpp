#include <fstream>

#include "Graphic_Object.h"

Graphic_Object::Graphic_Object(std::ifstream & load_from)
{
	load_from >> symbol;
}

Graphic_Object::~Graphic_Object()
{
}

void Graphic_Object::save_object(std::ofstream & save_here)
{
	save_here << symbol << ' ';
}

std::string Graphic_Object::print_me(){ std::string empty; return empty; }