#include <fstream>
#include <iostream>
#include <map>
#include <exception>

#include "local_types_definitions.h"
#include "Program_Core.h"
#include "exc_base.h"

std::map<user_action, void (Program_Core::*)(int, user_action, std::stringstream &)> command_map;

Program_Core::Program_Core()
{
	current_match = (Match*)0;
	number_of_active_users = 1;
	User* new_user = new User;
	active_users.push_back(new_user);
}

Program_Core::~Program_Core()
{
	active_users.clear();
	last_user_input.clear();
	delete current_match;
}

void Program_Core::interpret_user_command()
{
	for (int i = 0; i < number_of_active_users; i++)
	{
		std::stringstream & user_input_stream = active_users[i]->give_input();
		user_action action = change_option;	//initialized just so the compiler wont complain
		user_input_stream >> action;

		try
		{
			(this->*(command_map[action]))(i, action, user_input_stream);
		}
		catch (const exc_base & e)
		{
			std::cout << "CORE> " << e.what() << std::endl;
		}
		user_input_stream.clear();
	}
	if (current_match)
	{
		this->draw_match();
	}
}

void Program_Core::create_new_match(int player_number, user_action action, std::stringstream & command_stream)
{
	if (current_match)
	{
		throw exc_base("A Match already exists. Cannot create a new one.\n");
	}
	int mapsize_x, mapsize_y;
	command_stream >> mapsize_x >> mapsize_y;
	current_match = new Match(mapsize_x, mapsize_y, number_of_active_users);
	return;
}

void Program_Core::save_match(int player_number, user_action action, std::stringstream & command_stream)
{
	if (!current_match)
	{
		throw exc_base("No match exists to be saved.\n");
	}
	std::string str_filename;
	command_stream >> str_filename;
	const char* filename = str_filename.c_str();
	std::ofstream save_here(filename);

	if (!save_here)
	{
		throw exc_base("File opening error.\n");
	}

	save_here << Program_Core::number_of_active_users << ' ';
	current_match->save_Match(save_here);
}

void Program_Core::load_match(int player_number, user_action action, std::stringstream & command_stream)
{
	if (current_match)
	{
		throw exc_base("A match is already in play, cannot load a new one.\n");
	}
	std::string str_filename;
	command_stream >> str_filename;
	const char* filename = str_filename.c_str();
	std::ifstream load_from(filename);

	if (!load_from)
	{
		throw exc_base("File opening error.\n");
	}

	int tmp_users_number;
	load_from >> tmp_users_number;

	if (tmp_users_number != number_of_active_users)
	{
		throw exc_base("Wrong number of users, add or delete users.\n");
	}
	current_match = new Match(load_from);
}

void Program_Core::change_user_option(int player_number, user_action action, std::stringstream & command_stream)
{
	active_users[player_number]->modify_setting();
}

void Program_Core::inmatch_command(int player_number, user_action action, std::stringstream & command_stream)
{
	if (current_match)
	{
		current_match->interpret_user_command(player_number, action, command_stream);
	}
	else
	{
		throw exc_base("No match present.\n");
	}
}

void Program_Core::add_new_user(int, user_action, std::stringstream & command_stream)
{
	if (current_match)
	{
		throw exc_base("A match is underway, cannot add users during a Match.\n");
	}
	User* new_user = new User;
	active_users.push_back(new_user);
	Program_Core::number_of_active_users++;
	return;
}

void Program_Core::delete_user(int, user_action, std::stringstream & command_stream)
{
	if (current_match)
	{
		throw exc_base("A match is underway, cannot delete users during a Match.\n");
	}
	int delete_me;
	command_stream >> delete_me;
	delete active_users[delete_me];
	Program_Core::number_of_active_users--;
}

void Program_Core::close_match(int, user_action, std::stringstream &)
{
	if (!current_match)
	{
		throw exc_base("No match to close.\n");
	}
	current_match->~Match();
	current_match = 0;
}

void Program_Core::exit(int, user_action, std::stringstream &)
{
	if (current_match)
	{
		throw exc_base("A match is underway, please end it first before leaving.\n");
	}
	throw std::exception("Closing game...\n");
}

bool Program_Core::is_match_in_progress()
{
	if (current_match) return 1;
	else return 0;
}

void Program_Core::draw_match()
{
	current_match->draw_match();
	for (int i = 0; i < number_of_active_users; i++)
	{
		active_users[i]->show_to_player(*(current_match->player_streams[i]));
	}
}