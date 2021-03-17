#include "fileTemplate.h"
#include "String Utilities.h"

void fileTemplate::set_template(string f_name)
{
	file_name = f_name;
	file.open(file_name);
	file_string = StringUtilities::file_to_string(&file);

	set_variables();
}

void fileTemplate::set_variables()
{
	variables = StringUtilities::split(StringUtilities::split(file_string, "\n")[0], ",");

	for (int i = 0; i < variables.size(); i++)
	{
		variables[i] = StringUtilities::trim(variables[i]);
		variables[i].insert(variables[i].begin(), ' ');
		variables[i].insert(variables[i].end(), ' ');
	}
}

void fileTemplate::set_var_values(vector<string> values)
{
	//if (values.size() != variables.size())
	//{
		//throw "Your variables and variable values are not the same size";
	//}
	var_values = values;
}

string fileTemplate::get_file_name() const
{
	return file_name;
}

string fileTemplate::get_file_string() const
{
	return file_string;
}

string fileTemplate::get_menu_string() const
{
	vector<string> tempVector;
	tempVector = StringUtilities::split(file_string, "\n");
	tempVector.erase(tempVector.begin());
	return StringUtilities::vector_to_string(tempVector, "\n");
}

string fileTemplate::get_parsed_menu_string() const
{
	string s = get_menu_string();
	for (int i = 0; i < variables.size(); i++)
	{
		s = StringUtilities::replace(s, variables[i], var_values[i]);
	}

	return s;
}

vector<string> fileTemplate::get_variables() const
{
	return variables;
}

vector<string> fileTemplate::get_var_values() const
{
	return var_values;
}

fileTemplate::fileTemplate(string f_name, vector<string> values)
{
	file_name = f_name;
	file.open(file_name);
	file_string = StringUtilities::file_to_string(&file);

	set_variables();
	set_var_values(values);
}