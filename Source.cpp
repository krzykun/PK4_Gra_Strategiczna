#include <iostream>
#include <conio.h>
#include <map>

#include "local_types_definitions.h"
#include "Graphic_Object.h"
#include "Gamestate.h"
#include "Map.h"
#include "Match.h"
#include "Program_Core.h"
#include "User.h"

int main()
{
	command_map.emplace(select, &(Program_Core::inmatch_command));
	command_map[move] = &(Program_Core::inmatch_command);
	command_map[attack] = &(Program_Core::inmatch_command);
	command_map[build] = &(Program_Core::inmatch_command);
	command_map[turn] = &(Program_Core::inmatch_command);
	command_map[change_option] = &(Program_Core::change_user_option);
	command_map[save_match] = &(Program_Core::save_match);
	command_map[load_match] = &(Program_Core::load_match);
	command_map[new_match] = &(Program_Core::create_new_match);
	command_map[add_user] = &(Program_Core::add_new_user);
	command_map[delete_user] = &(Program_Core::delete_user);
	command_map[close_match] = &(Program_Core::close_match);
	command_map[exit_app] = &(Program_Core::exit);

	map_str_to_action["select"] = select;
	map_str_to_action["move"] = move;
	map_str_to_action["attack"] = attack;
	map_str_to_action["build"] = build;
	map_str_to_action["turn"] = turn;
	map_str_to_action["change"] = change_option;
	map_str_to_action["save"] = save_match;
	map_str_to_action["load"] = load_match;
	map_str_to_action["new"] = new_match;
	map_str_to_action["add_user"] = add_user;
	map_str_to_action["delete"] = delete_user; 
	map_str_to_action["close"] = close_match;
	map_str_to_action["exit"] = exit_app;

	map_str_to_option["height"] = user_height;
	map_str_to_option["width"] = user_width;
	map_str_to_option["brick"] = user_brick;
	
	User::init_player_number();
	Program_Core Core;
	Gamestate::null_game_object = Match::null_graphic_object;
	
	try
	{
		while (1)
		{
			Core.interpret_user_command();
		}
	}
	catch (const std::exception & e)
	{
		std::cout << "CORE> " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "CORE> An unidentified error occured. Closing game..." << std::endl;
	}
	
	system("pause");
}