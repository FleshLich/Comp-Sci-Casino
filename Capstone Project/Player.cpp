#include "Player.h"

double Player::get_xp() const
{
	return xp;
}

double Player::get_max_xp() const
{
	return max_xp;
}

double Player::get_damage()
{
	return equipped[3].get_damage_mod() + (equipped[3].get_type() == Item::sword) ? get_strength() : get_dexterity();
}

int Player::get_knowledge() const
{
	return knowledge;
}

int Player::get_attr_points() const
{
	return attribute_points;
}

int Player::get_points_per_level() const
{
	return points_per_level;
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

void Player::set_xp(double x)
{
	xp = x;
}

void Player::set_max_xp(double x)
{
	max_xp = x;
}

void Player::set_knowledge(int k)
{
	knowledge = k;
}

void Player::set_attr_points(int i)
{
	attribute_points = i;
}

void Player::set_pos(vector<int> p)
{
	cur_pos = p;
}

void Player::add_stats(vector<double> v)
{
	health += v[0];
	strength += v[1];
	dexterity += v[2];
	evasion += v[3];
	fortitude += v[4];
	leech += v[5];
	knowledge += int(v[6]);
}

void Player::add_to_inventory(Item i)
{
	inventory.push_back(i);
}

Player::Player(string n, int l, vector<double> stats, vector<double> mods) : Entity(n, l, stats, mods)
{
	equipped = {Item::empty_item, Item::empty_item, Item::empty_item, Item::empty_item};
}