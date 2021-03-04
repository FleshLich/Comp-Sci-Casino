#pragma once

class game_of_life
{
public:
	int** get_life_array() const;

	// Creates a 10 x 10 2d array that the game will operate on
	void init_array();

	void print_game();

	game_of_life();
private:
	int** life_array;
};