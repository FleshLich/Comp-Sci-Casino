#pragma once
#include "Entity.h"
#include "Item.h"

struct drop
{
	Item to_drop;
	double chance;
};

class Monster : Entity
{
public:
	double get_drop_chance();

	vector<drop> get_drop_table() const;

	vector<double> get_level_mods() const;

	Monster(string n = "", int l = 0, vector<double> stats = { 0, 0, 0, 0, 0, 0, 0 });
private:
	// % for normal, % for uncommon, % for rare, % for legendary, % for enigma
	double rarity_drop_chance[5] = { 50, 0, 0, 0, 0};

	vector<drop> drop_table;

	vector<double> level_mods;
};