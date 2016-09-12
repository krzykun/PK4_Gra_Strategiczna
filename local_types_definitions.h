#include <map>
#include <string>
#include <sstream>

class Program_Core;

enum user_action{ inmatch_command, change_option, save_match, load_match, new_match };
std::map<user_action, void (Program_Core::*)(user_action, std::stringstream &)> command_map;
std::map<char*, user_action> map_cstr_to_action;

std::stringstream & operator>> (std::stringstream &, user_action);