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

	Player();
protected:
	double xp;

	int knowledge;
	int attribute_points;
	vector<Item> inventory;
	Item* equipped;

};