#pragma once
#include <string>

// NOTE: This game of life will vary majorly depending on how big the grid is 
// Rather than killing cells that go out of bounds, the program instead has the cells wrap around to the other side
// This means that patterns such as the R-pentomino will eventually die(rather than stabilize) because some of the cells will wrap around and disrupt the original formation
// The best way to test this is to use things such as "still lifes", "Oscillators", or "Spaceships"
// Wikipedia has some good patterns: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
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

	// Creates an txt file filled with zeroes based on game of life parameters
	void create_blank_template();

	// Sets life array to a template
	void use_template(std::string);

	game_of_life();
private:
	int** life_array;
	int width = 20;
	int height = 20;
	int generationsSimulated = 0;
};