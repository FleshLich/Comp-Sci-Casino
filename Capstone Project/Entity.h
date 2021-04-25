#pragma once
#include <string>
#include <vector>
#include <random>

using namespace std;

class Entity
{
public:
	string get_name() const;

	int get_level() const;

	double get_health() const;
	double get_strength() const;
	double get_dexterity() const;
	double get_evasion() const;
	double get_fortitude() const;
	double get_leech() const;
	double get_base_damage() const;

	double get_health_mod() const;
	double get_strength_mod() const;
	double get_dexterity_mod() const;
	double get_evasion_mod() const;
	double get_fortitude_mod() const;
	double get_leech_mod() const;
	double get_base_damage_mod() const;

	double get_damage() const;

	void set_level(int);

	void set_stats(vector<double>);
	void set_health(double);
	void set_strength(double);
	void set_dexterity(double);
	void set_evasion(double);
	void set_fortitude(double);
	void set_leech(double);
	void set_base_damage(double);

	void set_mods(vector<double>);
	void set_health_mod(double);
	void set_strength_mod(double);
	void set_dexterity_mod(double);
	void set_evasion_mod(double);
	void set_fortitude_mod(double);
	void set_leech_mod(double);
	void set_base_damage_mod(double);

	// do X amount of damage to entity, this function takes into account all the stats
	void do_damage(double);

	// Stat and mod vector should be {health, strength, dexterity, evasion, fortitude, leech, base}
	Entity(string name = "", int level = 0, vector<double> stats = { 0, 0, 0, 0, 0, 0, 0 }, vector<double> mods = {0,0,0,0,0,0,0});

	vector<string> entity_event_stack;
protected:
	string name;

	int level;

	double health;
	double strength;
	double dexterity;
	double evasion;
	double fortitude;
	double leech;
	double base_damage = 0;

	double health_mod;
	double strength_mod;
	double dex_mod;
	double evasion_mod;
	double fortitude_mod;
	double leech_mod;
	double base_damage_mod;
private:
	//Game game;
};