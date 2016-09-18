#include <string>
#include <sstream>
#include <fstream>
#include <exception>

#include "Match.h"
#include "Program_Core.h"
#include "Graphic_Object.h"

#include "exc_base.h"

//Graphic_Object* Match::null_game_object = (Graphic_Object*)0;	//setting up the null object. this pointer will be copied to Gamestate

Graphic_Object* Match::null_graphic_object = new Graphic_Object(' ');

Match::Match(int _mapsize_x, int _mapsize_y, int _players) : number_of_active_users(_players)
{
	gamestate = new Gamestate(_mapsize_x, _mapsize_y);
	mapsize_x = _mapsize_x;
	mapsize_y = _mapsize_y;
	for (int i = 0; i < number_of_active_users; i++)
	{
		int* tmp = new int[2];
		tmp[0] = 0; tmp[1] = 0;
		selected.push_back(tmp);
		player_streams.push_back(new std::stringstream);
	}
}

Match::Match(std::ifstream & load_from)
{
	load_from >> turn_number >> number_of_active_users >> mapsize_x >> mapsize_y;
	gamestate = new Gamestate(load_from);
	selected.resize(number_of_active_users);
	for (int i = 0; i < number_of_active_users; i++)
	{
		int* tmp = new int[2];
		tmp[0] = 0; tmp[1] = 0;
		selected[i] = tmp;
		player_streams.push_back(new std::stringstream);
	}
}

Match::~Match()
{
	gamestate->~Gamestate();
	selected.clear();
	player_streams.clear();
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
	try
	{
		if (action == select)
		{
			change_selection(calling_user, command_stream);
		}
		else if (action == turn)
		{
			throw exc_base("Skipping the turn...\n");
		}
		else if ((action == move) || (action == attack))	//set unit actions
		{
			int curr_x = selected[calling_user][0];
			int curr_y = selected[calling_user][1];
			gamestate->order_unit(curr_x, curr_y, action, command_stream);
		}

		implement_turn();	//commence unit actions
	}
	catch (const std::exception & e)
	{
		std::cout << "CORE> " << e.what() << std::endl;
	}
}

void Match::change_selection(int calling_user, std::stringstream & command_stream)
{
	int new_x, new_y;
	command_stream >> new_x >> new_y;
	//check if order is within map bounds
	if ((new_x > mapsize_x) || (new_x < 0) || (new_y > mapsize_y) || (new_y < 0))
	{
		throw exc_base("Destination is out of the map bounds and thus unreachable.\n");
	}
	//if order is within map bounds, set new selected unit
	selected[calling_user][0] = new_x;
	selected[calling_user][1] = new_y;
}

void Match::draw_match()
{ 
	for (int i = 0; i < number_of_active_users; i++)
	{
		player_streams[i]->clear();	//error przy zabijaniu progframu
		*(player_streams[i]) << mapsize_x << ' ' << mapsize_y << ' ' << gamestate->draw();
		*(player_streams[i]) << gamestate->show_selection(selected[i][0], selected[i][1]);
		//*(player_streams[i]) << " CranK " << "ducked " << 9001;
	}
	return;
}