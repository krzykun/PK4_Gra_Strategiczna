#include "Unit.h"


Unit::Unit(int owner, int pos_x, int pos_y, char symbol) : Game_Object(owner, pos_x, pos_y, symbol)
{
	dest_x = 0;
	dest_y = 0;
}


Unit::~Unit()
{
}

void Unit::move_unit(int, int) {}

void Unit::attack_unit(int, int) {}