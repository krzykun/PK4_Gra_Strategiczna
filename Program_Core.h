#pragma once
#include <string>
#include <vector>

#include "Match.h"
#include "User.h"

class Program_Core
{
	int number_of_active_users;
	Match* current_match;
	std::vector<std::string> last_user_input;
public:
	std::vector<User*> active_users;

	Program_Core();
	~Program_Core();

	//main loop function reading input
	void interpret_user_command();

	//menu functions
	void create_new_match(user_action, std::stringstream &);
	void save_match(user_action, std::stringstream &);
	void load_match(user_action, std::stringstream &);
	void change_user_option(user_action, std::stringstream &);
	void inmatch_command(user_action, std::stringstream &);

	//side functions
	void print_for_user(int player_id, std::stringstream print_this);
	int how_many_active_users(){ return number_of_active_users; }
	bool is_match_in_progress();
	void add_user(User*);
	void draw_match();
};

