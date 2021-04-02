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

vector<Item> Player::get_equipped() const
{
	return equipped;
}

vector<int> Player::get_pos() const
{
	return cur_pos;
}

void Player::set_pos(vector<int> p)
{
	cur_pos = p;
}

Player::Player(string n, int l, vector<double> stats) : Entity(n, l, stats)
{
	equipped = {Item::empty_item, Item::empty_item, Item::empty_item, Item::empty_item};
}