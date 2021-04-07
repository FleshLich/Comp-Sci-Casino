#pragma once
#include <vector>
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "Battle.h"
#include "MazeGenerator.h"

struct tile
{
	vector<int> pos;
	Monster monster;
	Item* treasure;
	bool contains_player = false;
	bool is_wall = false;
	int type_id = 0;

	static const int tile_uninit = 0;
	static const int tile_empty = 1;
	static const int tile_monster = 2;
	static const int tile_treasure = 3;
	static const int tile_treas_monst = 4;
	static const int tile_wall = 5;
	static const int tile_start = -1;
	static const int tile_end = -2;
};

class Game
{
public:
	void generate_map();
	Monster generate_monster();
	Item* generate_item();

	void parse_map();

	void debug_print_map();

	void load_items();
	void load_monsters();

	Maze get_raw_map() const;
	vector<vector<tile>> get_map() const;
	Player get_player() const;
	Battle get_battle() const;

	Monster get_random_monster();

	vector<int> get_start() const;
	vector<int> get_end() const;

	int get_depth() const;

	vector<double> get_global_mods() const;

	void move_player(vector<int>);

	void start_battle(bool debug = false);

	void toggle_game();
	void run_game();

	Game();
private:
	Maze raw_map;
	vector<vector<tile>> map;
	Player player;

	int depth;

	vector<double> global_modifiers;
	
	vector<Item*> item_list;
	vector<Monster> monster_list;

	vector<int> map_start;
	vector<int> map_end;

	Battle cur_battle;

	bool playing = false;
};