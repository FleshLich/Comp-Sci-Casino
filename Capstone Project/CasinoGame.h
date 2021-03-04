#pragma once

class casino_game
{
public:
	double get_money() const;

	double get_bet() const;

	int get_difficulty() const;
	
	// Calculates how much the user will get from winning
	double get_return() const;

	void set_money(double);

	void set_bet(double);

	void set_difficulty(int);

	virtual void print_game() = 0;

	casino_game(double m = 0, double b = 0, int difficulty = 2);
private:
	double money;
	double bet;

	// Determines how hard the game will be as well as how the return will be calculated
	// Difficulty should be between 1 and 3, 1 being easiest, 3 being hardest
	int difficulty;
};