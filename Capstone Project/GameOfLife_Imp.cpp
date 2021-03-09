#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "GameOfLife.h"

using namespace std;

void game_of_life::init_array()
{
	life_array = new int* [width];
	for (int i = 0; i < height; i++)
	{
		life_array[i] = new int[height];
		for (int j = 0; j < width; j++)
		{
			srand((unsigned)time(0) + rand());

			//life_array[i][j] = rand() % 2;
			life_array[i][j] = 0;
			if (i == 3)
			{
				if (j == 7 || j == 8)
				{
					life_array[i][j] = 1;
				}
			}
			if (i == 4)
			{
				if (j == 6 || j == 7)
				{
					life_array[i][j] = 1;
				}
			}
			if (i == 5)
			{
				if (j == 7)
				{
					life_array[i][j] = 1;
				}
			}
		}
	}
}

void game_of_life::print_game()
{
	for (int i = 0; i < height; i++)
	{
		(i == 0) ? cout << "" : cout << "\n";
		for (int j = 0; j < width; j++)
		{
			(life_array[i][j] == 1) ? cout << "X " : cout << "0 ";
		}
	}
}

int game_of_life::get_num_neighbors(int y, int x)
{
	vector<int> neighbours;
	int next_y;
	for (int i = -1; i < 2; i++)
	{
		int next_y = y + i;
		if (next_y < 0)
		{
			next_y = height - 1;
		}
		else if (next_y > height - 1)
		{
			next_y = 0;
		}
		for (int j = -1; j < 2; j++)
		{
			int next_x = x + j;
			if (next_x < 0)
			{
				next_x = width - 1;
			}
			else if (next_x > width - 1)
			{
				next_x = 0;
			}
			
			// If checking self
			if (i == 0 && j == 0)
			{
				continue;
			}
			if (life_array[next_y][next_x] == 1)
			{
				neighbours.push_back(next_x);
				neighbours.push_back(next_y);
			}
		}
	}
	return neighbours.size() / 2;
}

int** game_of_life::get_life_array() const
{
	return life_array;
}

void game_of_life::simulate_generation()
{
	vector<int> to_kill;
	vector<int> to_live;
	for (int i = 0; i < height; i++)
	{

		for (int j = 0; j < width; j++)
		{
			int neighbours = get_num_neighbors(j, i);

			if (life_array[i][j] == 0)
			{
				if (neighbours == 3) { to_live.push_back(i); to_live.push_back(j); }
			}

			if (life_array[i][j] == 1)
			{
				if (neighbours == 2 || neighbours == 3)
				{
					continue;
				}
				else
				{
					to_kill.push_back(i); to_kill.push_back(j);
				}
			}
		}
	}
	for (int i = 0; i <= to_kill.size() / 2; i += 2)
	{
		life_array[to_kill[i]][to_kill[i + 1]] = 0;
	}
	for (int i = 0; i <= to_live.size() / 2; i += 2)
	{
		life_array[to_live[i]][to_live[i + 1]] = 1;
	}
}

game_of_life::game_of_life()
{
	init_array();
}