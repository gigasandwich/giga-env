#pragma once

#include <string>
#include <vector>

// TODO: add name update
class EnvVar {
public:
	char separator;

	// Expected scope values are in util/util.h
	EnvVar(int scope, std::string name, char separator);

	std::string value; // from this->getUpdatedValue();
	std::vector<std::string> getValues();

	virtual std::string setValue(const std::string &value) = 0;

	std::string updateName(const std::string &updated); // Uses setValue

	std::string remove(); // Calls both removeEnvEntry and removeRelatedPathEntries

	virtual void refreshEnvironment() = 0;

	virtual void addSubDirToPath(std::string subDir) = 0;
	void addBinToPath(); // Calls addSubDirToPath

protected:
	int scope;
	std::string name;
	virtual std::string getUpdatedValue() = 0; // Unsplitted string version, unlike getValues()

	// Called by remove()
	virtual std::string removeEnvEntry() = 0;
	std::vector<int> removeRelatedPathEntries();
};