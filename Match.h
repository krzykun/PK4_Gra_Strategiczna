#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

#include "Gamestate.h"
#include "Game_Object.h"
class Match
{
	Gamestate* gamestate;

	int turn_number;
	int number_of_active_users;
	int mapsize_x;
	int mapsize_y;
	std::vector<int*> selected;	//array of units selected by users
public:
	static Graphic_Object* null_graphic_object;	//null object used to initialize now_selected array
												// and used when a unit that is selected dies (resets the user selection)
	std::vector<std::stringstream*> player_streams;

	Match(int, int, int);
	Match(std::ifstream &);	//for loading a match
	~Match();

	void save_Match(std::ofstream &);
	void implement_turn();
	void interpret_user_command(int, user_action, std::stringstream &);
	void draw_match();

	void change_selection(int, std::stringstream &);
	

	int* return_object_selected_by(int player_number);	//change int to Game_Object in final version
	int current_turn_no(){ return turn_number; }
	void add_stats_death(Game_Object*);	//todo, suspended
};

