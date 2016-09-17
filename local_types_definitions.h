#pragma once
#include <map>
#include <string>
#include <sstream>

class Program_Core;


enum user_option{ user_height, user_width, user_brick };
enum user_action{ select, move, attack, build, turn, change_option, save_match, load_match, new_match, add_user, delete_user, exit_app };
enum game_obj_state{ idle, moving, attakcing, in_construction };
extern std::map<user_action, void (Program_Core::*)(int, user_action, std::stringstream &)> command_map;
extern std::map<std::string, user_action> map_str_to_action;
extern std::map<std::string, user_option> map_str_to_option;


std::stringstream & operator>> (std::stringstream &, user_action &);
std::stringstream & operator>> (std::stringstream &, user_option &);