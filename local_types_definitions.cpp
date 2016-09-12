#include <sstream>

#include "local_types_definitions.h"

//command_map
{
	command_map[inmatch_command] = Program_Core::inmatch_command;
	command_map[change_option] = Program_Core::change_user_option;
	command_map[save_match] = Program_Core::save_match;
	command_map[load_match] = Program_Core::load_match;
	command_map[new_match] = Program_Core::create_new_match;

}

//map_cstr_to_action
{
	map_cstr_to_action["select"] = inmatch_command;
	map_cstr_to_action["move"] = inmatch_command;
	map_cstr_to_action["attack"] = inmatch_command;
	map_cstr_to_action["option"] = change_option;
	map_cstr_to_action["save"] = save_match;
	map_cstr_to_action["load_match"] = load_match;
	map_cstr_to_action["new_match"] = new_match;
}

std::stringstream & operator>> (std::stringstream & sstream, user_action _action)
{
	char* cstr_action;
	sstream >> cstr_action;
	_action = map_cstr_to_action[cstr_action];
	return sstream;
}