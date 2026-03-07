#pragma once

#include <string>
#include <vector>
#include <windows.h>

// TODO: add name update
class EnvVar {
public:
	EnvVar(HKEY scopeHkey, std::string name);
	
	std::string value; // from this->getValue();
	std::string setValue(const std::string& value);

	std::vector<std::string> getValues(); // Splitted string

	std::string remove();

	static void refreshEnvironment();
private:
	HKEY scopeHkey;

	std::string name;
	std::string getValue(); // Unsplitted string version, only called in the constructor for perfomance reasons :)
};