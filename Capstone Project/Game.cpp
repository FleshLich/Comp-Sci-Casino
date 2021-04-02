#include <random>
#include <iostream>
#include <Windows.h>
#include "Game.h"

void Game::generate_map()
{
	raw_map.reverse_backtrack_generate();

	parse_map();

	player.set_pos(map_start);
}

Monster Game::generate_monster()
{
	Monster temp;
	return temp;
}

Item* Game::generate_item()
{
	Item* temp = new Item;
	item_list.push_back(temp);
	return temp;
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
	cout << endl << endl;
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

void Game::move_player(vector<int> offset)
{
	vector<int> new_pos = { player.get_pos()[0] + offset[0], player.get_pos()[1] + offset[1] };
	tile* new_tile = &map[new_pos[1]][new_pos[0]];

	map[player.get_pos()[1]][player.get_pos()[0]].contains_player = false;
	new_tile->contains_player = true;
	player.set_pos(new_pos);
}

void Game::toggle_game()
{
	playing = (playing) ? false : true;
}

void Game::run_game()
{
	while (playing)
	{
		system("CLS");
		if (GetAsyncKeyState(0x57))
		{
			move_player({ 0, -1 });
		}
		debug_print_map();
		Sleep(1000);
	}
}

Game::Game() 
{
	generate_map();
}