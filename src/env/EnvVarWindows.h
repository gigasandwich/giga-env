#pragma once

#include <string>
#include <vector>
#include <windows.h>
#include "EnvVar.h"

class EnvVarWindows : public EnvVar {
public:
	EnvVarWindows(HKEY scopeHkey, std::string name);

	std::vector<std::string> getValues();

	std::string setValue(const std::string& value) override;
	std::string remove() override;
	void refreshEnvironment() override;

protected:
	std::string getValue() override;

private:
	HKEY getHkeyOrThrow(REGSAM permission);
	std::vector<std::string> getValues(char separator);
};