#pragma once
#include <vector>
#include <string>

using namespace std;

class AStarPathfinding
{
public:
	void init_map();

	void generate_maze();

	void generate_path();

	vector<vector<char>> get_map() const;

	vector<int> get_start() const;

	vector<int> get_end() const;

	string get_map_string() const;

	AStarPathfinding();
private:
	vector<vector<char>> map;
	vector<int> startPos;
	vector<int> endPos;
};