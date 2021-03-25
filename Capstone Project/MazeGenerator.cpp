#include <cstdlib>
#include <ctime>
#include <string>
#include "MazeGenerator.h"

// Pseudo-Constructor for cell struct
cell create_cell(int x, int y, char visited_from = NULL, bool visited = false)
{
	cell temp;
	temp.x = x;
	temp.y = y;
	temp.visited = visited;
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

// https://weblog.jamisbuck.org/2011/1/24/maze-generation-hunt-and-kill-algorithm
void Maze::hunt_kill_generate()
{
	// walk phase
	srand((unsigned)time(0) + rand());
	int y = rand() % height + 1;
	srand((unsigned)time(0) + rand());
	int x = rand() % width + 1;
	
	int i = 0;
	cell *current = get_cell_by_pos(x, y);
	current->visited = true;
	while (i < 10) //has_unvisited_neigbors(current)
	{
		i++;
		// Add direction overflow handler
		// 1 = North, 2 = East, 3 = South, 4 = West
		srand((unsigned)time(0) + rand());
		int dir = rand() % 4 + 1;
		
		switch (dir)
		{
		case 1:
			current = get_cell_by_pos(current->x, current->y - 1);
			current->visited_from = 'n';
			break;
		case 2:
			current = get_cell_by_pos(current->x + 1, current->y);
			current->visited_from = 'e';
			break;
		case 3:
			current = get_cell_by_pos(current->x, current->y + 1);
			current->visited_from = 's';
			break;
		case 4:
			current = get_cell_by_pos(current->x - 1, current->y);
			current->visited_from = 'w';
			break;
		default:
			break;
		}
		current->visited = true;
	}
}

vector<vector<char>> Maze::tree_to_map()
{
	vector<vector<char>> map;
	return map;
}

bool Maze::has_visited_neighbors(cell c)
{
	vector<cell> neighbors = get_neighbors(c);
	for (int i = 0; i < neighbors.size(); i++)
	{
		if (neighbors[i].visited)
		{
			return true;
		}
	}
	return false;
}

bool Maze::has_unvisited_neigbors(cell c)
{
	vector<cell> neighbors = get_neighbors(c);
	for (int i = 0; i < neighbors.size(); i++)
	{
		if (!neighbors[i].visited)
		{
			return true;
		}
	}
	return false;
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
	//throw string("No cell with that position");
}

vector<cell> Maze::get_neighbors(cell c)
{
	vector<cell> neighbors;
	for (int i = 0; i < tree.size(); i++)
	{
		if ((tree[i].x == c.x + 1 || tree[i].x == c.x - 1) && tree[i].y == c.y)
		{
			neighbors.push_back(tree[i]);
		}
		else if ((tree[i].y == c.y + 1 || tree[i].y == c.y - 1) && tree[i].x == c.x)
		{
			neighbors.push_back(tree[i]);
		}
	}
	return neighbors;
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

Maze::Maze(int w, int h)
{
	width = w;
	height = h;

	init_tree();
}