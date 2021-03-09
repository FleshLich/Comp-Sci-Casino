#pragma once

class game_of_life
{
public:
	// Creates a 10 x 10 2d array that the game will operate on
	void init_array();

	void print_game();

	// returns number of neigbors adjacent to cell
	// Pass in two integers representing position of cell in 2d array
	int get_num_neighbors(int, int);

	int** get_life_array() const;

	// Simulates a generation based on the rules of Conway's game of life
	void simulate_generation();

	game_of_life();
private:
	int** life_array;
	int width = 20;
	int height = 20;
};