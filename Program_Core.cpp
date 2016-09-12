#include <fstream>
#include <iostream>
#include <map>

#include "Program_Core.h"
#include "local_types_definitions.h"

Program_Core::Program_Core()
{
	current_match = (Match*)0;
	number_of_active_users = 0;
}


Program_Core::~Program_Core()
{
}

void Program_Core::interpret_user_command()
{
	std::stringstream & user_input_stream = active_users[0]->give_input();
	user_action action;
	user_input_stream >> action;
	(*(command_map[action]))(action, user_input_stream);

	for (int i = 0; i < number_of_active_users; i++)
	{
		//last_user_input[i] = active_users[i]->give_input();
	}
}

void Program_Core::create_new_match(user_action action, std::stringstream & command_stream)
{
	int mapsize_x, mapsize_y;
	command_stream >> mapsize_x >> mapsize_y;
	current_match = new Match(mapsize_x, mapsize_y, number_of_active_users);
	return;
}

void Program_Core::save_match(user_action action, std::stringstream & command_stream)
{

	const char* filename;
	command_stream >> filename;
	std::ofstream save_here(filename);
	save_here << number_of_active_users << ' ';
	current_match->save_Match(save_here);
}

void Program_Core::load_match(const char* filename)
{
	std::ifstream load_from(filename);
	int tmp_users_number;
	load_from >> tmp_users_number;
	if (tmp_users_number != number_of_active_users)
	{
		std::cout << "Wrong number of users, plz" << std::endl;
		return;
	}
	current_match = new Match(load_from);
}

bool Program_Core::is_match_in_progress()
{
	if (current_match) return 1;
	else return 0;
}

void Program_Core::add_user(User* new_user)
{
	active_users.push_back(new_user);
	number_of_active_users++;
	return;
}

void Program_Core::draw_match()
{
	current_match->draw_match();
	for (int i = 0; i < number_of_active_users; i++)
	{
		active_users[i]->show_to_player(*(current_match->player_streams[i]));
	}
}