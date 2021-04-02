#pragma once
#include "Entity.h"
#include "Item.h"

class Player : Entity
{
public:
	int get_knowledge() const;
	int get_attr_points() const;

	vector<Item> get_inventory() const;
	vector<Item> get_equipped() const;

	vector<int> get_pos() const;

	void set_pos(vector<int>);

	Player(string n = "Player", int l = 1, vector<double> stats = { 0, 0, 0, 0, 0, 0, 0 });
protected:
	double xp = 0;

	int knowledge = 1;
	int attribute_points = 5;
	vector<Item> inventory;
	// vector should be: helm, chest, legs, weapon
	vector<Item> equipped;

	vector<int> cur_pos;
};