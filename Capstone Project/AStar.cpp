#include <cstdlib>
#include <ctime>
#include <math.h>
#include <iostream>
#include "AStar.h"

node create_node(node* parent, vector<int> p)
{
	node temp;
	temp.parent = parent;
	temp.position = p;

	return temp;
}


void AStarPathfinding::init_map()
{
	map.reverse_backtrack_generate();
}

void AStarPathfinding::print_path_map() 
{
	vector<vector<char>> char_map = map.tree_to_map();
	for (int i = 0; i < fin_path.size(); i++)
	{
		char_map[fin_path[i][1]][fin_path[i][0]] = 'O';
	}
}

void AStarPathfinding::generate_end()
{
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> posGen(0, map.get_tree().size());

	int num = posGen(mt);
	endPos = { map.get_tree()[num].x, map.get_tree()[num].y };
}

void AStarPathfinding::generate_path() 
{
	node start_node = create_node(nullptr, startPos);
	node end_node = create_node(nullptr, endPos);

	vector<node*> to_visit = { &start_node };
	vector<node*> visited;
	int outer_iterations = 0;
	int max_iterations = 1000; // Make this dynamic

	vector<vector<int>> movements = { {1,0},{0,1},{-1,0},{0,-1} };
	while (!to_visit.empty())
	{
		outer_iterations++;

		node* current = to_visit[0];
		int cur_index = 0;
		for (int i = 0; i < to_visit.size(); i++)
		{
			if (to_visit[i]->f < current->f)
			{
				current = to_visit[i];
				cur_index = i;
			}
		}

		if (outer_iterations > max_iterations)
		{
			return;
		}

		to_visit.erase(to_visit.begin() + cur_index);
		visited.push_back(current);
		if (current->position == endPos)
		{
			vector<vector<int>> path;
			node* cur_path = current;
			while (cur_path->parent != nullptr)
			{
				path.push_back(cur_path->position);
				cur_path = current->parent;
			}

			fin_path = path;
			return;
		}

		vector<node*> children;

		for (int i = 0; i < movements.size(); i++)
		{
			vector<int> cur_pos = { current->position[0] + movements[i][0], current->position[1] + movements[i][1] };

			if (cur_pos[0] > map.tree_to_map()[0].size() - 1 || cur_pos[0] < 0 || cur_pos[1] > map.tree_to_map().size() - 1 || cur_pos[1] < 0) continue;
			if (map.tree_to_map()[cur_pos[1]][cur_pos[0]] != 'X') continue;

			node new_node = create_node(current, cur_pos);
			children.push_back(&new_node); // Figure out why pointer is not passing position field correctly
		}

		for (int i = 0; i < children.size(); i++)
		{
			for (int j = 0; j < visited.size(); j++)
			{
				if (children[i] == visited[i]) continue;
			}

			children[i]->g = current->g + 1;
			children[i]->h = pow((children[i]->position[0] - end_node.position[0]), 2) + pow((children[i]->position[1] - end_node.position[1]), 2);
			children[i]->f = children[i]->h + children[i]->g;

			cout << "DELETE ME 12345";
			//if len([i for i in to_visit if child == i and child.g > i.g]) > 0:
			//continue
			for (int j = 0; j < to_visit.size(); j++)
			{
				if (children[i] == to_visit[i] && children[i]->g > to_visit[i]->g) continue;
			}

			to_visit.push_back(children[i]);
		}
	}
}

Maze AStarPathfinding::get_map() const
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

AStarPathfinding::AStarPathfinding(Maze* m, vector<int> start, vector<int> end)
{
	if (m == nullptr)
	{
		init_map();
	}
	else
	{
		map = *m;
	}

	if (start[0] == -1)
	{
		startPos = map.get_start();
	}
	else
	{
		startPos = start;
	}

	if (end[0] == -1)
	{
		generate_end();
	}
	else
	{
		endPos = end;
	}
}
