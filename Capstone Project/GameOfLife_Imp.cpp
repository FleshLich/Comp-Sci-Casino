#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define REDB "\e[41m"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>
#include <Windows.h>
#include "GameOfLife.h"
#include "String Utilities.h"

using namespace std;

void game_of_life::init_array()
{
	life_array = new int* [height];
	for (int i = 0; i < height; i++)
	{
		life_array[i] = new int[width];
		for (int j = 0; j < width; j++)
		{
			srand((unsigned)time(0) + rand());

			life_array[i][j] = rand() % 2;
		}
	}
}

void game_of_life::print_game()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < height; i++)
	{
		(i == 0) ? cout << "" : cout << "\n";
		for (int j = 0; j < width; j++)
		{
			SetConsoleTextAttribute(hConsole, 15);
			if (life_array[i][j] == 1)
			{
				SetConsoleTextAttribute(hConsole, 4 + 4 * 16);
				cout << "X";
			}
			else
			{
				cout << "0";
			}
		}
	}
	SetConsoleTextAttribute(hConsole, 15);
}

int game_of_life::get_num_neighbors(int x, int y)
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
				neighbours.push_back(next_y);
				neighbours.push_back(next_x);
			}
		}
	}
	return neighbours.size() / 2;
}

int** game_of_life::get_life_array() const
{
	return life_array;
}

int game_of_life::get_amount_simulated() const
{
	return generationsSimulated;
}

void game_of_life::simulate_generation()
{
	generationsSimulated++;
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
	for (int i = 0; i < to_kill.size(); i+= 2)
	{
		life_array[to_kill[i]][to_kill[i + 1]] = 0;
	}
	for (int j = 0; j < to_live.size(); j+= 2)
	{
		life_array[to_live[j]][to_live[j + 1]] = 1;
	}
}

void game_of_life::create_blank_template() 
{
	ofstream tempFile;
	tempFile.open("Blank Template.txt");

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			tempFile << "0 ";
		}
		if (i != height - 1) { tempFile << endl; }
	}
	tempFile.close();
}

void game_of_life::use_template(string file) 
{
	ifstream tempFile;
	tempFile.open(file);
	vector<string> file_vector = StringUtilities::split(StringUtilities::trim(StringUtilities::file_to_string(&tempFile)), "\n");
	for (int i = 0; i < height; i++)
	{
		vector<string> row = StringUtilities::split(file_vector[i], " ");
		for (int j = 0; j < width; j++)
		{
			life_array[i][j] = stoi(row[j]);
		}
	}
	tempFile.close();
}

game_of_life::game_of_life()
{
	init_array();
}