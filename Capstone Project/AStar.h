#pragma once
#include <vector>
#include <string>
#include <random>
#include "MazeGenerator.h"

using namespace std;

struct node
{
	node* parent;
	vector<int> position;

	double g = 0;
	double h = 0;
	double f = 0;
};

class AStarPathfinding
{
public:
	void init_map();

	void print_path_map();

	void generate_end();

	void generate_path();

	Maze get_map() const;

	vector<int> get_start() const;

	vector<int> get_end() const;

	AStarPathfinding(Maze* m = nullptr, vector<int> sPos = { -1, -1 }, vector<int> ePos = { -1, -1 });
private:
	Maze map;
	vector<int> startPos;
	vector<int> endPos;

	vector<vector<int>> fin_path;
};