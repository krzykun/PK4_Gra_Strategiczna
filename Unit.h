#pragma once
#include <fstream>

#include "Game_Object.h"
#include "weapon.h"

class Unit :
	public Game_Object, public weapon	//here go the weapoin and armor classes that this guy wants to have
{
protected:
	int dest_x, dest_y;
	Game_Object* target;
public:
	Unit(int, int, int, char);
	Unit(std::ifstream &);
	virtual ~Unit();

	//functions to use
	void change_position(int, int);
	int get_target_x(){ return dest_x; }
	int get_target_y(){ return dest_y; }
	void set_dxdy(int new_dx, int new_dy){ dest_x = new_dx; dest_y = new_dy; }
	virtual void move_unit(int, int);	//virtual, some units cant move
	virtual void attack_unit(int, int);	//virtual, different attacks
	void save_unit(std::ofstream &);
	int try_to_attack();
	virtual int get_damage();
	virtual int get_unit_speed();
	Game_Object* get_target() { return target; }
	void set_target(Game_Object* _g) { target = _g; }
};

