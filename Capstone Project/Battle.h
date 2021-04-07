#pragma once
#include "Player.h"
#include "Monster.h"

class Battle
{
public:
	bool get_status() const;

	void toggle_status();

	Player* get_player_instance() const;
	Monster get_monster() const;

	void do_monster_attack(bool debug=false);
	void do_player_attack(bool debug = false);

	void do_turn(bool debug=false);

	Battle(Player *player_instance, Monster monster);
private:
	// Whether the battle is ongoing or not, false means battle is over/not start, true means battle is current
	bool status = false;
	Player *player_instance;
	Monster monster;
};