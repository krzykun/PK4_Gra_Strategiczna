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
	/*
	Graphic_Object nowy('P');
	Graphic_Object nowy2;
	std::cout << nowy.draw() << nowy2.draw();
	int bzdet;
	std::cin >> bzdet;
	system("pause");
	Map mapka1(100, 100, &nowy);
	std::cout << mapka1.show_gamefield(0,0).str() << std::endl;
	system("pause");
	*/
	/*
	Gamestate test1;
	test1.tmp_set_filler('2');
	std::cout << test1.draw();
	*/
	/*
	Match abc(10, 10, 1);
	abc.draw_match();
	std::cout << abc.player_streams[0]->str();
	*/


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
	map_str_to_action["exit"] = exit_app;

	map_str_to_option["height"] = user_height;
	map_str_to_option["width"] = user_width;
	map_str_to_option["brick"] = user_brick;
	
	User::init_player_number();
	Program_Core Core;
	
	try
	{
		while (1)
		{
			Core.interpret_user_command();
		}
	}
	catch (...)
	{
		std::cout << "unidentified error. Closing game..." << std::endl;
	}
	
	/*
	Core.create_new_match(100, 100);
	Core.draw_match();
	Core.save_match(filename);
	*/

	//std::string teststring("input_test.txt");
	//const char* filename = teststring.c_str();
	////Core.load_match(filename);

	//Core.draw_match();

	system("pause");
}