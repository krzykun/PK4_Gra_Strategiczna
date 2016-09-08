#pragma once
#include <iostream>
#include <string>

class User
{
	int screen_height;
	int screen_width;
public:
	User(int player_number);
	~User();
	int read_user_input();
	std::string user_command();			//returns the user input
	int modify_setting(int, int);	//modifies the user setting of par1 number, for a value of par2
	void show_user_stats(std::ostream&);	//prints user statistics to the ostream
	void show_user_settings(std::ostream&);	//prints user settings to the stream
	int get_height() { return screen_height; }
	int get_width() { return screen_width; }
};

