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
	now_selected = new Graphic_Object*[number_of_active_users];
	for (int i = 0; i < number_of_active_users; i++)
	{
		now_selected[i] = null_graphic_object;
		player_streams.push_back(new std::stringstream);
	}
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

void Match::draw_match()
{ 
	for (int i = 0; i < number_of_active_users; i++)
	{
		player_streams[i]->clear();
		*(player_streams[i]) << mapsize_x << ' ' << mapsize_y << ' ' << gamestate->draw() << " CranK " << "ducked " << 9001 ;

	}
	return;
}