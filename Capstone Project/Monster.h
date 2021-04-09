#pragma once
#include "Entity.h"
#include "Item.h"

struct drop
{
	Item* to_drop;
	double chance;
};

class Monster : public Entity
{
public:
	double get_drop_chance();

	vector<drop> get_drop_table() const;

	vector<double> get_level_mods() const;

	void add_to_drops(drop);

	Monster(string n = "", int l = 0, vector<double> stats = { 0, 0, 0, 0, 0, 0, 0 }, vector<double> mods = { 0,0,0,0,0,0,0 }, vector<double> chance_vector = { 50, 0, 0, 0, 0 });
private:
	// % for normal, % for uncommon, % for rare, % for legendary, % for enigma -- Do I need this if I am attaching drop chance to drop struct?
	vector<double> rarity_drop_chance;

	vector<drop> drop_table;

	vector<double> level_mods;
};