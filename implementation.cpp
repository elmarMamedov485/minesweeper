#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <time.h>
#include <sstream>
#include "initialization.h"

using namespace std;
using namespace sf;

namespace minesweeper
{
	//main game textures
	Texture one;
	Texture two;
	Texture three;
	Texture four;
	Texture five;
	Texture six;
	Texture seven;
	Texture eight;
	Texture block;
	Texture empty_block;
	Texture flagged_block;
	Texture mine;
	Texture angry;
	Texture happy;
	Texture worried;
	Texture boss;
	Vector2f block_scale;

	//this variable is used not to make music beginning from start every time the new window opens
	float music_offset;

	//grid size
	int grid_w; //grid width
	int grid_h; //grid height;

	//number of mines
	int mine_count;

	//number of flags
	int flag_count;

	//first move
	bool first_move = false;

	//padding - is used to put blocks together 
	int padding;

	//grid position
	int grid_x;
	int grid_y;

	//checks if user lost the game ; 1 - lose , 2 - win, 0 - playing
	int game_over = 0;

	void main_menu()
	{
		//configuring window
		RenderWindow main_menu(VideoMode(VideoMode::getDesktopMode().width - 200, VideoMode::getDesktopMode().height - 100), "Minesweeper", Style::Close | Style::Titlebar);

		//configuring application icon
		Image icon;
		icon.loadFromFile("textures/icon.png");
		main_menu.setIcon(900, 900, icon.getPixelsPtr());

		//configuring text
		Font font;
		Text minesweeper_text;

		font.loadFromFile("fonts/KashimaDemo.otf");

		minesweeper_text.setFont(font);
		minesweeper_text.setString("Minesweeper");
		minesweeper_text.setCharacterSize(120);
		minesweeper_text.setFillColor(Color::Black);
		minesweeper_text.setPosition(275, 75);

		//configuring background
		Sprite main_menu_bg;
		Texture bg;

		if (!bg.loadFromFile("textures/main_menu_bg.jpg"))
		{
			cout << "Can't open file";
		}
		main_menu_bg.setTexture(bg);

		//configuring audio
		SoundBuffer buffer;
		Sound sound;

		if (!buffer.loadFromFile("music/music.ogv"))
		{
			cout << "Can't open file";
		}

		sound.setBuffer(buffer);

		sound.play();
		sound.setLoop(true);
		sound.setVolume(50.0f);
		sound.setPlayingOffset(milliseconds(music_offset));

		//play button
		Sprite play_button;
		Texture play_texture;
		Vector2f play_button_size(185.0f, 185.0f);

		play_button.setOrigin(50.0f, 50.0f);

		if (!play_texture.loadFromFile("textures/play.png"))
		{
			cout<<"Can't open file";
		}
		play_button.setTexture(play_texture);
		play_button.setScale(play_button_size.x / play_button.getLocalBounds().width,
			play_button_size.y / play_button.getLocalBounds().height);
		play_button.setPosition(510, 300);

		//quit button
		Sprite quit_button;
		Texture quit_texture;
		Vector2f quit_button_size(125.0f, 125.0f);

		if (!quit_texture.loadFromFile("textures/quit.png"))
		{
			cout << "Can't open file";
		}
		quit_button.setTexture(quit_texture);
		quit_button.setScale(quit_button_size.x / quit_button.getLocalBounds().width,
			quit_button_size.y / quit_button.getLocalBounds().height);
		quit_button.setPosition(1035, 540);

		//bringing window to life
		while (main_menu.isOpen())
		{
			Event evnt;

			while (main_menu.pollEvent(evnt))
			{
				switch(evnt.type)
				{
					case Event::Closed : 

						main_menu.close();

						break;
				}

				
				//detecting if any of buttons is clicked
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					//mouse x and y
					int x = Mouse::getPosition(main_menu).x;
					int y = Mouse::getPosition(main_menu).y;

					//if play button is clicked
					if (play_button.getPosition().x <= x + 10 && play_button.getPosition().x  >= x - 100
						&& play_button.getPosition().y <= y + 10 && play_button.getPosition().y >= y - 170)
					{
						main_menu.close();					
						music_offset = sound.getPlayingOffset().asMilliseconds();
						sound.stop();
						choose_difficulty_window();
					}

					//if quit button is clicked
					if (quit_button.getPosition().x <= x - 10 && quit_button.getPosition().x >= x - 110
						&& quit_button.getPosition().y <= y + 1 && quit_button.getPosition().y >= y - 110)
					{
						main_menu.close();
					}
				}
				
			}

			main_menu.clear();
			main_menu.draw(main_menu_bg);
			main_menu.draw(minesweeper_text);
			main_menu.draw(play_button);
			main_menu.draw(quit_button);
			main_menu.display();
		}
	}
	void choose_difficulty_window()
	{
		RenderWindow choose_difficulty(VideoMode(VideoMode::getDesktopMode().width - 200, VideoMode::getDesktopMode().height - 100), "Minesweeper", Style::Close | Style::Titlebar);

		//configuring application icon
		Image icon;
		icon.loadFromFile("textures/icon.png");
		choose_difficulty.setIcon(900, 900, icon.getPixelsPtr());

		//configuring text
		Font font;
		Text choose_difficulty_text;

		font.loadFromFile("fonts/r.otf");

		choose_difficulty_text.setFont(font);
		choose_difficulty_text.setString("CHOOSE DIFFICULTY : ");
		choose_difficulty_text.setCharacterSize(70);
		choose_difficulty_text.setFillColor(Color::Black);
		choose_difficulty_text.setPosition(25, 75);

		// "beginner" text
		Text beginner_text;

		beginner_text.setFont(font);
		beginner_text.setString("BEGINNER");
		beginner_text.setCharacterSize(45);
		beginner_text.setFillColor(Color::Black);
		beginner_text.setPosition(45, 185);

		// "intermediate" text
		Text intermediate_text;

		intermediate_text.setFont(font);
		intermediate_text.setString("INTERMEDIATE");
		intermediate_text.setCharacterSize(45);
		intermediate_text.setFillColor(Color::Black);
		intermediate_text.setPosition(45, 275);

		// "expert" text
		Text expert_text;

		expert_text.setFont(font);
		expert_text.setString("EXPERT");
		expert_text.setCharacterSize(45);
		expert_text.setFillColor(Color::Black);
		expert_text.setPosition(45, 365);

		//back button
		Sprite back_button;
		Texture back_texture;
		Vector2f back_button_scale(75.0f, 75.0f);

		if (!back_texture.loadFromFile("textures/back.png"))
		{
			cout << "Can't open file";
		}
		back_button.setTexture(back_texture);
		back_button.setScale(back_button_scale.x / back_button.getLocalBounds().width,
			back_button_scale.y / back_button.getLocalBounds().height);
		back_button.setPosition(1075, 575);

		//configuring background
		Sprite choose_difficulty_bg;
		Texture bg;

		if (!bg.loadFromFile("textures/main_menu_bg.jpg"))
		{
			cout << "Can't open file";
		}
		choose_difficulty_bg.setTexture(bg);

		//configuring audio
		SoundBuffer buffer;
		Sound sound;

		if (!buffer.loadFromFile("music/music.ogv"))
		{
			cout << "Can't open file";
		}

		sound.setBuffer(buffer);

		sound.play();
		sound.setLoop(true);
		sound.setVolume(50.0f);
		sound.setPlayingOffset(milliseconds(music_offset));
		
		//bringing window to life
		while (choose_difficulty.isOpen())
		{
			Event evnt;

			while (choose_difficulty.pollEvent(evnt))
			{
				switch (evnt.type)
				{
					case Event::Closed:

						choose_difficulty.close();

						break;
				}

				//checks if any button was clicked by user
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					int x = Mouse::getPosition(choose_difficulty).x;
					int y = Mouse::getPosition(choose_difficulty).y;

					//checks if back button clicked
					if (back_button.getPosition().x <= x + 1 && back_button.getPosition().x >= x - 100
						&& back_button.getPosition().y <= y + 1 && back_button.getPosition().y >= y - 170)
					{
						choose_difficulty.close();
						music_offset = sound.getPlayingOffset().asMilliseconds();
						sound.stop();
						main_menu();
					}

					//if beginnner text was clicked
					if (beginner_text.getPosition().x <= x + 1 && beginner_text.getPosition().x >= x - 250
						&& beginner_text.getPosition().y <= y + 1 && beginner_text.getPosition().y >= y - 50)
					{
						grid_w = 8;
						grid_h = 8;
						mine_count = 10;
						flag_count = 10;
						music_offset = sound.getPlayingOffset().asMilliseconds();
						sound.stop();
						choose_difficulty.close();
						block_scale = Vector2f(4.0f, 4.0f);
						grid_x = 325;
						grid_y = 100;
						padding = 65;
						game_over = 0;
						first_move = false;
						game();
					}

					//if intermediate text was clicked
					if (intermediate_text.getPosition().x <= x + 1 && intermediate_text.getPosition().x >= x - 330
						&& intermediate_text.getPosition().y <= y + 1 && intermediate_text.getPosition().y >= y - 50)
					{
						grid_w = 16;
						grid_h = 16;
						mine_count = 40;
						flag_count = 40;
						music_offset = sound.getPlayingOffset().asMilliseconds();
						sound.stop();
						choose_difficulty.close();
						block_scale = Vector2f(2.5f, 2.5f);
						grid_x = 250;
						grid_y = 15;
						padding = 40;
						game_over = 0;
						first_move = false;
						game();
					}

					//if expert text was clicked
					if (expert_text.getPosition().x <= x + 1 && expert_text.getPosition().x >= x - 200
						&& expert_text.getPosition().y <= y + 1 && expert_text.getPosition().y >= y - 50)
					{
						grid_w = 30;
						grid_h = 30;
						mine_count = 250;
						flag_count = 250;
						music_offset = sound.getPlayingOffset().asMilliseconds();
						sound.stop();
						choose_difficulty.close();
						block_scale = Vector2f(1.25f, 1.25f);
						grid_x = 250;
						grid_y = 20;
						padding = 21;
						game_over = 0;
						first_move = false;
						game();
					}
				}
			}

			choose_difficulty.clear();
			choose_difficulty.draw(choose_difficulty_bg);
			choose_difficulty.draw(choose_difficulty_text);
			choose_difficulty.draw(beginner_text);
			choose_difficulty.draw(intermediate_text);
			choose_difficulty.draw(expert_text);
			choose_difficulty.draw(back_button);
			choose_difficulty.display();
		}
	}
	void create_arr(int**& arr, int size_1, int size_2)
	{
		arr = new int*[size_1];

		for (int i = 0; i < size_1; i++)
		{
			arr[i] = new int[size_2];
		}

		for (int k = 0; k < grid_w; k++)
		{
			for (int t = 0; t < grid_h; t++)
			{
				arr[k][t] = 0;
			}
		}
	}
	void create_arr(Sprite**& arr, int size_1, int size_2)
	{
		arr = new Sprite*[size_1];

		for (int i = 0; i < size_1; i++)
		{
			arr[i] = new Sprite[size_2];
		}
	}
	void create_arr(bool**& arr, int size_1, int size_2)
	{
		arr = new bool* [size_1];

		for (int i = 0; i < size_1; i++)
		{
			arr[i] = new bool[size_2];
		}

		for (int i = 0; i < size_1; i++)
		{
			for (int j = 0; j < size_2; j++)
			{
				arr[i][j] = false;
			}
		}
	}
	void set_texture_num(Sprite& block, int bomb_count)
	{
		

		if (!one.loadFromFile("textures/one.png") || !two.loadFromFile("textures/two.png")
			|| !three.loadFromFile("textures/three.png") || !four.loadFromFile("textures/four.png")
			|| !five.loadFromFile("textures/five.png") || !six.loadFromFile("textures/six.png")
			|| !seven.loadFromFile("textures/seven.png") || !eight.loadFromFile("textures/eight.png")
			|| !empty_block.loadFromFile("textures/empty.png"))
		{
			cout << "Can't open all files";
		}

		switch (bomb_count)
		{
			case 0:

				block.setTexture(empty_block);
				block.setScale(block_scale);

				break;

			case 1:

				block.setTexture(one);
				block.setScale(block_scale);

				break;

			case 2:

				block.setTexture(two);
				block.setScale(block_scale);

				break;

			case 3:

				block.setTexture(three);
				block.setScale(block_scale);

				break;

			case 4:

				block.setTexture(four);
				block.setScale(block_scale);

				break;

			case 5:

				block.setTexture(five);
				block.setScale(block_scale);

				break;

			case 6:

				block.setTexture(six);
				block.setScale(block_scale);

				break;

			case 7:

				block.setTexture(seven);
				block.setScale(block_scale);

				break;

			case 8:

				block.setTexture(eight);
				block.setScale(block_scale);

				break;

			case 9:

				block.setTexture(mine);
				block.setScale(block_scale);
		}
	}
	void check_bomb(Sprite**& grid, int**& bomb_grid, bool**& opened_grid, int**& flagged_grid, int grid_h, int grid_w, int i, int j)
	{
		//top left corner
		if (i == 0 && j == 0 && opened_grid[i][j] == false && bomb_grid[i][j] == 0 && flagged_grid[i][j] == 0)
		{
			int bomb_count = 0;
			
			if (bomb_grid[i][j + 1] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i + 1][j] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i + 1][j + 1] == 1)
			{
				bomb_count++;
			}

			set_texture_num(grid[i][j], bomb_count);

			opened_grid[i][j] = true;

			if (bomb_count == 0)
			{
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i, j + 1);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i + 1, j);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i + 1, j + 1);
			}
			else
			{
				return;
			}
		}
		//bottom left corner
		else if (i == 0 && j == grid_w - 1 && opened_grid[i][j] == false && bomb_grid[i][j] == 0 && flagged_grid[i][j] == 0)
		{
			int bomb_count = 0;
			
			if (bomb_grid[i][j - 1] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i + 1][j] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i + 1][j - 1] == 1)
			{
				bomb_count++;
			}

			set_texture_num(grid[i][j], bomb_count);

			opened_grid[i][j] = true;

			if (bomb_count == 0)
			{
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i, j - 1);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i + 1, j);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i + 1, j - 1);
			}
			else
			{
				return;
			}
		}
		//top right corner
		else if (i == grid_w - 1 && j == 0 && opened_grid[i][j] == false && bomb_grid[i][j] == 0 && flagged_grid[i][j] == 0)
		{
			int bomb_count = 0;
			
			if (bomb_grid[i - 1][j] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i - 1][j + 1] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i][j + 1] == 1)
			{
				bomb_count++;
			}

			cout << bomb_count;
			set_texture_num(grid[i][j], 0);

			opened_grid[i][j] = true;

			if (bomb_count == 0)
			{
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i  + 1, j);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i , j + 1);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i - 1, j + 1);
			}
			else
			{
				return;
			}
		}
		//bottom right corner
		else if (i == grid_w - 1 && j == grid_h - 1 && opened_grid[i][j] == false && bomb_grid[i][j] == 0 && flagged_grid[i][j] == 0)
		{
			int bomb_count = 0;
			
			if (bomb_grid[i][j - 1] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i - 1][j] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i - 1][j - 1] == 1)
			{
				bomb_count++;
			}

			set_texture_num(grid[i][j], bomb_count);

			opened_grid[i][j] = true;

			if (bomb_count == 0)
			{
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i, j - 1);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i - 1, j);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i - 1, j - 1);
			}
			else
			{
				return;
			}
		}
		//furthest left side except corners
		else if (i == 0 && j > 0 && j < grid_h - 1 && opened_grid[i][j] == false && bomb_grid[i][j] == 0 && flagged_grid[i][j] == 0)
		{
			int bomb_count = 0;
			
			if (bomb_grid[i][j - 1] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i + 1][j - 1] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i + 1][j] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i + 1][j + 1] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i][j + 1] == 1)
			{
				bomb_count++;
			}

			set_texture_num(grid[i][j], bomb_count);

			opened_grid[i][j] = true;

			if (bomb_count == 0)
			{
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i, j - 1);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i + 1, j - 1);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i + 1, j);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i + 1, j + 1);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i, j + 1);
			}
			else
			{
				return;
			}
		}
		//furthest top side except corners
		else if (j == 0 && i > 0 && i < grid_w - 1 && opened_grid[i][j] == false && bomb_grid[i][j] == 0 && flagged_grid[i][j] == 0)
		{
			int bomb_count = 0;
			
			if (bomb_grid[i - 1][j] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i - 1][j + 1] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i][j + 1] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i + 1][j + 1] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i + 1][j] == 1)
			{
				bomb_count++;
			}

			set_texture_num(grid[i][j], bomb_count);

			opened_grid[i][j] = true;

			if (bomb_count == 0)
			{
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i - 1, j);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i - 1, j + 1);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i, j + 1);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i + 1, j + 1);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i + 1, j);
			}
			else
			{
				return;
			}
		}
		//furthest right side except corners
		else if (i == grid_w - 1 && j > 0 && j < grid_h - 1 &&  opened_grid[i][j] == false && bomb_grid[i][j] == 0 && flagged_grid[i][j] == 0)
		{
			int bomb_count = 0;
			
			if (bomb_grid[i][j - 1] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i - 1][j - 1] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i - 1][j] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i - 1][j + 1] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i][j + 1] == 1)
			{
				bomb_count++;
			}

			set_texture_num(grid[i][j], bomb_count);

			opened_grid[i][j] = true;

			if (bomb_count == 0)
			{
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i, j - 1);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i - 1, j - 1);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i - 1, j);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i - 1, j + 1);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i, j + 1);
			}
			else
			{
				return;
			}
		}
		else if (j == grid_h - 1 && i > 0 && i < grid_w - 1 &&  opened_grid[i][j] == false && bomb_grid[i][j] == 0 && flagged_grid[i][j] == 0)
		{
			int bomb_count = 0;
			cout << "ko";
			if (bomb_grid[i - 1][j] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i - 1][j - 1] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i][j - 1] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i + 1][j - 1] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i + 1][j] == 1)
			{
				bomb_count++;
			}

			set_texture_num(grid[i][j], bomb_count);

			opened_grid[i][j] = true;

			if (bomb_count == 0)
			{
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i - 1, j);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i - 1, j - 1);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i, j - 1);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i + 1, j - 1);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i + 1, j);
			}
			else
			{
				return;
			}
		}
		else if (i > 0 && i < grid_w - 1 && j > 0 && j < grid_w - 1 && opened_grid[i][j] == false && bomb_grid[i][j] == 0 && flagged_grid[i][j] == 0)
		{
			int bomb_count  = 0;

			if (bomb_grid[i - 1][j - 1] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i - 1][j] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i - 1][j + 1] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i][j - 1] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i][j + 1] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i + 1][j - 1] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i + 1][j] == 1)
			{
				bomb_count++;
			}

			if (bomb_grid[i + 1][j + 1] == 1)
			{
				bomb_count++;
			}

			set_texture_num(grid[i][j], bomb_count);

			opened_grid[i][j] = true;

			if (bomb_count == 0)
			{
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i - 1, j - 1);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i - 1, j);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i - 1, j + 1);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i, j - 1);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i, j + 1);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i + 1, j - 1);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i + 1, j);
				check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i + 1, j + 1);
			}
			else
			{
				return;
			}
		}
		return;
	}
	void game()
	{
		//main grid
		Sprite** grid;

		create_arr(grid, grid_w, grid_h);

		//for checking if user won
		int count = 0;

		//bomb grid
		int** bomb_grid;

		create_arr(bomb_grid, grid_w, grid_h);

		//flagged grid
		int** flagged_grid;

		create_arr(flagged_grid, grid_w, grid_h);

		//opened blocks grid
		bool** opened_grid;

		create_arr(opened_grid, grid_w, grid_h);

		//creating window
		RenderWindow game(VideoMode(VideoMode::getDesktopMode().width - 200, VideoMode::getDesktopMode().height - 100), "Minesweeper", Style::Close | Style::Titlebar);

		//configuring application icon
		Image icon;
		icon.loadFromFile("textures/icon.png");
		game.setIcon(900, 900, icon.getPixelsPtr());

		//stopwatch
		Font font_2;
		Text time_text;
		stringstream strm;
		Clock clock;
		
		

		font_2.loadFromFile("fonts/r.otf");

		time_text.setFont(font_2);
		time_text.setString("0");
		time_text.setCharacterSize(45);
		time_text.setFillColor(Color::Black);
		time_text.setPosition(47, 360);
		
		//shows count of flags
		Font font;
		Text flag_text;
		stringstream stream;

		stream << flag_count;

		font.loadFromFile("fonts/r.otf");

		flag_text.setFont(font);
		flag_text.setString(stream.str());
		flag_text.setCharacterSize(45);
		flag_text.setFillColor(Color::Black);
		flag_text.setPosition(45, 200);

		//configuring background
		Sprite game_bg;
		Texture bg;

		if (!bg.loadFromFile("textures/main_menu_bg.jpg"))
		{
			cout << "Can't open file";
		}
		game_bg.setTexture(bg);

		//loading textures

		if (!block.loadFromFile("textures/block.png") || !empty_block.loadFromFile("textures/empty.png")
			|| !flagged_block.loadFromFile("textures/flagged.png") || !mine.loadFromFile("textures/mine.png")
			|| !angry.loadFromFile("textures/angry.png") || !boss.loadFromFile("textures/boss.png")
			|| !happy.loadFromFile("textures/happy.png") || !worried.loadFromFile("textures/worried.png"))
		{
			cout << "Can't open all files";
		}

		//emoji
		Sprite emoji;
		Vector2f emoji_scale(75.0f, 75.0f);

		emoji.setTexture(happy);
		emoji.setScale(emoji_scale.x / emoji.getLocalBounds().width,
			emoji_scale.y / emoji.getLocalBounds().height);
		emoji.setPosition(40, 272);

		//back button
		Sprite back_button;
		Texture back_texture;
		Vector2f back_button_scale(75.0f, 75.0f);
		
		if (!back_texture.loadFromFile("textures/back.png"))
		{
			cout << "Can't open file";
		}
		back_button.setTexture(back_texture);
		back_button.setScale(back_button_scale.x / back_button.getLocalBounds().width,
			back_button_scale.y / back_button.getLocalBounds().height);
		back_button.setPosition(1075, 575);

		//configuring audio
		SoundBuffer buffer;
		Sound sound;

		if (!buffer.loadFromFile("music/music.ogv"))
		{
			cout << "Can't open file";
		}

		sound.setBuffer(buffer);
		sound.play();
		sound.setLoop(true);
		sound.setVolume(50.0f);
		sound.setPlayingOffset(milliseconds(music_offset));

		//settng texture to the grid
		for (int i = 0, k = grid_x; i < grid_w; i++ , k += padding)
		{
			for (int j = 0,  t = grid_y; j < grid_h; j++, t += padding)
			{
				grid[i][j].setTexture(block);
				grid[i][j].setScale(block_scale);
				grid[i][j].setPosition(k, t);

				//my code is reading block by columns not by rows because I put k , t not t , k
			}
		}

		//bringing window to live;
		while (game.isOpen())
		{
			Event evnt;

			//time
			if (game_over == 0 && first_move == true)
			{
				strm.str("");
				strm.clear();


				strm << int(clock.getElapsedTime().asSeconds());
				time_text.setString(strm.str());
			}
			

			while (game.pollEvent(evnt))
			{
				switch (evnt.type)
				{
					case Event::Closed:

						game.close();

						break;

					case Event::MouseButtonPressed:

						if (game_over == 0)
						{
							emoji.setTexture(worried);
						}
						

						//checks if back button clicked
						if (Mouse::isButtonPressed(Mouse::Left))
						{
							int x = Mouse::getPosition(game).x;
							int y = Mouse::getPosition(game).y;

							if (back_button.getPosition().x <= x + 1 && back_button.getPosition().x >= x - 100
								&& back_button.getPosition().y <= y + 1 && back_button.getPosition().y >= y - 170)
							{
								game.close();
								music_offset = sound.getPlayingOffset().asMilliseconds();
								sound.stop();
								first_move = false;
								choose_difficulty_window();
							}
						}

						//checks wheter any of block was pressed or button
						if (game_over == 0)
						{
							if (Mouse::isButtonPressed(Mouse::Left))
							{
								int x = Mouse::getPosition(game).x;
								int y = Mouse::getPosition(game).y;

								//checks if back button clicked
								

								//check if any block is clicked
								for (int i = 0; i < grid_w; i++)
								{
									for (int j = 0; j < grid_h; j++)
									{
										
										if (grid[i][j].getPosition().x <= x + 1 && grid[i][j].getPosition().x >= x - padding
											&& grid[i][j].getPosition().y <= y + 1 && grid[i][j].getPosition().y >= y - padding
											&& flagged_grid[i][j] == 0)
										{
											//initialazing every block as 0
											// 0 - empty ; 1 - mine
											//randomly putting mines
											//cout << "first move : " << int(first_move) << endl << endl;
											if (first_move == false)
											{
												srand(time(0));

												for (int e = 0; e < mine_count; e++)
												{
													int k = rand() % grid_w;
													int t = rand() % grid_h;

													if (bomb_grid[k][t] == 0 && k != i && t != j)
													{
														bomb_grid[k][t] = 1;
													}
													else
													{
														do
														{
															k = rand() % grid_w;
															t = rand() % grid_h;
														} while (bomb_grid[k][t] == 1 && k == i && t == j);

														bomb_grid[k][t] = 1;
													}

												}

												first_move = true;
											}

											if (first_move == true)
											{

											}

											//for debugging!! shows the position of mines
											/*for (int k = 0; k < grid_w; k++)
											{
												for (int t = 0; t < grid_h; t++)
												{
													if (bomb_grid[k][t] == 1)
													{
														cout << k << " " << t << endl;
													}
												}
											}*/
											
											//checks how many bombs are there round the block and changes its texture
											//cout << i << " " << j << endl;
											if (opened_grid[i][j] == false && bomb_grid[i][j] != 1 && bomb_grid[i][j] != 2)
											{
												check_bomb(grid, bomb_grid, opened_grid, flagged_grid, grid_h, grid_w, i, j);
												
											}
											else if (bomb_grid[i][j] == 1)
											{
												for (int k = 0; k < grid_w; k++)
												{
													for (int t = 0; t < grid_h; t++)
													{
														if (bomb_grid[k][t] == 1)
														{
															set_texture_num(grid[k][t], 9);
														}
													}
												}

												sound.stop();
												game_over = 1;
												emoji.setTexture(angry);
												game.draw(emoji);
											}


											break;
										}
									}
								}
							}
							//flag block
							else if (Mouse::isButtonPressed(Mouse::Middle))
							{
								int x = Mouse::getPosition(game).x;
								int y = Mouse::getPosition(game).y;

								for (int i = 0; i < grid_w; i++)
								{
									for (int j = 0; j < grid_h; j++)
									{
										if (grid[i][j].getPosition().x <= x + 1 && grid[i][j].getPosition().x >= x - padding
											&& grid[i][j].getPosition().y <= y + 1 && grid[i][j].getPosition().y >= y - padding && opened_grid[i][j] == false
											&& flagged_grid[i][j] == 0)
										{

											flagged_grid[i][j] = 2;//2 - flagged
											grid[i][j].setTexture(flagged_block);
											grid[i][j].setScale(block_scale);

											flag_count--;

											stream.str("");
											stream.clear();
											stream << flag_count;
											flag_text.setString(stream.str());
										}
									}
								}
							}
							//unflag block
							else if (Mouse::isButtonPressed(Mouse::Right))
							{
								int x = Mouse::getPosition(game).x;
								int y = Mouse::getPosition(game).y;

								for (int i = 0; i < grid_w; i++)
								{
									for (int j = 0; j < grid_h; j++)
									{
										if (grid[i][j].getPosition().x <= x + 1 && grid[i][j].getPosition().x >= x - padding
											&& grid[i][j].getPosition().y <= y + 1 && grid[i][j].getPosition().y >= y - padding && opened_grid[i][j] == false
											&& flagged_grid[i][j] != 0)
										{

											flagged_grid[i][j] = 0;
											grid[i][j].setTexture(block);
											grid[i][j].setScale(block_scale);

											flag_count++;

											stream.str("");
											stream.clear();
											stream << flag_count;
											flag_text.setString(stream.str());
										}
									}
								}
							}

							
						}
						
						
						break;

					case Event::MouseButtonReleased:

						if (game_over == 0)
						{
							emoji.setTexture(happy);
						}
						else if (game_over == 2)
						{
							emoji.setTexture(boss);
						}
						
						//checking if user won game
						count = 0;
						for (int i = 0; i < grid_w; i++)
						{
							for (int j = 0; j < grid_h; j++)
							{
								if (bomb_grid[i][j] == 1 && flagged_grid[i][j] == 2)
								{
									count++;
									cout << "count : " << count << endl << endl;
								}
							}
						}

						if (count == mine_count)
						{
							game_over = 2;
							emoji.setTexture(boss);
						}

						break;
				}
			}

			//drawing everything
			game.clear();
			
			game.draw(game_bg);
			game.draw(back_button);
			game.draw(flag_text);
			game.draw(emoji);
			game.draw(time_text);

			for (int i = 0; i < grid_w; i++)
			{
				for (int j = 0; j < grid_h; j++)
				{	
					game.draw(grid[i][j]);
				}
			}
	
			game.display();
		}

		
	}
}