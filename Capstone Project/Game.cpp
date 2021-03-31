#include "Game.h"

void Game::generate_map()
{
	map.reverse_backtrack_generate();

	// Do tile stuff
}

Maze Game::get_map() const
{
	return map;
}

Player Game::get_player() const
{
	return player;
}

int Game::get_depth() const
{
	return depth;
}

vector<double> Game::get_global_mods() const
{
	return global_modifiers;
}