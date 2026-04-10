#pragma once

#include <string>
#include <vector>

// TODO: add name update
class EnvVar {
public:
	char separator;

	// Expected scope values are in util/util.h
	EnvVar(int scope, std::string name, char separator);
	
	std::string value; // from this->getValue();
	virtual std::string getValue() = 0; // Unsplitted string version, only called in the constructor for performance reasons :) (Why did I not make it a protected/private method ?)
	std::vector<std::string> getValues();

	virtual std::string setValue(const std::string& value) = 0;

	std::string updateName(const std::string& updated); // Uses setValue

	std::string remove(); // Calls both removeEnvEntry and removeRelatedPathEntries
	
	virtual void refreshEnvironment() = 0;
	
	virtual void addSubDirToPath(std::string subDir) = 0;
	void addBinToPath(); // Calls addSubDirToPath 

protected:
	int scope;
	std::string name;
	virtual std::string removeEnvEntry() = 0;
	std::vector<int> removeRelatedPathEntries();
};