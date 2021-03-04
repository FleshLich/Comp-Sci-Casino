#include "CasinoGame.h"

double casino_game::get_money() const
{
	return money;
}

double casino_game::get_bet() const
{
	return bet;
}

int casino_game::get_difficulty() const
{
	return difficulty;
}

double casino_game::get_return() const
{
	switch (difficulty)
	{
	case 1:
		return bet * 1.5;
		break;
	case 2:
		return bet * 2;
		break;
	case 3:
		return bet * 3;
		break;
	default:
		break;
	}
}

void casino_game::set_money(double m)
{
	money = m;
}

void casino_game::set_bet(double b) 
{
	bet = b;
}

void casino_game::set_difficulty(int d)
{
	difficulty = d;
}

casino_game::casino_game(double m, double b, int difficulty)
{
	set_money(m);
	set_bet(b);
	set_difficulty(difficulty);
}