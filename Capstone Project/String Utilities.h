#pragma once
#include <string>
#include <sstream>
#include <regex>
#include <fstream>
#include <vector>
#include "MazeGenerator.h"

using namespace std;

extern struct cell;

class StringUtilities
{
public:
	// Stores the contents of a file into a string
	// Used to allow easier manipulation on the contents of a file
	static string file_to_string(ifstream* file)
	{
		stringstream contents;
		contents << file->rdbuf();

		return contents.str();
	}

	// Converts vector into string
	static string vector_to_string(vector<string> v, string seperator = "")
	{
		string s;

		for (int i = 0; i < v.size(); i++)
		{
			s.append(v[i] + seperator);
		}
		return s;
	}

	static string cell_connected_to_string(cell c)
	{
		string temp = "";
		for (int i = 0; i < c.connected_to.size(); i++)
		{
			temp += c.connected_to[i]->x + " " + c.connected_to[i]->y;
			temp += " ";
		}
		return temp;
	}

	static string maze_to_string(vector<vector<char>> m)
	{
		string s;
		for (int i = 0; i < m.size(); i++)
		{
			for (int j = 0; j < m[i].size(); j++)
			{
				s += m[i][j];
				s += " ";
			}
			s += "\n";
		}
		return s;
	}

	// Creates a vector with elements that are determined by what is between the delimeter
	static vector<string> split(string s, string delimeter = " ")
	{
		vector<string> split;

		int start = 0;
		int end = s.find(delimeter);
		while (end > -1)
		{
			split.push_back(s.substr(start, end - start));
			start = end + delimeter.size();
			end = s.find(delimeter, start);
		}
		split.push_back(s.substr(start, end - start));

		return split;
	}

	static string replace(string s, string to_replace, string replace_with = "")
	{
		string::size_type n = 0;
		while ((n = s.find(to_replace, n)) != string::npos)
		{
			s.replace(n, to_replace.size(), replace_with);
			n += replace_with.size();
		}
		return s;
	}

	static string replace_without_move(string s, string to_replace, string replace_with = " ")
	{

	}

	// Removes any sort of whitespace from the beginning and end of a string
	static string trim(string s)
	{
		s = regex_replace(s, regex("\\s+$"), string(""));
		s = regex_replace(s, regex("^\\s+"), string(""));

		return s;
	}

	StringUtilities(string s)
	{
		curString = s;
	}
private:
	string curString;
};