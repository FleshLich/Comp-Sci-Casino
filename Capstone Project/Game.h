#pragma once
#include <vector>
#include "Player.h"
#include "MazeGenerator.h"

class Game
{
public:
	void generate_map();

	// function convert maze char vector into vector of tile types
	Maze get_map() const;
	Player get_player() const;

	int get_depth() const;

	vector<double> get_global_mods() const;

	Game();
private:
	Maze map;
	Player player;

	int depth;

	vector<double> global_modifiers;
};