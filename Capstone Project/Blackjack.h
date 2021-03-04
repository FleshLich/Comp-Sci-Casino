#pragma once
#include <vector>
#include "CasinoGame.h"

using namespace std;

class Blackjack : public casino_game
{
public:
	// prints player card at index or all cards if index is -1
	void print_playerCards(int index);

	// prints house card at index or all cards if index is -1
	void print_houseCards(int index);

	void print_game();

	// Returns a random number which will act as a card
	int get_card();

	// Gets the total of the hand passed through
	int get_total(vector<int>);

	vector<int> get_playerHand() const;

	vector<int> get_houseHand() const;

	bool hasBlackjack(vector<int>);

	// Adds card to player's hand
	void add_to_player(int);

	// Adds card to house's hand
	void add_to_house(int);
	
	// Does all the actions that "hitting" does in blackjack
	// Returns a bool, 1 if player has busted, 0 if player is has not
	bool hit();

	// Makes the player stand, the house will draw cards until they stop due to difficulty or busting
	// Returns 1 if the player won the game, 0 if the player lost
	bool stand();

	Blackjack(double m = 0, double b = 0, int difficulty = 1);
private:
	vector<int> playerHand;
	vector<int> houseHand;
	int card_amounts[10][2] = { {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {8, 4}, {9, 4}, {10, 12} };
	bool stood = false;
};