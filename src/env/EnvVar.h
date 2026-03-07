#pragma once

#include <string>
#include <vector>
#include <windows.h>

// TODO: add name update
class EnvVar {
public:
	EnvVar(HKEY scopeHkey, std::string name);
	
	std::string value; // from this->getValue();

	virtual std::vector<std::string> getValues() = 0;

	virtual std::string setValue(const std::string& value) = 0;

	virtual std::string remove() = 0;

	virtual void refreshEnvironment() = 0;

protected:
	HKEY scopeHkey;

	std::string name;
	std::vector<std::string> getValues(char separator); // Splitted string version
	virtual std::string getValue() = 0; // Unsplitted string version, only called in the constructor for performance reasons :)
};