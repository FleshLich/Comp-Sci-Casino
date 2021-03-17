#pragma once
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class fileTemplate
{
public:
	void set_template(string);

	void set_variables();

	void set_var_values(vector<string>);

	string get_file_name() const;

	string get_file_string() const;

	string get_menu_string() const;

	string get_parsed_menu_string() const;

	vector<string> get_variables() const;

	vector<string> get_var_values() const;

	fileTemplate(string, vector<string>);
private: 
	ifstream file;
	string file_name;
	string file_string;
	vector<string> variables;
	vector<string> var_values;
};