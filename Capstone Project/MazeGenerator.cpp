#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <random>
#include <Windows.h>
#include "MazeGenerator.h"

// Pseudo-Constructor for cell struct
cell create_cell(int x, int y, vector<cell*> c_to = {}, bool visited = false)
{
	cell temp;
	temp.x = x;
	temp.y = y;
	temp.visited = visited;
	temp.connected_to = c_to;
	return temp;
}

void Maze::init_tree()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			cell temp = create_cell(x, y);
			tree.push_back(temp);
		}
	}
}

void Maze::print_map()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	vector<vector<char>> map = tree_to_map();
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			if (map[i][j] == '#')
			{
				SetConsoleTextAttribute(hConsole, 15);
			}
			else
			{
				SetConsoleTextAttribute(hConsole, 4 + 4 * 16);
			}
			cout << map[i][j];
		}
		SetConsoleTextAttribute(hConsole, 15);
		cout << "\n";
	}
}

void Maze::reverse_backtrack_generate()
{

	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> heightGen(0, height - 1);
	uniform_int_distribution<int> widthGen(0, width - 1);
	
	int y = heightGen(mt);
	int x = widthGen(mt);
	startPos = { x, y };
	
	vector<cell*> track;
	cell *current = get_cell_by_pos(x, y);
	do
	{
		vector<cell*> neighbors = get_unvisited_neigbors(*current);
		uniform_int_distribution<int>neighborGen(0, (neighbors.empty()) ? 1 : neighbors.size() - 1);

		if (neighbors.empty())
		{
			current->visited = true;
			current = track[track.size() - 1];
			track.pop_back();
		}
		else 
		{
			track.push_back(current);
			int num = neighborGen(mt);

			cell* selected = neighbors[num];
			current->visited = true;
			current->connected_to.push_back(selected);
			current = selected;
		}
		continue;
	} while (!track.empty());
	
}

vector<vector<char>> Maze::tree_to_map()
{
	vector<vector<char>> map((height * 2) - 1);
	cell cur_cell;
	for (int y = 0; y < (height * 2) - 1; y++)
	{
		for (int x = 0; x < (width * 2) - 1; x++)
		{
			if (y % 2 != 0)
			{
				if (x % 2 == 0)
				{
					if (are_cells_connected(get_cell_by_pos(x / 2, (y - 1) / 2), get_cell_by_pos(x / 2, (y + 1) / 2)))
					{
						map[y].push_back('X');
					}
					else
					{
						map[y].push_back('#');
					}
				}
				else
				{
					map[y].push_back('#');
				}
			}
			else
			{
				if (x % 2 == 0)
				{
					//cur_cell = *get_cell_by_pos(x / 2, y);
					map[y].push_back('X');
				}
				else
				{
					if (are_cells_connected(get_cell_by_pos((x - 1) / 2, y / 2), get_cell_by_pos((x + 1) / 2, y / 2)))
					{
						map[y].push_back('X');
					}
					else
					{
						map[y].push_back('#');
					}
				}
			}
		}
	}
	return map;
}

bool Maze::has_visited_neighbors(cell c)
{
	vector<cell*> neighbors = get_neighbors(c);
	for (int i = 0; i < neighbors.size(); i++)
	{
		if (neighbors[i]->visited)
		{
			return true;
		}
	}
	return false;
}

bool Maze::has_unvisited_neighbors(cell c)
{
	vector<cell*> neighbors = get_neighbors(c);
	for (int i = 0; i < neighbors.size(); i++)
	{
		if (!neighbors[i]->visited)
		{
			return true;
		}
	}
	return false;
}

bool Maze::are_cells_connected(cell* c, cell* c2)
{
	for (int i = 0; i < c->connected_to.size(); i++)
	{
		if (c2 == c->connected_to[i]) return true;
	}
	for (int i = 0; i < c2->connected_to.size(); i++)
	{
		if (c == c2->connected_to[i]) return true;
	}
	return false;
}

bool Maze::is_complete()
{
	for (int i = 0; i < tree.size(); i++)
	{
		if (has_unvisited_neighbors(tree[i]))
		{
			return false;
		}
	}
	return true;
}

cell* Maze::get_cell_by_pos(int x, int y)
{
	for (int i = 0; i < tree.size(); i++)
	{
		if (tree[i].x == x && tree[i].y == y)
		{
			return &tree[i];
		}
	}
	throw string("No cell with that position");
}

vector<cell*> Maze::get_neighbors(cell c)
{
	vector<cell*> neighbors;
	for (int i = 0; i < tree.size(); i++)
	{
		if ((tree[i].x == c.x + 1 || tree[i].x == c.x - 1) && tree[i].y == c.y)
		{
			neighbors.push_back(&tree[i]);
		}
		else if ((tree[i].y == c.y + 1 || tree[i].y == c.y - 1) && tree[i].x == c.x)
		{
			neighbors.push_back(&tree[i]);
		}
	}
	return neighbors;
}

vector<cell*> Maze::get_unvisited_neigbors(cell c)
{
	vector<cell*> neighbors = get_neighbors(c);
	vector<cell*> unvisited;
	for(int i = 0; i < neighbors.size(); i++)
	{
		if (!neighbors[i]->visited)
		{
			unvisited.push_back(neighbors[i]);
		}
	}
	return unvisited;
}

vector<cell> Maze::get_tree() const
{
	return tree;
}

int Maze::get_width() const
{
	return width;
}

int Maze::get_height() const
{
	return height;
}

vector<int> Maze::get_start() const
{
	return startPos;
}

Maze::Maze(int w, int h)
{
	width = w;
	height = h;

	init_tree();
}