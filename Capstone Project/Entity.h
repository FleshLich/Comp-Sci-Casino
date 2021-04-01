#pragma once
#include <string>
#include <vector>
#include "Game.h"

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

	//Game get_game() const;

	// Stat vector should be {health, strength, dexterity, evasion, fortitude, leech, base}
	Entity(string name = "", int level = 0, vector<double> stats = { 0, 0, 0, 0, 0, 0, 0 });
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
private:
	//Game game;
};