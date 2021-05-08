#include <iostream>
#include <random>
#include "Blackjack.h"

using namespace std;

void Blackjack::print_playerCards(int index)
{
	if (index == -1)
	{
		for (int i = 0; i < playerHand.size(); i++)
		{
			(playerHand[i] == 1) ? cout << "Ace" : cout << playerHand[i];
			cout << " ";
		}
	}
	else
	{
		cout << (playerHand[index] == 1) ? 'Ace' : char(playerHand[index]);
		cout << " ";
	}
}

void Blackjack::print_houseCards(int index)
{
	if (index == -1)
	{
		for (int i = 0; i < houseHand.size(); i++)
		{
			(houseHand[i] == 1) ? cout << "Ace" : cout << houseHand[i];
			cout << " ";
		}
	}
	else
	{
		(houseHand[index] == 1) ? cout << "Ace" : cout << houseHand[index];
		cout << " ";
	}
}

void Blackjack::print_game()
{
	cout << "House's Card: "; stood ? print_houseCards(-1) : print_houseCards(0); cout << endl;
	cout << "Your cards: "; print_playerCards(-1); cout << endl;
	cout << "Your total: " << get_total(playerHand) << endl;
	if (stood) { cout << "House's total: " << get_total(houseHand) << endl; }
}

int Blackjack::get_card()
{
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> cardGen(1, 10);
	
	// Generate a number between 1 and 10
	int card = cardGen(mt);

	if (card_amounts[card][1] > 0)
	{
		card_amounts[card][1]--;
	}
	else 
	{
		get_card();
	}
	return card;
}

int Blackjack::get_total(vector<int> hand)
{
	int total = 0;
	int aces = 0;
	for(int i = 0; i < hand.size(); i++)
	{
		if (hand[i] == 1 && total + 11 <= 21) 
		{
			aces++;
			total += 11;
		}
		else
		{
			total += hand[i];
		}
		if (aces > 0 && total > 21) { aces--; total -= 10; };
	}

	return total;
}

vector<int> Blackjack::get_playerHand() const
{
	return playerHand;
}

vector<int> Blackjack::get_houseHand() const
{
	return houseHand;
}

bool Blackjack::hasBlackjack(vector<int> hand)
{
	if (hand[0] == 1 && hand[1] == 10)
	{
		return 1;
	}
	else if (hand[1] == 1 && hand[0] == 10)
	{
		return 1;
	}
	return 0;
}

void Blackjack::add_to_player(int card)
{
	playerHand.push_back(card);
}

void Blackjack::add_to_house(int card)
{	
	houseHand.push_back(card);
}

bool Blackjack::hit()
{
	add_to_player(get_card());
	return (get_total(playerHand) > 21) ? 1 : 0;
}

int Blackjack::stand()
{
	stood = true;
	switch (get_difficulty())
	{
	case 1:
		while (get_total(houseHand) < 17)
		{
			add_to_house(get_card());
		}
		if (get_total(houseHand) >= 17 && get_total(houseHand) <= 21)
		{
			if (get_total(houseHand) == get_total(playerHand)) return 2;
			return (get_total(houseHand) < get_total(playerHand));
		}
		else 
		{
			return 1;
		}
		break;
	default:
		break;
	}
}

Blackjack::Blackjack(double m, double b, int difficulty) : casino_game(m, b, difficulty)
{
	add_to_house(get_card()); add_to_house(get_card());
	add_to_player(get_card()); add_to_player(get_card());
}