
#include "Graphic_Object.h"
#include "Gamestate.h"
#include "Map.h"
#include "Match.h"
#include "Program_Core.h"
#include "User.h"

#include <iostream>
#include <conio.h>

int main()
{
	/*
	Graphic_Object nowy('P');
	Graphic_Object nowy2;
	std::cout << nowy.draw() << nowy2.draw();
	int bzdet;
	std::cin >> bzdet;
	system("pause");
	Map mapka1(100, 100, &nowy);
	std::cout << mapka1.show_gamefield(0,0).str() << std::endl;
	system("pause");
	*/
	/*
	Gamestate test1;
	test1.tmp_set_filler('2');
	std::cout << test1.draw();
	*/
	/*
	Match abc(10, 10, 1);
	abc.draw_match();
	std::cout << abc.player_streams[0]->str();
	*/

	User::init_player_number();
	Program_Core Core;
	Core.add_user(new User);
	/*
	while (1)
	{
		Core.interpret_user_command();
	}
	*/
	/*
	Core.create_new_match(100, 100);
	Core.draw_match();
	Core.save_match(filename);
	*/

	std::string teststring("input_test.txt");
	const char* filename = teststring.c_str();
	Core.load_match(filename);

	Core.draw_match();

	system("pause");
}