#include <cstdlib>
#include <ctime>
#include "AStar.h"

struct Node
{
	Node* parent = nullptr;
	vector<int> position;

	int g;
	int h;
	int f;
};

struct Cell
{
	bool visited = false;
	int x, y;
};

// Pseudo-Constructor for node struct
Node create_node(Node* parent = nullptr, vector<int> position = { 0, 0 })
{
	Node temp;
	temp.parent = parent;
	temp.position = position;
	return temp;
}

void AStarPathfinding::init_map()
{
	int width = 20;
	int height = 15;

	for (int y = 0; y < height; y++)
	{
		vector<char> row;
		for (int x = 0; x < width; x++)
		{
			row.push_back('#');

		}
		map.push_back(row);
	}
}

void AStarPathfinding::generate_maze()
{
	vector<vector<int>> stack_path;
	stack_path.push_back(startPos);

	while (!stack_path.empty())
	{
		vector<int> cell = stack_path[stack_path.size() - 1];
		vector<vector<int>> neighbors;
		int x = stack_path[stack_path.size() - 1][0];
		int y = stack_path[stack_path.size() - 1][1];

		if (y > 0) neighbors.push_back({ x, y - 1 });
		if (y < map.size() - 1) neighbors.push_back({x, y + 1});
		if (x > 0) neighbors.push_back({ x - 1, y });
		if (x < map[0].size() - 1) neighbors.push_back({ x + 1, y });

		if (!neighbors.empty())
		{
			srand((unsigned)time(0) + rand());
			int cell = rand() % neighbors.size();

			for (int i = 0; i < neighbors.size(); i++)
			{
				map[y][x] = 'X';

				if (i != cell) stack_path.push_back(neighbors[i]);
			}
			stack_path.push_back(neighbors[cell]);
		}
	}
}

void AStarPathfinding::generate_path() 
{
}

vector<vector<char>> AStarPathfinding::get_map() const
{
	return map;
}

vector<int> AStarPathfinding::get_start() const
{
	return startPos;
}

vector<int> AStarPathfinding::get_end() const
{
	return endPos;
}

string AStarPathfinding::get_map_string() const
{
	string temp = "";
	for (int y = 0; y < map.size(); y++)
	{
		for (int x = 0; x < map[y].size(); x++)
		{
			temp += map[y][x];
		}
		temp += "\n";
	}
	return temp;
}

AStarPathfinding::AStarPathfinding() 
{
	init_map();
	generate_maze();

	startPos = { 0, 0 };
}
