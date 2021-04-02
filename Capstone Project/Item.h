#pragma once
#include <string>
#include <vector>

using namespace std;

// types are 1-5 one being lowest(common) 5 being highest(enigma)
struct rarity_type
{
	int type;
};

// types can be: sword, bow, armor(helm, chest, legs), potion,
struct item_type
{
	string type;
};

class Item
{
public:
	string get_name() const;
	string get_desc() const;

	int get_knowledge_req() const;

	rarity_type get_rarity() const;
	item_type get_type() const;

	double get_health_mod() const;
	double get_strength_mod() const;
	double get_dex_mod() const;
	double get_evasion_mod() const;
	double get_fortitude_mod() const;
	double get_leech_mod() const;

	Item(string name = "", string desc = "", vector<double> modifier_vector = {0,0,0,0,0,0});

	static const rarity_type rarity_n;
	static const rarity_type rarity_un;
	static const rarity_type rarity_r;
	static const rarity_type rarity_l;
	static const rarity_type rarity_e;

	static const item_type sword;
	static const item_type bow;
	static const item_type helmet;
	static const item_type breastplate;
	static const item_type greaves;
	static const item_type potion_set;

	static const Item empty_item;
private:
	string name;
	string description;

	int knowledge_req;

	rarity_type rarity;
	item_type type;
	double health_mod;
	double strength_mod;
	double dex_mod;
	double evasion_mod;
	double fortitude_mod;
	double leech_mod;
};


