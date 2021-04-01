#include "Player.h"

int Player::get_knowledge() const
{
	return knowledge;
}

int Player::get_attr_points() const
{
	return attribute_points;
}

vector<Item> Player::get_inventory() const
{
	return inventory;
}

Item* Player::get_equipped() const
{
}

Player::Player(string n, int l, vector<double> stats = { 0, 0, 0, 0, 0, 0, 0 }) : Entity(n, l, stats)
{
	equipped = new Item[4];
}