#pragma once
class Graphic_Object
{
	char symbol;
public:
	Graphic_Object(char _symbol) : symbol(_symbol){}
	~Graphic_Object();
	char draw() { return symbol; }
};

