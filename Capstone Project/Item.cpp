#include "Item.h"

const rarity_type Item::rarity_n{ 1 };
const rarity_type Item::rarity_un{ 2 };
const rarity_type Item::rarity_r{ 3 };
const rarity_type Item::rarity_l{ 4 };
const rarity_type Item::rarity_e{ 5 };

const item_type Item::sword{ "sword" };
const item_type Item::bow{ "bow" };
const item_type Item::helmet{ "helmet" };
const item_type Item::breastplate{ "breastplate" };
const item_type Item::greaves{ "greaves" };
const item_type Item::potion_set{ "potion set" };

const Item Item::empty_item;

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

Item::Item(string name, string desc, vector<double> modifier_vector)
{

}