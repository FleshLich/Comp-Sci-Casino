#include <cstdlib>
#include <ctime>
#include "AStar.h"


void AStarPathfinding::init_map()
{
	Maze cur_map;
}

void AStarPathfinding::generate_path() 
{
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

AStarPathfinding::AStarPathfinding() 
{
	init_map();

	startPos = { 0, 0 };
}
