#pragma once
#include <vector>

using namespace std;

struct cell
{
	bool visited = false;
	vector<cell*> connected_to;
	int x, y;
};
// NOTE: Due to the way that the maze is generated the width and height will be almost doubled 
class Maze
{
public:
	void init_tree();
	
	void print_map();

	void reverse_backtrack_generate();

	vector<vector<char>> tree_to_map();

	bool has_visited_neighbors(cell);

	bool has_unvisited_neighbors(cell);

	bool are_cells_connected(cell*, cell*);

	bool is_complete();

	cell* get_cell_by_pos(int x, int y);

	vector<cell*> get_neighbors(cell);

	vector<cell*> get_unvisited_neigbors(cell);

	cell* get_random_cell();

	vector<cell> get_tree() const;

	vector<int> get_start() const;

	int get_width() const;

	int get_height() const;

	Maze(int w = 5, int h = 5);
private:
	int width;
	int height;
	vector<int> startPos;

	vector<cell> tree;
};