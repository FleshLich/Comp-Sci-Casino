// Assignment: Capstone Project
// Created by Joshua Roberts
// Date: 

#include <iostream>
#include <string>
#include <stdlib.h>
#include "Blackjack.h"

using namespace std;


int main()
{
	bool mainMenu = true;
	bool casinoMenu = false;
	bool gameOfLifeMenu = false;
	int input;

	while (mainMenu)
	{
		Blackjack bGame;
		system("CLS");
		cout << "Welcome to the Casino of computer science!\n";
		cout << "Input a number to go to one of the categories below!\n";
		cout << "1. Games\n2. Simulations\n";

		cin >> input;

		switch (input)
		{
		case 1:
			casinoMenu = true;
			break;
		default:
			break;
		}

		while (casinoMenu)
		{
			system("CLS");
			if (bGame.get_total(bGame.get_playerHand()) > 21)
			{
				cout << "You lose!!\n";
				system("PAUSE");
				break;
			}
			if (bGame.get_total(bGame.get_playerHand()) == 21)
			{
				cout << "You win!\n";
				system("PAUSE");
				break;
			}

			bGame.print_game();

			cout << "\n\n1. To hit, 2 to stand: ";
			cin >> input;
			switch (input)
			{
			case 1:
				bGame.hit();
				break;
			case 2:
				if (bGame.stand())
				{
					cout << "\n\nYou win!\n";
				}
				else 
				{
					cout << "\n\nYou lose\n";
				}
				system("PAUSE");
				casinoMenu = false;
				break;
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
