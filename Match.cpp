#include <string>
#include <sstream>
#include <fstream>

#include "Match.h"
#include "Program_Core.h"
#include "Graphic_Object.h"

//Graphic_Object* Match::null_game_object = (Graphic_Object*)0;	//setting up the null object. this pointer will be copied to Gamestate

Graphic_Object* Match::null_graphic_object = new Graphic_Object(' ');

Match::Match(int _mapsize_x, int _mapsize_y, int _players) : number_of_active_users(_players)
{
	gamestate = new Gamestate(_mapsize_x, _mapsize_y, null_graphic_object);
	mapsize_x = _mapsize_x;
	mapsize_y = _mapsize_y;
	for (int i = 0; i < number_of_active_users; i++)
	{
		int selection_ints[2] = { 0, 0 };
		selected.push_back(selection_ints);
		player_streams.push_back(new std::stringstream);
	}
}

Match::Match(std::stringstream & command_stream, int number_of_active_users)
{
	
}

Match::Match(std::ifstream & load_from)
{
	load_from >> turn_number >> number_of_active_users >> mapsize_x >> mapsize_y;
	gamestate = new Gamestate(load_from);
	for (int i = 0; i < number_of_active_users; i++)
	{
		//now_selected[i] = null_game_object;
		player_streams.push_back(new std::stringstream);
	}
}

Match::~Match()
{
}

void Match::save_Match(std::ofstream & save_here)
{
	save_here << turn_number << ' ' << number_of_active_users << ' ' << mapsize_x << ' ' << mapsize_y << ' ';
	gamestate->save_Gamestate(save_here);
}

void Match::implement_turn()
{
	gamestate->implement_turn();
}

void Match::interpret_user_command(int calling_user, user_action action, std::stringstream & command_stream)
{
	//THROW exception handling here
	if (action == select)
	{
		change_selection(calling_user, command_stream);
	}
	else if (action == turn)
	{
		//THROW skip-turn
	}

	implement_turn();
}

void Match::change_selection(int calling_user, std::stringstream & command_stream)
{
	int new_x, new_y;
	command_stream >> new_x >> new_y;
	//check if order is within map bounds
	if ((new_x > mapsize_x) || (new_x < 0) || (new_y > mapsize_y) || (new_y < 0))
	{
		//throw out-of-map-bounds
	}
	//if order is within map bounds, set new selected unit
	selected[calling_user][0] = new_x;
	selected[calling_user][1] = new_y;
}

void Match::draw_match()
{ 
	for (int i = 0; i < number_of_active_users; i++)
	{
		player_streams[i]->clear();
		*(player_streams[i]) << mapsize_x << ' ' << mapsize_y << ' ' << gamestate->draw();
		*(player_streams[i]) << gamestate->show_selection(selected[i][0], selected[i][1]);
		//*(player_streams[i]) << " CranK " << "ducked " << 9001;
		
	}
	return;
}