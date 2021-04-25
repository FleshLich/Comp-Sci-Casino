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
	return health + (get_health_mod() * 5);
}

double Entity::get_strength() const
{
	return strength + get_strength_mod();
}

double Entity::get_dexterity() const
{
	return dexterity + get_dexterity_mod();
}

double Entity::get_evasion() const
{
	return evasion + get_evasion_mod();
}

double Entity::get_fortitude() const
{
	return fortitude + get_fortitude_mod();
}

double Entity::get_leech() const
{
	return leech + get_leech_mod();
}

double Entity::get_base_damage() const
{
	return base_damage + get_base_damage_mod();
}

double Entity::get_health_mod() const
{
	return health_mod;
}

double Entity::get_strength_mod() const
{
	return strength_mod;
}

double Entity::get_dexterity_mod() const
{
	return dex_mod;
}

double Entity::get_evasion_mod() const
{
	return evasion_mod;
}

double Entity::get_fortitude_mod() const
{
	return fortitude_mod;
}

double Entity::get_leech_mod() const
{
	return leech_mod;
}

double Entity::get_base_damage_mod() const
{
	return base_damage_mod;
}

double Entity::get_damage() const
{
	return get_base_damage() + get_strength() + get_dexterity();
}

void Entity::set_level(int l)
{
	level = l;
}

void Entity::set_stats(vector<double> v)
{
	health = v[0];
	strength = v[1];
	dexterity = v[2];
	evasion = v[3];
	fortitude = v[4];
	leech = v[5];
	base_damage = v[6];
}

void Entity::set_health(double h)
{
	health = h;
}

void Entity::set_strength(double i)
{
	strength = i;
}

void Entity::set_dexterity(double i)
{
	dexterity = i;
}

void Entity::set_evasion(double i)
{
	evasion = i;
}

void Entity::set_fortitude(double i)
{
	fortitude = i;
}

void Entity::set_leech(double i)
{
	leech = i;
}

void Entity::set_base_damage(double i)
{
	base_damage = i;
}

void Entity::set_mods(vector<double> mv)
{
	health_mod = mv[0];
	strength_mod = mv[1];
	dex_mod = mv[2];
	evasion_mod = mv[3];
	fortitude_mod = mv[4];
	leech_mod = mv[5];
	base_damage_mod = mv[6];
}

void Entity::set_health_mod(double h)
{
	health_mod = h;
}

void Entity::set_strength_mod(double s)
{
	strength_mod = s;
}

void Entity::set_dexterity_mod(double d)
{
	dex_mod = d;
}

void Entity::set_evasion_mod(double e)
{
	evasion = e;
}

void Entity::set_fortitude_mod(double f)
{
	fortitude = f;
}

void Entity::set_leech_mod(double l)
{
	leech_mod = l;
}

void Entity::set_base_damage_mod(double bd)
{
	base_damage_mod = bd;
}

void Entity::do_damage(double d)
{
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> chanceGen(0, 100);

	if (chanceGen(mt) < evasion)
	{
		entity_event_stack.push_back(name + " dodged the attack!");
		return;
	}
	if (fortitude > 0) entity_event_stack.push_back(name + "'s strong body prevented " + to_string((d * (fortitude * 0.01))) + " points of damage");
	health -= (d - (d * (fortitude * 0.01)));
	if (health < 1) health = 0;
}

Entity::Entity(string n, int l, vector<double> stats, vector<double> mods)
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

	health_mod = mods[0];
	strength_mod = mods[1];
	dex_mod = mods[2];
	evasion_mod = mods[3];
	fortitude_mod = mods[4];
	leech_mod = mods[5];
	base_damage_mod = mods[6];
}