#pragma once
#include <string>
#include "Match.h"
#include "User.h"

class Program_Core
{
	int number_of_active_users;
public:
	User** active_users;

	Program_Core();
	~Program_Core();

	void interpret_user_command(std::string);
	Match* create_new_match();
	void save_match();
	void load_match();
	void print_for_user(int player_id, std::stringstream print_this);
	int how_many_active_users(){ return number_of_active_users; }
	bool is_match_in_progress();
};

