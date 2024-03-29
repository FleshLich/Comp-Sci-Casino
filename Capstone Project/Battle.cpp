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
	if (player_instance->get_leech() > 0)
	{
		player_instance->set_health(player_instance->get_health() + (player_instance->get_damage() * (player_instance->get_leech() * 0.01)));
		player_instance->entity_event_stack.push_back(player_instance->get_name() + " absorbed " + to_string(player_instance->get_damage() * (player_instance->get_leech() * 0.01)) + " points of health from his attack");
	}

	if (d) 
	{
		cout << "Player did " << player_instance->get_damage() << " points of damage!" << endl;

		cout << "\n";
		for (int i = player_instance->entity_event_stack.size() - 1; i > -1; i--)
		{
			cout << player_instance->entity_event_stack[i] << "\n\n";
			player_instance->entity_event_stack.pop_back();
		}
	} 
}

void Battle::do_monster_attack(bool p)
{
	player_instance->do_damage(monster.get_damage());
	if (monster.get_leech() > 0)
	{
		monster.set_health(monster.get_health() + (monster.get_damage() * (monster.get_leech() * 0.01)));
		monster.entity_event_stack.push_back(monster.get_name() + " absorbed " + to_string(monster.get_damage() * (monster.get_leech() * 0.01)) + " points of health from his attack");
	}

	if (p)
	{
		cout << "Monster did " << monster.get_damage() << " points of damage!" << endl;

		cout << "\n";
		for (int i = monster.entity_event_stack.size() - 1; i > -1; i--)
		{
			cout << monster.entity_event_stack[i] << "\n\n";
			monster.entity_event_stack.pop_back();
		}
	}
	
}

void Battle::do_turn(bool p)
{
	
	while (player_instance->get_health() >= 1 && monster.get_health() >= 1)
	{
		if (p) system("CLS");
		if (p) cout << "Player Health: " << player_instance->get_health() << endl;
		if (p) cout << "Monster Health: " << monster.get_health() << endl;
		do_player_attack(p);
		if (monster.get_health() < 1)
		{
			break;
		}
		do_monster_attack(p);


		if (p) cout << "\nPlayer has " << player_instance->get_health() << " hp.\nMonster has " << monster.get_health() << " hp.\n\n";
		system("PAUSE");
	}
	(player_instance->get_health() > monster.get_health() && p) ? cout << "\nPlayer wins!" << endl : cout << "\nMonster wins!" << endl; system("PAUSE");
	toggle_status();
}

Battle::Battle(Player* p, Monster m)
	: player_instance(p), monster(m)
{
}