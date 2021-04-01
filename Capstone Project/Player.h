#pragma once
#include "Entity.h"
#include "Item.h"

class Player : Entity
{
public:
	int get_knowledge() const;
	int get_attr_points() const;

	vector<Item> get_inventory() const;
	Item* get_equipped() const;

	Player(string n, int l, vector<double> stats = { 0, 0, 0, 0, 0, 0, 0 });
protected:
	double xp;

	int knowledge;
	int attribute_points;
	vector<Item> inventory;
	Item* equipped;

};