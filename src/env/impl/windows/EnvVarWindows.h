#pragma once

#include <string>
#include <vector>
#include <windows.h>
#include "../../EnvVar.h"

class EnvVarWindows : public EnvVar {
public:
	EnvVarWindows(int scope, std::string name);

	std::vector<std::string> getValues();
	std::string getUpdatedValue() override;

	std::string setValue(const std::string& value) override;
	void refreshEnvironment() override;
	
	void addSubDirToPath(std::string subDir) override;

private:
	HKEY scopeHkey;
	HKEY getHkeyOrThrow(REGSAM permission);
	std::vector<std::string> getValues(char separator);
	
	std::string removeEnvEntry() override;
};