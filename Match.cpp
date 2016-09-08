#include "Match.h"
#include "Program_Core.h"
#include "Graphic_Object.h"
#include <string>
#include <sstream>

Program_Core Core;	//forward declaration of program core
//Graphic_Object* Match::null_game_object = (Graphic_Object*)0;	//setting up the null object. this pointer will be copied to Gamestate

Match::Match(int mapsize_x, int mapsize_y, int _players) : null_game_object(new Graphic_Object('X')), players_num(_players)
{
	gamestate = new Gamestate(mapsize_x, mapsize_y, null_game_object);
	now_selected = new Graphic_Object*[players_num];
	for (int i = 0; i < players_num; i++)
	{
		now_selected[i] = this->null_game_object;
		player_streams[i] = new std::stringstream;
	}
}


Match::~Match()
{
}

void Match::draw_match()
{ 
	std::string tmp_string;
	tmp_string = gamestate->draw();
	std::stringstream ssvisible_match;

	for (int i = 0; i < players_num; i++)
	{
		
	}
	return;
}