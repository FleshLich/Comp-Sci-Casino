// Assignment: Capstone Project
// Created by Joshua Roberts
// Date: 

#include <iostream>
#include <string>
#include <stdlib.h>
#include "Blackjack.h"
#include "GameOfLife.h"

using namespace std;


int main()
{
	bool mainMenu = true;
	bool casinoMenu = false;
	bool gameOfLifeMenu = false;
	int input;
	double money = 1000;

	while (mainMenu)
	{
		system("CLS");

		Blackjack bGame(money, 10, 1);
		game_of_life gGame;

		cout << "Welcome to the Casino of computer science!\n";
		cout << "Input a number to go to one of the categories below!\n";
		cout << "1. Games\n2. Simulations\n";

		cin >> input;

		switch (input)
		{
		case 1:
			casinoMenu = true;
			break;
		case 2:
			gameOfLifeMenu = true;
			break;
		default:
			break;
		}

		while (casinoMenu)
		{
			system("CLS");
			bGame.print_game();

			if (bGame.hasBlackjack(bGame.get_playerHand()))
			{
				cout << "\nYou have Blackjack!\n";
				money += bGame.get_return();
				system("PAUSE");
				break;
			}

			cout << "\n\n1. To hit, 2 to stand: ";
			cin >> input;
			switch (input)
			{
			case 1:
				if (bGame.hit()) { cout << "You busted!\n"; system("PAUSE"); casinoMenu = false; };
				money -= bGame.get_bet();
				break;
			case 2:
			{
				bool stand = bGame.stand();
				int index = 1;

				while (index < bGame.get_houseHand().size() - 1)
				{
					cout << "\nHouse draws "; bGame.print_houseCards(index); cout << endl;
					index++;
					system("PAUSE");
				}
				if (stand)
				{
					cout << "\nYou win!\n\n";
					money += bGame.get_return();
				}
				else
				{
					cout << "\nYou lose\n";
					money -= bGame.get_bet();
				}
				cout << money;
				bGame.print_game();
				system("PAUSE");
				casinoMenu = false;
			}
			default:
				break;
			}
		}
		while (gameOfLifeMenu)
		{
			cout << "";
		}
		input = NULL;
	}

	return 0;
}
