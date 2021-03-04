#include <iostream>
#include <cstdlib>
#include <ctime>
#include "GameOfLife.h"

using namespace std;

int** game_of_life::get_life_array() const
{
	return life_array;
}

void game_of_life::init_array()
{
	life_array = new int* [10];
	for (int i = 0; i < 10; i++)
	{
		life_array[i] = new int[10];
		for (int j = 0; j < 10; j++)
		{
			srand((unsigned)time(0) + rand());

			life_array[i][j] = rand() % 2;
		}
	}
}

game_of_life::game_of_life()
{
	init_array();
}