#include "Entity.h"

string Entity::get_name() const
{
	return name;
}

int Entity::get_level() const
{
	return level;
}

double Entity::get_health() const
{
	return health;
}

double Entity::get_strength() const
{
	return strength;
}

double Entity::get_dexterity() const
{
	return dexterity;
}

double Entity::get_evasion() const
{
	return evasion;
}

double Entity::get_fortitude() const
{
	return fortitude;
}

double Entity::get_leech() const
{
	return leech;
}

double Entity::get_base_damage() const
{
	return base_damage;
}

Entity::Entity(string n, int l, vector<double> stats)
{
	name = n;
	level = l;
	
	health = stats[0];
	strength = stats[1];
	dexterity = stats[2];
	evasion = stats[3];
	fortitude = stats[4];
	leech = stats[5];
	base_damage = stats[6];
}