#include <iostream>
#include <Windows.h>
#include "Battle.h"

using namespace std;

bool Battle::get_status() const
{
	return status;
}

void Battle::toggle_status()
{
	status = (status) ? 0 : 1;
}

Player* Battle::get_player_instance() const
{
	return player_instance;
}

Monster Battle::get_monster() const
{
	return monster;
}

void Battle::do_player_attack(bool d)
{
	monster.do_damage(player_instance->get_damage());

	if (d) cout << "Player did " << player_instance->get_damage() << " points of damage!" << endl;
}

void Battle::do_monster_attack(bool d)
{
	player_instance->do_damage(monster.get_damage());

	if (d) cout << "Monster did " << monster.get_damage() << " points of damage!" << endl;
}

void Battle::do_turn(bool d)
{
	
	while (player_instance->get_health() > 0 && monster.get_health() > 0)
	{
		if (d) cout << "Player Health: " << player_instance->get_health() << endl;
		if (d) cout << "Monster Health: " << monster.get_health() << endl;
		do_player_attack(d);
		do_monster_attack(d);

		if (d) cout << "Player has " << player_instance->get_health() << " hp.\nMonster has " << monster.get_health() << " hp." << endl;
		Sleep(5000);
	}
	(player_instance->get_health() > monster.get_health()) ? cout << "Player wins!" << endl : cout << "Monster wins!" << endl;
}
// Fix bug where passing monster from get_random returns empty monster instance
Battle::Battle(Player* p, Monster m)
	: player_instance(p), monster("Test", 1, {10, 1, 1, 0,0,0, 1})
{
}