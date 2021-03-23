#pragma once
#include <vector>

using namespace std;

class AStarPathfinding
{
public:
	void generate_map();

	void generate_path();

	vector<vector<char>> get_map() const;

	vector<int> get_start() const;

	vector<int> get_end() const;

	AStarPathfinding();
private:
	vector<vector<char>> map;
	vector<int> startPos;
	vector<int> endPos;
};