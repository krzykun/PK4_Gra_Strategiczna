#pragma once
#include <iostream>
#include <string>
#include <sstream>

#include "Gamestate.h"
class Match
{
	Gamestate* gamestate;

	int turn_number;
	int players_num;
	Graphic_Object** now_selected;	//array of units selected by users
	Graphic_Object* null_game_object;	//null object used to initialize now_selected array
										// and used when a unit that is selected dies (resets the user selection)_
public:
	std::stringstream** player_streams;

	Match(int, int, int);
	Match(std::istream&);	//for loading a match
	~Match();

	int save_Match(std::ostream&);
	void implement_turn();
	void interpret_user_command(std::string);
	void draw_match();

	int* return_object_selected_by(int player_number);	//change int to Game_Object in final version
	int current_turn_no(){ return turn_number; }
};

