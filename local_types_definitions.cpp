#include <sstream>
#include <iostream>
#include <string>
#include <map>

#include "local_types_definitions.h"

std::map<std::string, user_action> map_str_to_action;
std::map<std::string, user_option> map_str_to_option;

std::stringstream & operator>> (std::stringstream & sstream, user_action & _action)
{
	std::string str;
	sstream >> str;
	_action = map_str_to_action[str];
	return sstream;
}

std::stringstream & operator>> (std::stringstream & sstream, user_option & _option)
{
	std::string str;
	sstream >> str;
	_option = map_str_to_option[str];
	return sstream;
}