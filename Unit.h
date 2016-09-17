#pragma once
#include "Game_Object.h"
class Unit :
	public Game_Object	//here go the weapoin and armor classes that this guy wants to have
{
protected:
	int dest_x, dest_y;
public:
	Unit(int, int, int, char);
	virtual ~Unit();

	//functions to use
	void change_position(int, int);
	int get_target_x(){ return dest_x; }
	int get_target_y(){ return dest_y; }
	virtual void move_unit(int, int);	//virtual, some units cant move
	virtual void attack_unit(int, int);	//virtual, different attacks
};

