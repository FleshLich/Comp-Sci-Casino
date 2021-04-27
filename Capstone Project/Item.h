#pragma once
#include <string>
#include <vector>

using namespace std;

// types are 1-5 one being lowest(common) 5 being highest(enigma), -1 = random
struct rarity_type
{
	int type;

	bool operator==(rarity_type);

	friend ostream& operator<<(ostream&, const rarity_type&);
};

// types can be: sword, bow, armor(helm, chest, legs), potion,
struct item_type
{
	string type;

	bool operator==(item_type);

	friend ostream& operator<<(ostream&, const item_type&);
};

class Item
{
public:
	int get_id() const;

	string get_name() const;
	string get_desc() const;

	int get_knowledge_req() const;

	rarity_type get_rarity() const;
	item_type get_type() const;

	vector<double> get_mods() const;
	double get_health_mod() const;
	double get_strength_mod() const;
	double get_dex_mod() const;
	double get_evasion_mod() const;
	double get_fortitude_mod() const;
	double get_leech_mod() const;
	double get_damage_mod() const;

	void set_rarity(rarity_type);
	void set_type(item_type);
	void set_knowledge_req(int);

	bool operator==(Item);

	int equip_slot;

	Item(string name = "", string desc = "", item_type type = Item::rand_type, rarity_type r_type = Item::rarity_rand, int knowledge_req = -1, vector<double> modifier_vector = {0,0,0,0,0,0,0});

	// converts rarity type to string 
	static string rarity_to_string(rarity_type);

	static int global_id_space;

	static const rarity_type rarity_n;
	static const rarity_type rarity_un;
	static const rarity_type rarity_r;
	static const rarity_type rarity_l;
	static const rarity_type rarity_e;
	static const rarity_type rarity_rand;

	static const item_type sword;
	static const item_type bow;
	static const item_type helmet;
	static const item_type breastplate;
	static const item_type greaves;
	static const item_type potion_set;
	static const item_type rand_type;

	static const vector<item_type> all_types;

	static const Item empty_item;
private:
	int id;
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
	double damage_mod;
};


