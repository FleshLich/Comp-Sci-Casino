#include <iostream>
#include "Item.h"

using namespace std;

bool rarity_type::operator==(rarity_type a)
{
	return this->type == a.type;
}

ostream& operator<<(ostream& output, const rarity_type& i)
{
	output << i.type;
	return output;
}

bool item_type::operator==(item_type a)
{
	return this->type == a.type;
}

ostream& operator<<(ostream& output, const item_type& i)
{
	output << i.type;
	return output;
}

int Item::global_id_space = 0;

const rarity_type Item::rarity_n{ 1 };
const rarity_type Item::rarity_un{ 2 };
const rarity_type Item::rarity_r{ 3 };
const rarity_type Item::rarity_l{ 4 };
const rarity_type Item::rarity_e{ 5 };
const rarity_type Item::rarity_rand{ -1 };

const item_type Item::sword{ "sword" };
const item_type Item::bow{ "bow" };
const item_type Item::helmet{ "helmet" };
const item_type Item::breastplate{ "breastplate" };
const item_type Item::greaves{ "greaves" };
const item_type Item::potion_set{ "potion set" };
const item_type Item::rand_type{ "rand" };

const vector<item_type> Item::all_types = { Item::sword, Item::bow, Item::helmet, Item::breastplate, Item::greaves, Item::potion_set };

const Item Item::empty_item;

int Item::get_id() const
{
	return id;
}

string Item::get_name() const
{
	return name;
}

string Item::get_desc() const
{
	return description;
}

int Item::get_knowledge_req() const
{
	return knowledge_req;
}

rarity_type Item::get_rarity() const
{
	return rarity;
}

item_type Item::get_type() const
{
	return type;
}

vector<double> Item::get_mods() const
{
	return { health_mod, strength_mod, dex_mod, evasion_mod, fortitude_mod, leech_mod, damage_mod };
}

double Item::get_health_mod() const
{
	return health_mod;
}

double Item::get_strength_mod() const
{
	return strength_mod;
}

double Item::get_dex_mod() const
{
	return dex_mod;
}

double Item::get_evasion_mod() const
{
	return evasion_mod;
}

double Item::get_fortitude_mod() const
{
	return fortitude_mod;
}

double Item::get_leech_mod() const
{
	return leech_mod;
}

double Item::get_damage_mod() const
{
	return damage_mod;
}

void Item::set_rarity(rarity_type r)
{
	rarity = r;
}

void Item::set_type(item_type t)
{
	type = t;
}

void Item::set_knowledge_req(int i)
{
	knowledge_req = i;
}

bool Item::operator==(Item i)
{
	return this->id == i.get_id();
}

Item::Item(string n, string d, item_type i_type, rarity_type r_type, int k_req, vector<double> mv)
{
	id = Item::global_id_space;
	Item::global_id_space++;

	name = n;
	description = d;

	type = i_type;
	rarity = r_type;
	knowledge_req = k_req;

	health_mod = mv[0];
	strength_mod = mv[1];
	dex_mod = mv[2];
	evasion_mod = mv[3];
	fortitude_mod = mv[4];
	leech_mod = mv[5];
	damage_mod = mv[6];

	if (i_type.type == "sword" || i_type.type == "bow") equip_slot = 3;
	else if (i_type.type == "breastplate" || i_type.type == "potion set") equip_slot = 1;
	else if (i_type.type == "greaves") equip_slot = 2;
	else if (i_type.type == "helmet") equip_slot = 0;
}

string Item::rarity_to_string(rarity_type r)
{
	switch (r.type)
	{
	case 1:
		return "Common";
		break;
	case 2:
		return "Uncommon";
		break;
	case 3:
		return "Rare";
		break;
	case 4:
		return "Legendary";
		break;
	case 5:
		return "Enigmatic";
		break;
	default:
		break;
	}
}