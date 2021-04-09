#pragma once
#include <iostream>

using namespace std;

template <class type>
void safe_input(type* in)
{
	while (!(cin >> *in))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}