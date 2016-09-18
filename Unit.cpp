#include "Unit.h"


Unit::Unit(int owner, int pos_x, int pos_y, char symbol) : Game_Object(owner, pos_x, pos_y, symbol), weapon(0, 0)
{
	dest_x = 0;
	dest_y = 0;
}

Unit::Unit(int pos_x, int pos_y, std::ifstream & load_from) : Game_Object(pos_x, pos_y, load_from), weapon(0,0)
{
	load_from >> dest_x >> dest_y;
	set_target(this);
}

Unit::~Unit()
{
}

void Unit::move_unit(int, int) {}

void Unit::attack_unit(int, int) {}

void Unit::save_unit(std::ofstream & save_here)
{
	save_object(save_here);
	save_here << dest_x << dest_y;
}

int Unit::try_to_attack()
{
	if ((abs(target->get_x() - get_x()) < get_range()) && (abs(target->get_y() - get_y()) < get_range()))
	{	//two huge conditions, target needs to be at a distane of at most <range> in x AND y
		int tmp_dmg = (-1) * get_damage();	//multiply by -1 to subtract damage
		target->modify_health(tmp_dmg);
		return 0;	//success
	}
	else return 1;	//failure
}

int Unit::get_damage() { return 0; }

int Unit::get_unit_speed() { return 0; }