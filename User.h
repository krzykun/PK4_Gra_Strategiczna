#pragma once
#include <iostream>
#include <string>
#include <sstream>

#include "local_types_definitions.h"

class User
{
	int user_number;
	int screen_height;
	int scren_total_height;

	int screen_width;
	int screen_total_width;

	int screen_pos_x;
	int screen_pos_y;
	char interface_brick;
	static int number_of_active_users;
	std::stringstream user_input;
public:
	enum user_option{ user_height, user_width, user_brick };

	User(int height = 15, int width = 30);
	~User();
	void read_user_input();
	std::stringstream & give_input();			//returns the user input

	//
	int modify_setting(user_option);	//modifies the user setting of par1 number, for a value of par2
	void show_user_stats(std::ostream&);	//prints user statistics to the ostream
	void show_user_settings(std::ostream&);	//prints user settings to the stream
	int get_height() { return screen_height; }
	void set_height(int new_height) { screen_height = new_height; }
	void set_width(int new_width) { screen_width = new_width; }
	int get_width() { return screen_width; }

	//drawing functions
	void show_to_player(std::stringstream &);
	void prepare_mapview(std::string &, int, int);
	void draw_interface_line(std::string &, const char);
	void draw_mapview(std::string &, std::string &);
	void draw_ui(std::string &, std::stringstream &);

	static void init_player_number(){ number_of_active_users = 0; }
};

