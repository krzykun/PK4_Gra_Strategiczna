#include <fstream>

#include "Graphic_Object.h"

Graphic_Object::Graphic_Object(std::ifstream & load_from)
{
	load_from >> symbol;
}

Graphic_Object::~Graphic_Object()
{
}

