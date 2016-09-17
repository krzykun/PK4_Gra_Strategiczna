#include "Unit_Knight.h"

int Unit_Knight::production_time = 10;

Unit_Knight::Unit_Knight(int owner, int pos_x, int pos_y) : Unit(owner, pos_x, pos_y, 'K')
{
	health = 50;
	energy = 0;
	set_name("Knight");
	set_description("A brave shiny piece of metal.");
}


Unit_Knight::~Unit_Knight()
{
}

void Unit_Knight::move_unit(int new_x, int new_y)
{

}

void Unit_Knight::attack_unit(int new_x, int new_y)
{

}