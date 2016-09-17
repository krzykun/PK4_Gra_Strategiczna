#pragma once

#include <fstream>

class Graphic_Object
{
	char symbol;
public:
	Graphic_Object(char _symbol) : symbol(_symbol){}
	Graphic_Object(std::ifstream &);
	virtual ~Graphic_Object();
	char draw() { return symbol; }
	virtual void save_object(std::ofstream &);
	virtual std::string print_me();
};

