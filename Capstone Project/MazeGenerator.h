#include <vector>

using namespace std;

struct cell
{
	bool visited = false;
	// visited from should be the location in which, N E S W, in which the cell was visited from
	char visited_from = NULL;
	int x, y;
};

class Maze
{
public:
	void init_tree();

	void hunt_kill_generate();

	vector<vector<char>> tree_to_map();

	bool has_visited_neighbors(cell);

	bool has_unvisited_neigbors(cell);

	cell* get_cell_by_pos(int x, int y);

	vector<cell> get_neighbors(cell);

	vector<cell> get_tree() const;

	int get_width() const;

	int get_height() const;

	Maze(int width = 10, int height = 10);
private:
	int width;
	int height;

	vector<cell> tree;
};