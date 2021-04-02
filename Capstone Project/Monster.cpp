#include "Monster.h"

double Monster::get_drop_chance()
{
	return -1;
}

vector<drop> Monster::get_drop_table() const
{
	return drop_table;
}

vector<double> Monster::get_level_mods() const
{
	return level_mods;
}

Monster::Monster(string n, int l, vector<double> stats): Entity(n ,l, stats)
{
}