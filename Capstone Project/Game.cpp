#include <random>
#include <iostream>
#include "Game.h"

void Game::generate_map()
{
	raw_map.reverse_backtrack_generate();

	// Do tile stuff
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

	vector<vector<char>> raw = raw_map.tree_to_map();
	vector<vector<tile>> parsed_map(raw_map.get_height());
	for (int y = 0; y < parsed_map.size(); y++)
	{
		for (int x = 0; x < raw[y].size(); x++)
		{
			tile new_tile;
			new_tile.pos = { x, y };
			if (raw[y][x] == '#')
			{
				new_tile.is_wall = true;
				new_tile.type_id = tile::tile_wall;
				parsed_map[y].push_back(new_tile);
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
			switch (map[y][x].type_id)
			{
			case tile::tile_empty:
				cout << " " << " ";
				break;
			case tile::tile_monster:
				cout << "X" << " ";
				break;
			case tile::tile_treasure:
				cout << "O" << " ";
				break;
			case tile::tile_treas_monst:
				cout << "*" << " ";
				break;
			case tile::tile_wall:
				cout << "#" << " ";
				break;
			default:
				break;
			}
		}
		cout << endl;
	}
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

int Game::get_depth() const
{
	return depth;
}

vector<double> Game::get_global_mods() const
{
	return global_modifiers;
}

Game::Game() 
{

}