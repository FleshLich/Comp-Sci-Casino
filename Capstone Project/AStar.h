#pragma once
#include <vector>
#include <string>
#include "MazeGenerator.h"

using namespace std;

class AStarPathfinding
{
public:
	void init_map();

	void generate_path();

	Maze get_map() const;

	vector<int> get_start() const;

	vector<int> get_end() const;

	AStarPathfinding();
private:
	Maze map;
	vector<int> startPos;
	vector<int> endPos;
};