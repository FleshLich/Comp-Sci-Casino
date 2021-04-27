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
	if (equipped[3] == Item::empty_item)
	{
		return 1;
	}
	return equipped[3].get_damage_mod() + ((equipped[3].get_type() == Item::sword) ? get_strength() : get_dexterity());
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

double Player::get_health()
{
	if (health > get_max_health())
	{
		health = get_max_health();
	}
	return health;
}

double Player::get_max_health() const
{
	return max_health + (get_health_mod() * 5);
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

void Player::set_equipped(Item it, int i)
{
	health_mod -= equipped[i].get_health_mod();
	strength_mod -= equipped[i].get_strength_mod();
	dex_mod -= equipped[i].get_dex_mod();
	evasion_mod -= equipped[i].get_evasion_mod();
	fortitude_mod -= equipped[i].get_fortitude_mod();
	leech_mod -= equipped[i].get_leech_mod();

	health_mod += it.get_health_mod();
	strength_mod += it.get_strength_mod();
	dex_mod += it.get_dex_mod();
	evasion_mod += it.get_evasion_mod();
	fortitude_mod += it.get_fortitude_mod();
	leech_mod += it.get_leech_mod();

	equipped[i] = it;
}

void Player::set_pos(vector<int> p)
{
	cur_pos = p;
}

void Player::add_stats(vector<double> v)
{
	max_health += v[0];
	health += v[0] * 5;
	strength += v[1];
	dexterity += v[2];
	evasion += v[3];
	fortitude += v[4];
	leech += v[5];
	knowledge += int(v[6]);
}

void Player::add_to_inventory(Item i)
{
	if (i.get_id() == 0) return;
	inventory.push_back(i);
}

void Player::remove_from_inventory(Item it)
{
	for (int i = 0; i < inventory.size(); i++)
	{
		if (it == inventory[i])
		{
			inventory.erase(inventory.begin() + i);
			return;
		}
	}
}

Player::Player(string n, int l, vector<double> stats, vector<double> mods) : Entity(n, l, stats, mods)
{
	max_health = stats[0];
	equipped = {Item::empty_item, Item::empty_item, Item::empty_item, Item::empty_item};
}