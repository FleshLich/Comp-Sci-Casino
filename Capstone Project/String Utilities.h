#pragma once
#include <string>
#include <sstream>
#include <regex>
#include <fstream>
#include <vector>

using namespace std;

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