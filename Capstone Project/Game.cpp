#include <random>
#include <iostream>
#include <chrono>
#include <Windows.h>
#include "Game.h"

typedef std::chrono::duration<int, std::milli> millisecs_t;

void Game::generate_map()
{
	raw_map.reverse_backtrack_generate();

	parse_map();

	player.set_pos(map_start);
}

Item* Game::generate_item(int r)
{
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> typeGen(0, Item::all_types.size() - 1);
	uniform_int_distribution<int> statGen(0, 3);

	item_type temp_type = Item::all_types[typeGen(mt)];
	Item* temp = new Item(temp_type.type, "An Item", { (double)statGen(mt) * r, (double)statGen(mt) * r, (double)statGen(mt) * r, (double)statGen(mt) * r, (double)statGen(mt) * r, (double)statGen(mt) * r, (double)statGen(mt) * r + ((temp_type == Item::sword || temp_type == Item::bow) ? 1 : 0) });
	temp->set_knowledge_req(statGen(mt) * r);
	temp->set_type(temp_type);
	temp->set_rarity(rarity_type{r});

	item_list.push_back(temp);
	return temp;
}

Monster Game::generate_monster()
{
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> healthGen(2, 10);
	uniform_int_distribution<int> statGen(0, 3);

	Monster new_monster("Monster", 1);
	new_monster.set_stats({ (double)healthGen(mt), (double)statGen(mt), (double)statGen(mt), (double)statGen(mt), (double)statGen(mt), (double)statGen(mt), (double)statGen(mt) });
	// TODO: add monster difficulty generator to enhance item type
	int num_items = statGen(mt);
	for (int i = 0; i < num_items; i++)
	{
		Item* new_item = generate_item(Item::rarity_n.type);
		drop new_drop{new_item, (statGen(mt) + 1) * 25};
		new_monster.add_to_drops(new_drop);
	}

	monster_list.push_back(new_monster);

	return new_monster;
}

void Game::parse_map()
{
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> tileGen(0, 100);
	uniform_int_distribution<int> heightGen(0, raw_map.get_height() - 1);
	uniform_int_distribution<int> widthGen(0, raw_map.get_width() - 1);

	map_start = { widthGen(mt) * 2, heightGen(mt) * 2 };
	map_end = { widthGen(mt) * 2, heightGen(mt) * 2 };

	while (map_start == map_end) map_end = { widthGen(mt) * 2, heightGen(mt) * 2 };

	vector<vector<char>> raw = raw_map.tree_to_map();
	vector<vector<tile>> parsed_map(raw.size());
	for (int y = 0; y < parsed_map.size(); y++)
	{
		for (int x = 0; x < raw[y].size(); x++)
		{
			tile new_tile;
			new_tile.pos = { x, y };
			if (y == map_end[1] && x == map_end[0])
			{
				new_tile.type_id = tile::tile_end;
				parsed_map[y].push_back(new_tile);
				continue;
			}
			else if (y == map_start[1] && x == map_start[0])
			{
				new_tile.type_id = tile::tile_start;
				new_tile.contains_player = true;
				parsed_map[y].push_back(new_tile);
				continue;
			}
			if (raw[y][x] == '#')
			{
				new_tile.is_wall = true;
				new_tile.type_id = tile::tile_wall;
				parsed_map[y].push_back(new_tile);
				continue;
			}

			int num = tileGen(mt);
			
			if (num > 50 && num <= 80)
			{
				new_tile.monster = generate_monster();
				new_tile.type_id = tile::tile_monster;
			}
			else if (num > 80 && num <= 95)
			{
				new_tile.treasure = generate_item();
				new_tile.type_id = tile::tile_treasure;
			}
			else if (num > 95)
			{
				new_tile.treasure = generate_item();
				new_tile.type_id = tile::tile_treas_monst;
			}
			else
			{
				new_tile.type_id = tile::tile_empty;
			}
			parsed_map[y].push_back(new_tile);
		}
	}
	map = parsed_map;
}

// Fix inventory display, equip, and modifier bugs
void Game::show_inventory()
{
	system("CLS");
	vector<Item> cur_inv = player.get_inventory();
	int page = 1;
	int pages = (cur_inv.size() / 9) + 1; pages == 0 ? 1 : pages;
	bool showing_item = false;
	bool viewing = true;
	viewChanged = true;
	vector<int> keys = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 };

	while (viewing)
	{
		if (viewChanged)
		{
			system("CLS");
			for (int i = 0 + (10 * (page - 1)); i < ((cur_inv.size() / 9) * 9) / pages; i++)
			{
				if (player.get_knowledge() >= cur_inv[i].get_knowledge_req())
				{
					cout << (i / ((page > 1) ? 9 : 1)) + 1 << ". " << cur_inv[i].get_name() << " " << Item::rarity_to_string(cur_inv[i].get_rarity()) << " " << cur_inv[i].get_desc() << endl;
					continue;
				}
				cout << "????? ?????(Your knowledge level is too low)\n";
			}
			cout << "\nPage " << page << " of " << pages;

			cout << "\nPress the corresponding key to view an item.";
			cout << "\nPress the right and left arrow key to go back and forth between pages";
			cout << "\nPress x to exit";

			viewChanged = false;
		}
		for (int i = 0 ; i < keys.size(); i++)
		{
			if (GetAsyncKeyState(keys[i]) & 0x8000 && check_press() && (i + (10 * (page - 1))) < player.get_inventory().size())
			{
				viewChanged = true;
				view_item(i);//(i + (10 * (page - 1))) + 1);
			}
		}
		if (GetAsyncKeyState(0x25) & 0x8000 && check_press() && page != 1)
		{
			viewChanged = true;
			page--;
		}
		else if (GetAsyncKeyState(0x27) & 0x8000 && check_press() && page != pages)
		{
			viewChanged = true;
			page++;
		}
		if (GetAsyncKeyState(0x58) & 0x8000 && check_press())
		{
			viewChanged = true;
			viewing = false;
			break;
		}
		Sleep(1);
	}
}

void Game::show_stats()
{
	system("CLS");
	cout << "Health: " << player.get_health() << endl;
	cout << "Strength: " << player.get_strength() << endl;
	cout << "Dexterity: " << player.get_dexterity() << endl;
	cout << "Evasion: " << player.get_evasion() << endl;
	cout << "Fortitude: " << player.get_fortitude() << endl;
	cout << "Leech: " << player.get_leech() << endl;
	cout << "Knowledge: " << player.get_knowledge() << endl;
	cout << "Damage: " << player.get_damage() << endl;
	system("PAUSE");
}

void Game::view_item(int i)
{
	system("CLS");
	viewChanged = true;
	Item cur_item = player.get_inventory()[i];

	bool viewing = true;
	while (viewing)
	{
		if (viewChanged)
		{
			system("CLS");
			cout << "Item Name: " << cur_item.get_name() << endl;
			cout << "Item Description: " << cur_item.get_desc() << endl;
			cout << "Item Type: " << cur_item.get_type() << endl;
			cout << "Health Mod: " << cur_item.get_health_mod() << endl;
			cout << "Strength Mod: " << cur_item.get_strength_mod() << endl;
			cout << "Dexterity Mod: " << cur_item.get_dex_mod() << endl;
			cout << "Evasion Mod: " << cur_item.get_evasion_mod() << endl;
			cout << "Fortitude Mod: " << cur_item.get_fortitude_mod() << endl;
			cout << "Leech Mod: " << cur_item.get_leech_mod() << endl; 
			cout << "Damage: " << cur_item.get_damage_mod() << endl;

			cout << "\nPress 1 to equip this item";
			cout << "\nPress x to return";

			viewChanged = false;
		}
		if (GetAsyncKeyState(0x31) & 0x8000 && check_press())
		{
			equip_item(cur_item);
			viewChanged = true;
			viewing = false;
		}
		if (GetAsyncKeyState(0x58) & 0x8000 && check_press())
		{
			viewChanged = true;
			viewing = false;
			break;
		}
		Sleep(1);
	}
}

void Game::equip_item(Item i)
{
	item_type cur_type = i.get_type();
	if (cur_type == Item::bow || cur_type == Item::sword)
	{
		player.add_to_inventory(player.get_equipped()[3]);
		player.set_equipped(i, 3);
	}
	else if (cur_type == Item::helmet)
	{
		player.add_to_inventory(player.get_equipped()[0]);
		player.set_equipped(i, 0);
	}
	else if (cur_type == Item::breastplate || cur_type == Item::potion_set)
	{
		player.add_to_inventory(player.get_equipped()[1]);
		player.set_equipped(i, 1);
	}
	else if (cur_type == Item::greaves)
	{
		player.add_to_inventory(player.get_equipped()[2]);
		player.set_equipped(i, 2);
	}
	player.remove_from_inventory(i);
}

void Game::debug_print_map()
{
	for (int y = 0; y < map.size(); y++)
	{
		for (int x = 0; x < map[y].size(); x++)
		{
			if (map[y][x].contains_player) { cout << "W"; continue; }

			switch (map[y][x].type_id)
			{
			case tile::tile_empty:
				cout << " ";
				break;
			case tile::tile_monster:
				cout << "X";
				break;
			case tile::tile_treasure:
				cout << "O";
				break;
			case tile::tile_treas_monst:
				cout << "*";
				break;
			case tile::tile_wall:
				cout << "#";
				break;
			case tile::tile_start:
				cout << "S";
				break;
			case tile::tile_end:
				cout << "E";
				break;
			default:
				break;
			}
		}
		cout << endl;
	}
	cout << endl;
	for (int i = event_stack.size() - 1; i > -1; i--)
	{
		cout << event_stack[i] << endl;
		event_stack.pop_back();
	}
	cout << "Press 1 to view Inventory\n";
	cout << "Press 2 to view Stats\n";
}

void Game::load_items()
{}

void Game::load_monsters()
{}

Maze Game::get_raw_map() const
{
	return raw_map;
}

vector<vector<tile>> Game::get_map() const
{
	return map;
}

Player Game::get_player() const
{
	return player;
}

Battle Game::get_battle() const
{
	return cur_battle;
}

Monster Game::get_random_monster()
{
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> mGen(0, monster_list.size() - 1);

	return monster_list[mGen(mt)];
}

vector<int> Game::get_start() const
{
	return map_start;
}

vector<int> Game::get_end() const
{
	return map_end;
}

int Game::get_depth() const
{
	return depth;
}

vector<double> Game::get_global_mods() const
{
	return global_modifiers;
}

void Game::add_event(string m, bool repeats)
{
	if (event_stack.empty()) { event_stack.push_back(m); return; }
	
	if (!repeats)
	{
		for (int i = 0; i < event_stack.size(); i++)
		{
			if (event_stack[i] == m) return;
		}
	}
	event_stack.push_back(m);
	viewChanged = true;
}

void Game::move_player(vector<int> offset)
{
	viewChanged = true;

	vector<int> new_pos = { player.get_pos()[0] + offset[0], player.get_pos()[1] + offset[1] };
	if (new_pos[1] > map.size() - 1 || new_pos[1] < 0 || new_pos[0] > map[0].size() - 1 || new_pos[0] < 0)
	{
		return;
	}

	tile* new_tile = &map[new_pos[1]][new_pos[0]];
	if (new_tile->type_id == tile::tile_wall)
	{
		return;
	}
	

	map[player.get_pos()[1]][player.get_pos()[0]].contains_player = false;
	new_tile->contains_player = true;
	player.set_pos(new_pos);
}

void Game::level_player()
{
	system("CLS");
	bool leveling = true;
	bool viewChanged = true;

	int init_points = player.get_attr_points();
	int cur_points = init_points;

	vector<double> base_stats = { 0, 0, 0, 0, 0, 0, 0};
	vector<double> new_stats = base_stats;
	while (leveling)
	{
		if (viewChanged)
		{
			system("CLS");

			cout << "Press the corresponding key to level up that stat. Press C to refund your points\n";
			cout << "You currently have " << cur_points << " points to spend\n";
			cout << "1. Health: " << player.get_health() + new_stats[0] * 5 << "(+5 per point)\n";
			cout << "2. Strength: " << player.get_strength() + new_stats[1] << endl;
			cout << "3. Dexterity: " << player.get_dexterity() + new_stats[2] << endl;
			cout << "4. Evasion: " << player.get_evasion() + new_stats[3] << endl;
			cout << "5. Fortitude: " << player.get_fortitude() + new_stats[4] << endl;
			cout << "6. Leech: " << player.get_leech() + new_stats[5] << endl;
			cout << "7. Knowledge: " << player.get_knowledge() + new_stats[6] << endl;
			cout << "\nPress x to return to the game";

			viewChanged = false;
		}
		
		// Fix cpu usage
		if (cur_points > 0)
		{
			if (GetKeyState(0x31) & 0x8000 && check_press())
			{
				cur_points--;
				new_stats[0]++;
				viewChanged = true;
			}
			else if (GetKeyState(0x32) & 0x8000 && check_press())
			{
				cur_points--;
				new_stats[1]++;
				viewChanged = true;
			}
			else if (GetKeyState(0x33) & 0x8000 && check_press())
			{
				cur_points--;
				new_stats[2]++;
				viewChanged = true;
			}
			else if (GetKeyState(0x34) & 0x8000 && check_press())
			{
				cur_points--;
				new_stats[3]++;
				viewChanged = true;
			}
			else if (GetKeyState(0x35) & 0x8000 && check_press())
			{
				cur_points--;
				new_stats[4]++;
				viewChanged = false;
			}
			else if (GetKeyState(0x36) & 0x8000 && check_press())
			{
				cur_points--;
				new_stats[5]++;
				viewChanged = true;
			}
			else if (GetKeyState(0x37) & 0x8000 && check_press())
			{
				cur_points--;
				new_stats[6]++;
				viewChanged = true;
			}
		}
		if (GetKeyState(0x43) & 0x8000 && check_press())
		{
			cur_points = init_points;
			new_stats = base_stats;
			viewChanged = true;
		}
		else if (GetAsyncKeyState(0x58) & 0x8000 && check_press())
		{
			leveling = false;
		}
		Sleep(1);
	}
	player.set_attr_points(cur_points);
	new_stats[0] = new_stats[0] * 5;
	player.add_stats(new_stats);
}

void Game::start_battle(bool d)
{
	cur_battle.toggle_status();
	cur_battle.do_turn(d);
}

void Game::toggle_game()
{
	playing = (playing) ? false : true;
}

void Game::run_game()
{
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dropGen(0, 100);
	viewChanged = true;

	for (int i = 0; i < 18; i++)
	{
		player.add_to_inventory(*generate_item());
	}
	// TODO: Fix super fast keyboard input, fix some events not showing up due to has_changed not changing
	while (playing)
	{
		tile* cur_tile = &map[player.get_pos()[1]][player.get_pos()[0]];
		if (false)//cur_battle.get_status())
		{
			system("CLS");
			cur_battle.do_turn(1);
			cur_battle = Battle(&player, get_random_monster());
			for (int i = 0; i < cur_battle.get_monster().get_drop_table().size(); i++)
			{
				drop cur_drop = cur_battle.get_monster().get_drop_table()[i];
				if (dropGen(mt) < cur_drop.chance)
				{
					player.add_to_inventory(*cur_drop.to_drop);
					add_event("You got a new item!", true);
				}
				viewChanged = true;
			}
			continue;
		}

		if (player.get_attr_points() > 0)
		{
			add_event("You have attribute points to spend! Press L to spend them");
		}

		if (cur_tile->type_id == tile::tile_treasure)
		{
			cur_tile->type_id = tile::tile_empty;
			player.add_to_inventory(*generate_item());
			add_event("You found treasure! An item has been added to your inventory.");
			viewChanged = true;
		}
		if (cur_tile->type_id == tile::tile_monster || cur_tile->type_id == tile::tile_treas_monst)
		{
			cur_tile->type_id = tile::tile_empty;
			cur_battle.toggle_status();
			viewChanged = true;
			continue;
		}
		if (cur_tile->type_id == tile::tile_end)
		{
			add_event("You have found the exit, press x to move to the next level");
		}

		if (GetAsyncKeyState(0x31) & 0x8000 && check_press())
		{
			viewChanged = true;
			show_inventory();
		}
		else if (GetAsyncKeyState(0x32) & 0x8000 && check_press())
		{
			viewChanged = true;
			show_stats();
		}
		else if (GetAsyncKeyState(0x4C) && player.get_attr_points() > 0 && check_press())
		{
			viewChanged = true;
			level_player();
		}

		if (GetAsyncKeyState(0x57) & 0x8000 && check_press())
		{
			move_player({ 0, -1 });
		}
		else if (GetAsyncKeyState(0x53) & 0x8000 && check_press())
		{
			move_player({ 0, 1 });
		}
		if (GetAsyncKeyState(0x41) & 0x8000 && check_press())
		{
			move_player({ -1,0 });
		}
		else if (GetAsyncKeyState(0x44) & 0x8000 && check_press())
		{
			move_player({ 1,0 });
		}
		if (viewChanged) { system("CLS"); debug_print_map(); viewChanged = false; };
		Sleep(1);
	}
}

Game::Game()
	: cur_battle(&player, generate_monster()), raw_map(15, 15)
{
	generate_map();
}

bool Game::check_press()
{
	millisecs_t duration(std::chrono::duration_cast<millisecs_t>(chrono::steady_clock::now() - keyPressed));
	if (duration.count() > 50)
	{
		keyPressed = chrono::steady_clock::now();
		return true;
	}
	keyPressed = chrono::steady_clock::now();
	return false;
}