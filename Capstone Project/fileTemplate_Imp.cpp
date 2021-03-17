#include "fileTemplate.h"
#include "String Utilities.h"

void fileTemplate::set_variables()
{
	variables = StringUtilities::split(StringUtilities::split(file_string, "\n")[0], ",");

	for (int i = 0; i < variables.size(); i++)
	{
		variables[i] = StringUtilities::trim(variables[i]);
	}
}

void fileTemplate::set_var_values(vector<string> values)
{
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

vector<string> fileTemplate::get_variables() const
{
	return variables;
}

vector<string> fileTemplate::get_var_values() const
{
	return var_values;
}

fileTemplate::fileTemplate(string f_name)
{
	file_name = f_name;
	file.open(file_name);
	file_string = StringUtilities::file_to_string(&file);

	set_variables();
}