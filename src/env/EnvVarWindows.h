#pragma once

#include <string>
#include <vector>
#include <windows.h>
#include "EnvVar.h"

class EnvVarWindows : public EnvVar {
public:
	EnvVarWindows(int scope, std::string name);

	std::vector<std::string> getValues();
	std::string getValue() override;

	std::string setValue(const std::string& value) override;
	void refreshEnvironment() override;
	
	void addBinToPath() override;

private:
	HKEY scopeHkey;
	HKEY getHkeyOrThrow(REGSAM permission);
	std::vector<std::string> getValues(char separator);
	
	std::string removeEnvEntry() override;
};