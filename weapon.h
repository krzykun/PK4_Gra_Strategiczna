#pragma once
class weapon
{
	int damage;
	int range;
public:
	weapon(int, int);
	~weapon();
	int get_damage() { return damage; }
	int get_range() { return range; }
};

