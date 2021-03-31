#pragma once
#include "Entity.h"

class Monster : Entity
{
public:
	double* get_drop_chance() const;

	vector<double> get_level_mods() const;

	Monster();
private:
	// % for normal, % for uncommon, % for rare, % for legendary, % for enigma
	double rarity_drop_chance[5] = { 50, 0, 0, 0, 0};

	//drop table

	vector<double> level_mods;
};