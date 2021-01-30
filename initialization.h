#pragma once

#include<SFML/Graphics.hpp>

using namespace sf;

namespace minesweeper
{
	
	//main menu
	void main_menu();

	//window where player chooses difficulty
	void choose_difficulty_window();

	//game window
	void game();

	//Create two dimensional dinamic array
	void create_arr(int**&, int, int);
	void create_arr(Sprite**&, int, int);
	void create_arr(bool**&, int, int);

	//setting texture after counting the bombs round the block
	void set_texture_num(Sprite&, int);

	//checks how many bombs are there roud the block and changes its texture
	void check_bomb(Sprite**&, int**&, bool**&, int**&, int, int, int, int);
}
