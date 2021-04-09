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

void Player::add_to_inventory(Item i)
{
	inventory.push_back(i);
}

double Player::get_damage()
{
	return equipped[3].get_damage_mod() + (equipped[3].get_type() == Item::sword) ? get_strength() : get_dexterity();
}

vector<int> Player::get_pos() const
{
	return cur_pos;
}

void Player::set_pos(vector<int> p)
{
	cur_pos = p;
}

Player::Player(string n, int l, vector<double> stats, vector<double> mods) : Entity(n, l, stats, mods)
{
	equipped = {Item::empty_item, Item::empty_item, Item::empty_item, Item::empty_item};
}