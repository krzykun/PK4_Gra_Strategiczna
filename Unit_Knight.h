#pragma once
#include "Unit.h"
#include "weapon_sword.h"
#include "armor_plating.h"
class Unit_Knight :
	public Unit, public weapon_sword, public armor_plating
{
protected:
	static int production_time;
public:
	Unit_Knight(int, int, int);
	virtual ~Unit_Knight();

	void move_unit(int, int);
	void attack_unit(int, int);
};

