#include <string>
#include <iostream>
//#include <algorithm>

#include "User.h"

int User::number_of_active_users;

User::User(int height, int width)
{
	user_number = number_of_active_users;
	User::number_of_active_users++;
	screen_height = height;
	screen_total_height = height + 5;
	screen_width = width;
	screen_total_width = width + 4;
	screen_pos_x = 0;
	screen_pos_y = 0;
	interface_brick = '=';
}

User::~User()
{
	User::number_of_active_users--;
}

void User::read_user_input()
{
	user_input.clear();
	draw_menu();
	std::cout << "\nCommand> ";
	char* tmp = new char[50];
	std::cin.getline(tmp, 50);
	user_input << tmp;
}

std::stringstream & User::give_input()
{
	read_user_input();
	return user_input;
}

void User::modify_setting()
{
	user_option option = user_height;
	user_input >> option;
	if (option == 0)
	{
		int new_height;
		user_input >> new_height;
		// new_height > mapsize ? :<
		screen_height = new_height;
		screen_total_height = new_height + 5;
		std::cout << "New height is " << screen_height << std::endl;
	}
	else if (option == 1)
	{
		int new_width;
		user_input >> new_width;
		screen_width = new_width;
		screen_total_width = new_width + 4;
		std::cout << "New width is " << screen_width << std::endl;
	}
	else if (option == 2)
	{
		char new_brick;
		user_input >> new_brick;
		interface_brick = new_brick;
		std::cout << "New brick is " << interface_brick << std::endl;
	}

}

void User::prepare_mapview(std::string & mapview, int mapsize_x, int mapsize_y)
{
	// y part

	auto it = mapview.begin();
	it = mapview.erase(it, it + ((screen_pos_y)*mapsize_x));	//all the lines above what we want
	auto it2 = mapview.end();
	mapview.erase(it + mapsize_x*screen_height, it2);		//all the lines below what we want

	// x part

	for (it = mapview.begin(); it != mapview.end(); it += screen_width)
	{
		it2 = it + mapsize_x;
		it = mapview.erase(it, it + screen_pos_x);		//symbols before what we want in a line
		mapview.erase(it + screen_width, it2);		//symbols after what we want in a line
	}
}

void User::draw_interface_line(std::string & interface, const char brick_element)
{
	for (int i = 0; i < screen_total_width; i++)
	{
		interface += brick_element;
	}
}

void User::draw_mapview(std::string & interface, std::string & mapview)
{
	std::string::iterator it2;
	auto it = it2 = mapview.begin();
	for (int i = 0; i < screen_height; i++, it = it2)
	{
		it2 = it + screen_width;
		interface += interface_brick;
		interface += ' ';
		interface.append(it, it2);
		interface += ' ';
		interface += interface_brick;
		interface += '\n';
	}
}

void User::draw_ui(std::string & interface, std::stringstream & output_stream)
{
	std::string unit_name, status, health;
	char* tmp_desc = new char[screen_width];
	output_stream >> unit_name >> status >> health;
	output_stream.getline(tmp_desc, screen_width);
	std::string description(tmp_desc);
	delete[] tmp_desc;
	std::string str1(" UNIT NAME");
	std::string str2("UNIT STATUS ");
	int pause1to2 = screen_total_width - str1.length() - str2.length() - 2;
	int pause3to4 = screen_total_width - unit_name.length() - status.length() - 4;

	interface += '\n';
	interface += interface_brick;
	interface += str1;
	for (int i = 0; i < pause1to2; i++)
	{
		interface += ' ';
	}
	interface += str2;
	interface += interface_brick;
	interface += '\n';
	interface += interface_brick;
	interface += ' ';
	interface += unit_name;
	for (int i = 0; i < pause3to4; i++)
	{
		interface += ' ';
	}
	interface += status;	interface += ' ';	interface += interface_brick;	interface += '\n';
	interface += interface_brick;	interface += ' ';	interface += "\n";
	interface += interface_brick;	interface += " HEALTH: ";	interface += health;	interface += '\n';
	interface += interface_brick;	interface += description;	interface += '\n';
}

void User::show_to_player(std::stringstream & output_stream)
{
	int mapsize_y, mapsize_x;
	std::string mapview;
	output_stream >> mapsize_x >> mapsize_y >> mapview;

	prepare_mapview(mapview, mapsize_x, mapsize_y);	//erase parts not visible on end screen

	std::string interface = "";

	draw_interface_line(interface, interface_brick);	//draw a horizontal line of brick elements
	interface += '\n';
	draw_mapview(interface, mapview);	//put the cut out piece of mapview into interface
	draw_interface_line(interface, interface_brick);
	draw_ui(interface, output_stream);
	draw_interface_line(interface, interface_brick);

	std::cout << std::endl << interface << std::endl;
}

void User::draw_menu()
{
	std::string interface = "";
	draw_interface_line(interface, interface_brick);
	interface += "\n STRATEGY GAME MENU\nAvailable commands:\n\n";
	interface += "User options:\nchange [height/width/brick] [new value]\n";
	interface += "create match [mapsize]\nload match [filename]\nsave match [filename]\n";
	interface += "select [x] [y]\nattack [x] [y]\nclose\nexit\n";
	draw_interface_line(interface, interface_brick);
	std::cout << interface << std::endl;
}
